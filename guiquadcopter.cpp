#include "guiquadcopter.hpp"

GUIQuadcopter::GUIQuadcopter(ISceneNode *parent, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, rotationMatrix, sceneManager)
{
    createMesh(sceneManager);
}

GUIQuadcopter::GUIQuadcopter(ISceneNode *parent, vector3df positionVector, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, sceneManager)
{
    createMesh(sceneManager);
}

void GUIQuadcopter::createMesh(ISceneManager *sceneManager)
{
    IAnimatedMesh *mesh = sceneManager->addSphereMesh("Sphere", 20);
    IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode());
    addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());

    mesh = sceneManager->addArrowMesh("Arrow", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 160, 140, 4, 12);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(-75, 0, 0));
    node->setRotation(vector3df(90, 90, 0));
    //addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());

    mesh = sceneManager->addArrowMesh("Cylinder", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 150, 149.999f, 4, 4);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(0, -75, 0));
    node->setRotation(vector3df(0, 90, 0));
    //addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());

    mesh = sceneManager->addArrowMesh("Support", SColor(255, 100, 100, 150), SColor(255, 100, 100, 150), 4, 8, 10000, 9999, 3, 3);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getRotationFreeSceneNode(), -1, vector3df(0, 0, 0));
    node->setRotation(vector3df(-90, 0, 0));
    addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());

    getRotationFreeSceneNode()->setScale(vector3df(1.5, 1.5, 1.5));
}
