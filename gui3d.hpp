#ifndef GUI3D_HPP
#define GUI3D_HPP

#include <QIrrlichtWidget.hpp>
#include <irrlicht/IMesh.h>
#include <QTimer>
#include <QObject>
#include <map>

#include "API.hpp"

#include "guicamera.hpp"
#include "guiquadcopter.hpp"

class Gui3D : public QObject
{
    Q_OBJECT

public:
    Gui3D(QIrrlichtWidget *iw, kitrokopter::API *api);
    void initializeIrrlicht();

public slots:
    void updateQuadcopters();
    void updateCameras();

private:
    QIrrlichtWidget *iw;
    kitrokopter::API *api;

    std::map<int, GUICamera*> cameras;
    std::map<int, GUIQuadcopter*> quadcopters;

    QTimer quadcopterTimer;
    QTimer cameraTimer;
};

#endif // GUI3D_HPP
