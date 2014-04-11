#include "quadcoptermodel.hpp"
#include "colors.hpp"

#include "API.hpp"
#include "APIQuadcopter.hpp"

#include <QColor>

QuadcopterModel::QuadcopterModel(QObject *parent, kitrokopter::API *api)
	: QAbstractTableModel(parent),
	api(api)
{
	timer.setInterval(100);
	connect(&timer, SIGNAL(timeout()), this, SLOT(updateQuadcopters()));
	timer.start();
}

void QuadcopterModel::updateQuadcopters()
{
	QuadcopterVector next = QuadcopterVector::fromStdVector(api->getQuadcopters());
	int oldSize = quadcopters.size(), nextSize = next.size();
	if (oldSize < nextSize) {
		beginInsertRows(QModelIndex(), oldSize, nextSize - 1);
	} else if (oldSize > nextSize) {
		beginRemoveRows(QModelIndex(), nextSize, oldSize - 1);
	}
	// Do the data change.
	quadcopters = next;
	if (oldSize < nextSize) {
		endInsertRows();
	} else if (oldSize > nextSize) {
		endRemoveRows();
	}
	// We don't track changes, so we don't really know exactly what changed.
	emit dataChanged(index(0, 0), index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1));
}

int QuadcopterModel::rowFor(kitrokopter::APIQuadcopter *quadcopter)
{
	return quadcopters.indexOf(quadcopter);
}

kitrokopter::APIQuadcopter* QuadcopterModel::quadcopterFor(int row)
{
	return quadcopters.at(row);
}

int QuadcopterModel::rowCount(const QModelIndex& /*parent*/) const
{
	return quadcopters.size();
}

int QuadcopterModel::columnCount(const QModelIndex& /*parent*/) const
{
	return QUADCOPTER_COLUMNS_LAST;
}

/**
 * @brief Provides data about Quadcopters.
 * @param index model index
 * @param role Qt::DisplayRole or Qt::DecorationRole
 * @return fake data
 */
QVariant QuadcopterModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	kitrokopter::APIQuadcopter *quadcopter = quadcopters.at(row);
	switch (role) {
	// "The key data to be rendered in the form of text"
	case Qt::DisplayRole:
		switch (index.column()) {
		case QUADCOPTER_NAME:
			return QString("Q") + QString::number(quadcopter->getId());
		case QUADCOPTER_STATUS:
			return quadcopter->isTracked() ? QString("tracked") : QString("untracked");
		case QUADCOPTER_BATTERY:
			return QString::number(quadcopter->getBatteryStatus());
		case QUADCOPTER_CONNECTION:
			return QString::number(quadcopter->getLinkQuality());
		case QUADCOPTER_CHANNEL:
			return QString::number(quadcopter->getChannel());
		case QUADCOPTER_ROLL:
			return QString::number(quadcopter->getStabilizerRollData());
		case QUADCOPTER_PITCH:
			return QString::number(quadcopter->getStabilizerPitchData());
		case QUADCOPTER_YAW:
			return QString::number(quadcopter->getStabilizerYawData());
		default:
			// Invalid column.
			return QVariant();
		}
	// "The data to be rendered as a decoration in the form of an icon"
	case Qt::DecorationRole:
		// Color range is [min, max].
		// We only use the min color for visualization here.
		return parseColor(quadcopter->getColorRange()[0]);
	default:
		// We don't implement other display roles.
		return QVariant();
	}
}

QVariant QuadcopterModel::headerData(int section, Qt::Orientation orientation, int /*role*/) const
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
		case QUADCOPTER_CHANNEL:
			return QString("Channel");
		case QUADCOPTER_ROLL:
			return QString("Roll");
		case QUADCOPTER_PITCH:
			return QString("Pitch");
		case QUADCOPTER_YAW:
			return QString("Yaw");
		}
	}
	// Invalid column or vertical header.
	return QVariant();
}

