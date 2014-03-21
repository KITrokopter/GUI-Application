#include "gui3d.hpp"

#include <irrlicht/IGeometryCreator.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Gui3D::Gui3D(QIrrlichtWidget *iw)
{
    this->iw = iw;
}

void Gui3D::initializeIrrlicht()
{
    iw->initialize();

    qDebug() << "Constructing gui3d";
    ISceneManager *sceneManager = iw->getSceneManager();

    if (sceneManager != 0) {
        qDebug() << "Got scene manager";
    } else {
        qDebug() << "Got NULL scene manager";
    }

    sceneManager->addCameraSceneNodeMaya();

    const IGeometryCreator *geometryCreator = sceneManager->getGeometryCreator();
    qDebug() << "Got geometry creator";
    sphere = geometryCreator->createSphereMesh();
    sphereNode = sceneManager->addMeshSceneNode(sphere);

    sphereNode->setPosition(vector3df(0, 0, 0));

    qDebug() << "InitializedIrrlicht";
}
