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
    GUICamera *cam0 = new GUICamera("set me", position, rotation, sceneManager);

    qDebug() << "InitializedIrrlicht";
}
