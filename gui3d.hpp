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
#include "imouselistener.hpp"

class Gui3D : public QObject, public IMouseListener
{
    Q_OBJECT

public:
    Gui3D(QIrrlichtWidget *iw, kitrokopter::API *api);
    void initializeIrrlicht();
    void mouseDragged(int deltaX, int deltaY);
    void zoom(int delta);

public slots:
    void updateQuadcopters();
    void updateCameras();
    void callRepaint();

private:
    QIrrlichtWidget *iw;
    kitrokopter::API *api;

    std::map<int, GUICamera*> cameras;
    std::map<int, GUIQuadcopter*> quadcopters;

    vector3df cameraLookAt;
    vector3df cameraRotation;
    double cameraPitchRotationStep;
    double cameraHorizontalRotationStep;
    double cameraDistanceStep;
    double cameraDistance;
    double cameraZoomStep;
    volatile bool repaintRequested;
    ICameraSceneNode *cameraNode;
    ISceneNode *cameraCenterNode;

    QTimer quadcopterTimer;
    QTimer cameraTimer;
    QTimer repaintTimer;
};

#endif // GUI3D_HPP
