#include "gui3d.hpp"

#include <irrlicht/IGeometryCreator.h>

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
}

void Gui3D::initializeIrrlicht()
{
    iw->initialize();

    ISceneManager *sceneManager = iw->getSceneManager();

    sceneManager->getGUIEnvironment()->addStaticText(L"TestText", rect<s32>(10, 10, 200, 22));
    sceneManager->addCameraSceneNode(0, vector3df(0, 0, 0), vector3df(1, 0, 0));
    sceneManager->addLightSceneNode(0, vector3df(0, 0, 0), SColorf(1, 1, 1));

    /*const IGeometryCreator *geometryCreator = sceneManager->getGeometryCreator();
    sphere = geometryCreator->createSphereMesh();
    sphereNode = sceneManager->addMeshSceneNode(sphere);

    sphereNode->setPosition(vector3df(50, 0, 0));
    ITexture *greenTexture = iw->getIrrlichtDevice()->getVideoDriver()->getTexture("install/lib/gui_application/textures/green.png");
    sphereNode->setMaterialTexture(0, greenTexture);
    sphereNode->setMaterialFlag(EMF_LIGHTING, false);*/

    std::vector<double> position(3);
    std::vector<double> rotation(9);
    position[0] = 50;
    GUICamera *cam0 = new GUICamera("set me: camera mesh", position, rotation, sceneManager);

    qDebug() << "InitializedIrrlicht";

    quadcopterTimer.setInterval(100);
    connect(&quadcopterTimer, SIGNAL(timeout()), this, SLOT(updateQuadcopters()));
    quadcopterTimer.start();

    cameraTimer.setInterval(1000);
    connect(&cameraTimer, SIGNAL(timeout()), this, SLOT(updateCameras()));
    cameraTimer.start();
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

    for (std::vector<kitrokopter::APICamera*>::iterator it = cameras.begin(); it != cameras.end(); it++) {
        if (this->cameras.count((*it)->getId())) {
            this->cameras[(*it)->getId()] = new GUICamera("set me: camera mesh", std::vector<double>(3), std::vector<double>(9), iw->getSceneManager());
        }

        this->cameras[(*it)->getId()]->setPositionVector((*it)->getPosition());
        //this->cameras[(*it)->getId()]->setRotationMatrix((*it)->getOrientation());
    }
}
