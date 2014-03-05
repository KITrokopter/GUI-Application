#ifndef QUADCOPTERMODEL_HPP
#define QUADCOPTERMODEL_HPP

#include <QAbstractTableModel>

enum QuadcopterColumns
{
    QUADCOPTER_NAME,
    QUADCOPTER_STATUS,
    QUADCOPTER_BATTERY,
    QUADCOPTER_CONNECTION,
};

class QuadcopterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QuadcopterModel(QObject *parent = 0)
        : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

};

#endif // QUADCOPTERMODEL_HPP
