#include "quadcoptermodel.hpp"

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
 * @param role ignored for now
 * @return fake data
 */
QVariant QuadcopterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
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

}
