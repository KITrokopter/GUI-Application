#ifndef MOVEMENTCONTROLLER_HPP
#define MOVEMENTCONTROLLER_HPP

#include <QObject>
#include <QVector3D>
#include <stdint.h>

class MovementController : public QObject
{
    Q_OBJECT
public:
    explicit MovementController(QObject *parent = 0);

    QVector3D movementVector();
    QVector3D rotationVector();

signals:

public slots:
    void axisValueChanged(int, int);
    void buttonValueChanged(int, bool);

private:
    int16_t xmov, ymov, zmov;
    int16_t rot;

};

#endif // MOVEMENTCONTROLLER_HPP
