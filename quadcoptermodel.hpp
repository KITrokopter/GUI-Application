#ifndef QUADCOPTERMODEL_HPP
#define QUADCOPTERMODEL_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <QTimer>

namespace kitrokopter {
class API;
class APIQuadcopter;
}

enum QuadcopterColumns
{
	QUADCOPTER_NAME,
	QUADCOPTER_STATUS,
	QUADCOPTER_BATTERY,
	QUADCOPTER_CONNECTION,
	QUADCOPTER_CHANNEL,
	QUADCOPTER_ROLL,
	QUADCOPTER_PITCH,
	QUADCOPTER_YAW,
	QUADCOPTER_COLUMNS_LAST
};

typedef QVector<kitrokopter::APIQuadcopter*> QuadcopterVector;

/**
 * The quadcopter model adapts the API's quadcopters to a Qt table model.
 */
class QuadcopterModel : public QAbstractTableModel {
	Q_OBJECT
public:
	explicit QuadcopterModel(QObject *parent, kitrokopter::API *api);

	int rowFor(kitrokopter::APIQuadcopter *quadcopter);
	kitrokopter::APIQuadcopter* quadcopterFor(int row);

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:
	void updateQuadcopters();

private:
	kitrokopter::API *api;
	QuadcopterVector quadcopters;

	QTimer timer;
};

#endif // QUADCOPTERMODEL_HPP
