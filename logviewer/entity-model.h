/***************************************************************************
 *   Copyright (C) 2012 by David Edmundson <kde@davidedmundson.co.uk>      *
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


#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include <QAbstractItemModel>

#include <TelepathyQt/Types>

#include <TelepathyQt/Account>
#include <KTp/types.h>

/**
    Lists all avilable entities.

    roles:
      - Qt::DisplayRole - name
      - Qt::DecorationRole - avatar
      - EntityModel::IdRole
      - EntityModel::TypeRole - EntityType (EntityTypeContact/Room/Self/Unknown)
      - EntityModel::EntityRole - relevant KTp::LogEntity
  */

namespace KTp {
    class PendingLoggerOperation;
}

class EntityModelItem;

class EntityModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Role {
        IdRole = Qt::UserRole,
        TypeRole,
        EntityRole,
        AccountRole,
        ContactRole
    };

    explicit EntityModel(QObject *parent = 0);
    virtual ~EntityModel();

    void setAccountManager(const Tp::AccountManagerPtr &accountManager);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool removeRows(int start, int count, const QModelIndex &parent = QModelIndex());

private Q_SLOTS:
    void onEntitiesSearchFinished(KTp::PendingLoggerOperation*);
    void onEntityContactRetrieved(Tp::PendingOperation*);

private:
    EntityModelItem *m_rootItem;

};

#endif // ENTITYMODEL_H
