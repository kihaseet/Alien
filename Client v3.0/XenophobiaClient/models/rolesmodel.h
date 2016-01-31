#ifndef ROLESMODEL_H
#define ROLESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "proto/types.pb.h"

class RolesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoleRole {
        RoleID = Qt::UserRole + 1
    };

    RolesModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    void addRole(types::Role role);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role_role = Qt::DisplayRole) const;
    void clear();

private:
    QList<types::Role> _roles;
};

#endif // ROLESMODEL_H
