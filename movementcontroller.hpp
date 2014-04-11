#ifndef MOVEMENTCONTROLLER_HPP
#define MOVEMENTCONTROLLER_HPP

#include <QObject>
#include <QVector3D>
#include <stdint.h>

namespace kitrokopter {
class API;
}

class MovementController : public QObject {
	Q_OBJECT
public:
	explicit MovementController(kitrokopter::API *api, QObject *parent = 0);

	QVector3D movementVector();

signals:

public slots:
	void axisValueChanged(int, int);
	void buttonValueChanged(int, bool);

private:
	void notifyAPI();

	int16_t xmov, ymov, zmov;
	int16_t rot;

	kitrokopter::API *api;
};

#endif // MOVEMENTCONTROLLER_HPP
