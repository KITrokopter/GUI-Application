#include "guiquadcopter.hpp"

GUIQuadcopter::GUIQuadcopter(ISceneNode *parent, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, rotationMatrix, sceneManager)
{
    IAnimatedMesh *mesh = sceneManager->addSphereMesh("Sphere", 20);
    IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode());
    node->addShadowVolumeSceneNode()->updateShadowVolumes();

    mesh = sceneManager->addArrowMesh("Arrow", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 110, 83, 4, 6);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(-50, 0, 0));
    node->setRotation(vector3df(90, 90, 0));
    node->addShadowVolumeSceneNode()->updateShadowVolumes();

    mesh = sceneManager->addArrowMesh("Cylinder", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 100, 99.999f, 4, 4);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(0, -50, 0));
    node->setRotation(vector3df(0, 90, 0));
    node->addShadowVolumeSceneNode()->updateShadowVolumes();

    mesh = sceneManager->addArrowMesh("Support", SColor(255, 100, 100, 150), SColor(255, 100, 100, 150), 4, 8, 10000, 9999, 3, 3);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(0, 0, 0));
    node->setRotation(vector3df(-90, 0, 0));
    node->addShadowVolumeSceneNode()->updateShadowVolumes();
}
