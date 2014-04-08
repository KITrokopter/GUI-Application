#include "gui3d.hpp"
#include "API.hpp"

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

    simulationNode = 0;
    groundNode = 0;

    cameraDistance = 1000;
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

    ILightSceneNode *light = sceneManager->addLightSceneNode(0, vector3df(0, 2000, 0), SColorf(1, 1, 1), 10000);
    light->enableCastShadow(true);

    cameraCenterNode = sceneManager->addEmptySceneNode();
    cameraNode = sceneManager->addCameraSceneNode(cameraCenterNode, vector3df(0, 0, cameraDistance), vector3df(0, 0, -1));
    cameraNode->setFarValue(20000);

    simulationNode = sceneManager->addEmptySceneNode();
    simulationNode->setRotation(vector3df(-90, 0, 0));

    ISceneNode *arrowNode = sceneManager->addMeshSceneNode(sceneManager->addArrowMesh("x-axis", SColor(255, 255, 0, 0), SColor(255, 255, 0, 0), 4, 8, 100, 95, 5, 5), simulationNode);
    arrowNode->setRotation(vector3df(90, 90, 0));
    arrowNode->setMaterialFlag(EMF_LIGHTING, false);
    arrowNode = sceneManager->addMeshSceneNode(sceneManager->addArrowMesh("y-axis", SColor(255, 0, 255, 0), SColor(255, 0, 255, 0), 4, 8, 100, 95, 5, 5), simulationNode);
    arrowNode->setRotation(vector3df(0, 0, 0));
    arrowNode->setMaterialFlag(EMF_LIGHTING, false);
    arrowNode = sceneManager->addMeshSceneNode(sceneManager->addArrowMesh("z-axis", SColor(255, 0, 0, 255), SColor(255, 0, 0, 255), 4, 8, 100, 95, 5, 5), simulationNode);
    arrowNode->setRotation(vector3df(90, 0, 0));
    arrowNode->setMaterialFlag(EMF_LIGHTING, false);

    createBackground(simulationNode);

    #ifdef DEBUG
    q0 = new GUIQuadcopter(simulationNode, vector3df(100, 0, 500), sceneManager);
    c0 = new GUICamera(simulationNode, "install/lib/gui_application/models/camera.3ds", vector3df(0, 500, 0), sceneManager);
    #endif

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

    shadowFixTimer.setInterval(1000);
    connect(&shadowFixTimer, SIGNAL(timeout()), this, SLOT(updateShadows()));
    shadowFixTimer.start();
}

void Gui3D::createBackground(ISceneNode *parent)
{
    ISceneManager *sceneManager = iw->getSceneManager();

    sceneManager->setShadowColor(SColor(150, 0, 0, 0));

    int tileCount = 3;
    int textureCount = tileCount * 10;
    IMesh *groundMesh = sceneManager->getGeometryCreator()->createPlaneMesh(dimension2df(1000, 1000), dimension2du(tileCount, tileCount), 0, dimension2df(textureCount, textureCount));
    groundNode = sceneManager->addMeshSceneNode(groundMesh, parent);
    groundNode->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("install/lib/gui_application/textures/grid.png"));
    groundNode->setMaterialFlag(EMF_BILINEAR_FILTER, false);
    groundNode->setMaterialFlag(EMF_TRILINEAR_FILTER, true);
    groundNode->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
    groundNode->setRotation(vector3df(90, 0, 0));
    groundNode->setPosition(vector3df(0, 0, -20));
}

void Gui3D::updateQuadcopters()
{
    std::vector<kitrokopter::APIQuadcopter*> quadcopters = api->getQuadcopters();

    for (std::vector<kitrokopter::APIQuadcopter*>::iterator it = quadcopters.begin(); it != quadcopters.end(); it++) {
        if (this->quadcopters.count((*it)->getId()) == 0) {
            this->quadcopters[(*it)->getId()] = new GUIQuadcopter(simulationNode, std::vector<double>(3), std::vector<double>(9), iw->getSceneManager());
        }

        this->quadcopters[(*it)->getId()]->setPositionVector((*it)->getCurrentPosition());

        float z = (*it)->getCurrentPosition().getZ();
        vector3df groundPosition = groundNode->getPosition();

        if (z < groundPosition.Z) {
            groundPosition.Z = z;
            groundNode->setPosition(groundPosition);
        }

        // TODO correct signs?
        this->quadcopters[(*it)->getId()]->setEulerRotation(vector3df((*it)->getStabilizerYawData(),
                                                                      (*it)->getStabilizerPitchData(),
                                                                      (*it)->getStabilizerRollData()));
    }

    #ifdef DEBUG
    vector3df position = q0->getPositionVector();
    position.Y -= 1;
    q0->setPositionVector(position);
    #endif

    repaintRequested = true;
}

void Gui3D::updateCameras()
{
    std::vector<kitrokopter::APICamera*> cameras = api->getCameras();
    cameraLookAt = vector3df();

    for (auto camera : cameras) {
        if (this->cameras.count(camera->getId()) == 0) {
            this->cameras[camera->getId()] = new GUICamera(simulationNode, "install/lib/gui_application/models/camera.3ds", std::vector<double>(3), std::vector<double>(9), iw->getSceneManager());
        }

        cameraLookAt.X += camera->getPosition().getX() / cameras.size();
        cameraLookAt.Y += camera->getPosition().getY() / cameras.size();
        cameraLookAt.Z += camera->getPosition().getZ() / cameras.size();
        this->cameras[camera->getId()]->setPositionVector(camera->getPosition());
        //this->cameras[camera->getId()]->setRotationMatrix(camera->getOrientation());
    }

    repaintRequested = true;
}

void Gui3D::mouseDragged(int deltaX, int deltaY)
{
    cameraRotation.X += deltaY * cameraPitchRotationStep;

    if (cameraRotation.X > 80) {
        cameraRotation.X = 80;
    }

    if (cameraRotation.X < -80) {
        cameraRotation.X = -80;
    }

    cameraRotation.Y += deltaX * cameraHorizontalRotationStep;

    cameraCenterNode->setPosition(cameraLookAt);
    cameraCenterNode->setRotation(cameraRotation);

    repaintRequested = true;
}

void Gui3D::zoom(int delta)
{
    vector3df position = cameraNode->getPosition();
    position.Z *= pow(cameraZoomStep, delta);

    if (position.Z < 10) {
        position.Z = 10;
    } else if (position.Z > 4000) {
        position.Z = 4000;
    }

    cameraNode->setPosition(position);

    repaintRequested = true;
}

void Gui3D::callRepaint()
{
    if (repaintRequested) {
        iw->repaint();
        repaintRequested = false;
    }
}

void Gui3D::updateShadows()
{
    for (std::pair<int, GUICamera*> camera : cameras) {
        camera.second->updateShadowVolumes();
    }

    for (std::pair<int, GUIQuadcopter*> quadcopter : quadcopters) {
        quadcopter.second->updateShadowVolumes();
    }
}
