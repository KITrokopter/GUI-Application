#include "gui3d.hpp"

#include <irrlicht/IGeometryCreator.h>
#include <cmath>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Gui3D::Gui3D(QIrrlichtWidget *iw, kitrokopter::API *api)
{
    this->iw = iw;
    this->api = api;

    cameraDistance = 100;
    cameraHorizontalRotationStep = 0.5;
    cameraPitchRotationStep = -0.3;
    cameraDistanceStep = 10;
    cameraZoomStep = 0.9995;
    repaintRequested = false;

    cameraNode = 0;
    cameraCenterNode = 0;
}

void Gui3D::initializeIrrlicht()
{
    iw->initialize();
    iw->setMouseListener(this);

    ISceneManager *sceneManager = iw->getSceneManager();

    sceneManager->getGUIEnvironment()->addStaticText(L"TestText", rect<s32>(10, 10, 200, 22));
    sceneManager->addLightSceneNode(0, vector3df(0, 2000, 0), SColorf(1, 1, 1), 10000);

    cameraCenterNode = sceneManager->addEmptySceneNode();
    cameraNode = sceneManager->addCameraSceneNode(cameraCenterNode, vector3df(0, 0, cameraDistance), vector3df(0, 0, -1));
    cameraNode->setFarValue(20000);



    /*const IGeometryCreator *geometryCreator = sceneManager->getGeometryCreator();
    sphere = geometryCreator->createSphereMesh();
    sphereNode = sceneManager->addMeshSceneNode(sphere);

    sphereNode->setPosition(vector3df(50, 0, 0));
    ITexture *greenTexture = iw->getIrrlichtDevice()->getVideoDriver()->getTexture("install/lib/gui_application/textures/green.png");
    sphereNode->setMaterialTexture(0, greenTexture);
    sphereNode->setMaterialFlag(EMF_LIGHTING, false);*/

    std::vector<double> position(3);
    std::vector<double> rotation(9);
    //position[0] = 50;
    GUICamera *cam0 = new GUICamera("set me: camera mesh", position, rotation, sceneManager);

    qDebug() << "InitializedIrrlicht";

    quadcopterTimer.setInterval(100);
    connect(&quadcopterTimer, SIGNAL(timeout()), this, SLOT(updateQuadcopters()));
    quadcopterTimer.start();

    cameraTimer.setInterval(1000);
    connect(&cameraTimer, SIGNAL(timeout()), this, SLOT(updateCameras()));
    cameraTimer.start();

    repaintTimer.setInterval(10);
    connect(&repaintTimer, SIGNAL(timeout()), this, SLOT(callRepaint()));
    repaintTimer.start();
}

void Gui3D::updateQuadcopters()
{
    std::vector<kitrokopter::APIQuadcopter*> quadcopters = api->getQuadcopters();

    for (std::vector<kitrokopter::APIQuadcopter*>::iterator it = quadcopters.begin(); it != quadcopters.end(); it++) {
        // TODO
        (*it)->getCurrentPosition();
    }
}

void Gui3D::updateCameras()
{
    std::vector<kitrokopter::APICamera*> cameras = api->getCameras();
    cameraLookAt = vector3df();

    for (std::vector<kitrokopter::APICamera*>::iterator it = cameras.begin(); it != cameras.end(); it++) {
        if (this->cameras.count((*it)->getId())) {
            this->cameras[(*it)->getId()] = new GUICamera("set me: camera mesh", std::vector<double>(3), std::vector<double>(9), iw->getSceneManager());
        }

        cameraLookAt.X += (*it)->getPosition().getX() / cameras.size();
        cameraLookAt.Y += (*it)->getPosition().getY() / cameras.size();
        cameraLookAt.Z += (*it)->getPosition().getZ() / cameras.size();
        this->cameras[(*it)->getId()]->setPositionVector((*it)->getPosition());
        //this->cameras[(*it)->getId()]->setRotationMatrix((*it)->getOrientation());
    }
}

void Gui3D::mouseDragged(int deltaX, int deltaY)
{
    qDebug() << "Mouse dragged" << deltaX << "/" << deltaY;

    cameraRotation.X += deltaY * cameraPitchRotationStep;

    if (cameraRotation.X > 80) {
        cameraRotation.X = 80;
    }

    if (cameraRotation.X < -80) {
        cameraRotation.X = -80;
    }

    qDebug() << "Pitch: " << cameraRotation.X;

    cameraRotation.Y += deltaX * cameraHorizontalRotationStep;

    qDebug() << "Yaw: " << cameraRotation.Y;

    cameraCenterNode->setPosition(cameraLookAt);
    cameraCenterNode->setRotation(cameraRotation);

    repaintRequested = true;
}

void Gui3D::zoom(int delta)
{
    qDebug() << "Zoom enter " << delta;

    vector3df position = cameraNode->getPosition();
    position.Z *= pow(cameraZoomStep, delta);

    if (position.Z < 10) {
        position.Z = 10;
    } else if (position.Z > 4000) {
        position.Z = 4000;
    }

    cameraNode->setPosition(position);

    repaintRequested = true;

    qDebug() << "Zoom exit";
}

void Gui3D::callRepaint()
{
    if (repaintRequested) {
        iw->repaint();
        repaintRequested = false;
    }
}
