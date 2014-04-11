#include "quadcoptertrackedfilter.hpp"
#include "quadcoptermodel.hpp"

QuadcopterTrackedFilter::QuadcopterTrackedFilter(QObject *parent) :
	QSortFilterProxyModel(parent)
{
}

void QuadcopterTrackedFilter::filterTracked()
{
	tracked = true;
}

void QuadcopterTrackedFilter::filterUntracked()
{
	tracked = false;
}

bool QuadcopterTrackedFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	QModelIndex index = sourceModel()->index(source_row, QUADCOPTER_STATUS, source_parent);
	QString status = sourceModel()->data(index).toString();
	return (tracked && status == "tracked") || (!tracked && status == "untracked");
}

