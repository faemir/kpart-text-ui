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

#ifndef CHANNELCONTACTLIST_H
#define CHANNELCONTACTLIST_H

#include <QtCore/QObject>
#include <TelepathyQt4/TextChannel>
#include <TelepathyQt4/Contact>
#include <TelepathyQt4/Types>
#include <TelepathyQt4/Channel>
#include <TelepathyQt4/Presence>

class ChannelContactListContact: public QObject
{
    Q_OBJECT
public:
    explicit ChannelContactListContact(const Tp::ContactPtr & contact, QObject *parent);

signals:
    void contactPresenceChanged(const Tp::ContactPtr & contact, const Tp::Presence & presence);
    void contactAliasChanged(const Tp::ContactPtr & contact, const QString & alias);

private slots:
    void onPresenceChanged(const Tp::Presence & newPresence);
    void onAliasChanged(const QString &alias);

private:
    Tp::ContactPtr m_contact;
};


class ChannelContactList : public QObject
{
    Q_OBJECT
public:
    explicit ChannelContactList(const Tp::TextChannelPtr & channel, QObject *parent = 0);

signals:
    void contactPresenceChanged(const Tp::ContactPtr & contact, const Tp::Presence & presence);
    void contactAliasChanged(const Tp::ContactPtr & contact, const QString & alias);

public slots:
    void groupMembersChanged(const Tp::Contacts &groupMembersAdded,
                             const Tp::Contacts &groupLocalPendingMembersAdded,
                             const Tp::Contacts &groupRemotePendingMembersAdded,
                             const Tp::Contacts &groupMembersRemoved,
                             const Tp::Channel::GroupMemberChangeDetails &details);

private:
    QSet<ChannelContactListContact> contacts;
};

#endif // CHANNELCONTACTLIST_H