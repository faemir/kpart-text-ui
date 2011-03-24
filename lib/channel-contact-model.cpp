/***************************************************************************
 *   Copyright (C) 2011 by David Edmundson <kde@davidedmundson.co.uk>      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include "channel-contact-model.h"

#include <KDebug>
#include <KIcon>

ChannelContactModel::ChannelContactModel(const Tp::TextChannelPtr & channel, QObject *parent)
    : QAbstractListModel(parent)
{
    //add existing contacts
    addContacts(channel->groupContacts());

    //monitor for future changes
    connect(channel.data(),
            SIGNAL(groupMembersChanged(Tp::Contacts,Tp::Contacts,Tp::Contacts,
                                       Tp::Contacts,Tp::Channel::GroupMemberChangeDetails)),
            SLOT(onGroupMembersChanged(Tp::Contacts,Tp::Contacts,Tp::Contacts,
                                     Tp::Contacts,Tp::Channel::GroupMemberChangeDetails)));
}


int ChannelContactModel::rowCount(const QModelIndex &parent) const
{
    if (! parent.isValid()) {
        return m_contacts.size();
    }
    return 0;
}

QVariant ChannelContactModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    int row = index.row();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant(m_contacts[row]->alias());

    case Qt::DecorationRole:
        switch(m_contacts[row]->presence().type()) {
        case Tp::ConnectionPresenceTypeAvailable:
            return QVariant(KIcon("im-user"));
        case Tp::ConnectionPresenceTypeAway:
            //fall through
        case Tp::ConnectionPresenceTypeExtendedAway:
            return QVariant(KIcon("im-user-away"));
        case Tp::ConnectionPresenceTypeBusy:
            return QVariant(KIcon("im-user-busy"));
        case Tp::ConnectionPresenceTypeOffline:
            //fall through
        case Tp::ConnectionPresenceTypeHidden:
            return QVariant(KIcon("im-user-offline"));
        default:
            return QVariant(KIcon("im-user"));
        }

    default:
        return QVariant();
    }
}

void ChannelContactModel::onGroupMembersChanged(const Tp::Contacts & groupMembersAdded,
                                             const Tp::Contacts & groupLocalPendingMembersAdded,
                                             const Tp::Contacts & groupRemotePendingMembersAdded,
                                             const Tp::Contacts & groupMembersRemoved,
                                             const Tp::Channel::GroupMemberChangeDetails & details)
{
    kDebug();

    Q_UNUSED(groupLocalPendingMembersAdded);
    Q_UNUSED(groupRemotePendingMembersAdded);
    Q_UNUSED(details);

    addContacts(groupMembersAdded);
    removeContacts(groupMembersRemoved);
}

void ChannelContactModel::onContactPresenceChanged(const Tp::Presence &presence)
{
    Tp::ContactPtr contact(qobject_cast<Tp::Contact*>(sender()));

    QModelIndex index = createIndex(m_contacts.lastIndexOf(contact), 0);
    emit dataChanged(index, index);

    emit contactPresenceChanged(contact, presence);}

void ChannelContactModel::onContactAliasChanged(const QString &alias)
{
    Tp::ContactPtr contact(qobject_cast<Tp::Contact*>(sender()));

    QModelIndex index = createIndex(m_contacts.lastIndexOf(contact), 0);
    emit dataChanged(index, index);

    emit contactAliasChanged(contact, alias);
}

void ChannelContactModel::addContacts(const Tp::Contacts &contacts)
{
    QList<Tp::ContactPtr> newContacts = contacts.toList();

    foreach(Tp::ContactPtr contact, newContacts) {
        connect(contact.data(), SIGNAL(aliasChanged(QString)), SLOT(onContactAliasChanged(QString)));
        connect(contact.data(), SIGNAL(presenceChanged(Tp::Presence)), SLOT(onContactPresenceChanged(Tp::Presence)));
    }

    beginInsertRows(QModelIndex(), m_contacts.size(), m_contacts.size() + newContacts.size());
    m_contacts << newContacts;
    endInsertRows();
}

void ChannelContactModel::removeContacts(const Tp::Contacts &contacts)
{
    foreach(Tp::ContactPtr contact, contacts) {

        //I think this is needed as technically the contact itself hasn't actually been deleted even if we remove our pointers to it
        //and could be used referenced elsewhere in the chat application in a different tab.
        //if we don't disconnect could we still get notifications here about their status/presence changes even if a contact has left the room
        disconnect(contact.data(), SIGNAL(aliasChanged(QString)), this, SLOT(onContactAliasChanged(QString)));
        disconnect(contact.data(), SIGNAL(presenceChanged(Tp::Presence)), this, SLOT(onContactPresenceChanged(Tp::Presence)));

        beginRemoveRows(QModelIndex(), m_contacts.indexOf(contact), m_contacts.indexOf(contact));
        m_contacts.removeAll(contact);
        endRemoveRows();
    }
}
