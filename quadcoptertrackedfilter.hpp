#ifndef QUADCOPTERTRACKEDFILTER_H
#define QUADCOPTERTRACKEDFILTER_H

#include <QSortFilterProxyModel>

/**
 * Filters a quadcopter model, only letting tracked or untracked quadcopters
 * through.
 *
 * @see QuadcopterModel
 */
class QuadcopterTrackedFilter : public QSortFilterProxyModel {
	Q_OBJECT
public:
	explicit QuadcopterTrackedFilter(QObject *parent = 0);

	/**
	 * Set filtering mode to only allow untracked quadcopters.
	 */
	void filterUntracked();

	/**
	 * Set filtering mode to only allow tracked quadcopters.
	 */
	void filterTracked();

	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

signals:

public slots:

private:
	bool tracked;
};

#endif // QUADCOPTERTRACKEDFILTER_H
