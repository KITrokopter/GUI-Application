#include "quadcoptermodel.hpp"
#include <QColor>

int QuadcopterModel::rowCount(const QModelIndex &parent) const
{
    return 4;
}

int QuadcopterModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

/**
 * @brief Provides fake data about Quadcopters.
 * @param index model index
 * @param role Qt::DisplayRole or Qt::DecorationRole
 * @return fake data
 */
QVariant QuadcopterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    switch (role) {
    // "The key data to be rendered in the form of text"
    case Qt::DisplayRole:
        switch (index.column()) {
        case QUADCOPTER_NAME:
            return QString("Q") + QString::number(row);
        case QUADCOPTER_STATUS:
            return row % 2 ? QString("tracked") : QString("untracked");
        case QUADCOPTER_BATTERY:
            return QString::number(row * 5);
        case QUADCOPTER_CONNECTION:
            return QString::number(row * 7);
        default:
            // Invalid column.
            return QVariant();
        }
    // "The data to be rendered as a decoration in the form of an icon"
    case Qt::DecorationRole:
        return QColor(row * 20, row * 50, row * 30);
    default:
        // We don't implement other display roles.
        return QVariant();
    }
}

QVariant QuadcopterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case QUADCOPTER_NAME:
            return QString("Name");
        case QUADCOPTER_STATUS:
            return QString("Status");
        case QUADCOPTER_BATTERY:
            return QString("Battery");
        case QUADCOPTER_CONNECTION:
            return QString("Connection");
        }
    }
    // Invalid column or vertical header.
    return QVariant();
}
