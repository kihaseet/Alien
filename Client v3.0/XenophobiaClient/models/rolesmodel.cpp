#include "rolesmodel.h"

RolesModel::RolesModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> RolesModel::RolesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoleID] = "role";
    return roles;
}

void RolesModel::addRole(types::Role role)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _roles << role;
    endInsertRows();
}

int RolesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _roles.count();
}

QVariant RolesModel::data(const QModelIndex &index, int role_role) const
{
    if (index.row() < 0 || index.row() >= _roles.count())
    {
        return QVariant();
    }
    return _roles[index.row()];
}

void RolesModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    _roles.clear();
    endRemoveRows();
}

