#ifndef QUADCOPTERTRACKEDFILTER_H
#define QUADCOPTERTRACKEDFILTER_H

#include <QSortFilterProxyModel>

class QuadcopterTrackedFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QuadcopterTrackedFilter(QObject *parent = 0);

    void filterUntracked();
    void filterTracked();

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

signals:

public slots:

private:
    bool tracked;
};

#endif // QUADCOPTERTRACKEDFILTER_H
