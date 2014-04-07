#include "guiquadcopter.hpp"

GUIQuadcopter::GUIQuadcopter(ISceneNode *parent, const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, rotationMatrix, sceneManager)
{
    IAnimatedMesh *mesh = sceneManager->addSphereMesh("Sphere", 10);
    IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode());
    node->addShadowVolumeSceneNode(mesh);

    mesh = sceneManager->addArrowMesh("Arrow", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 40, 33, 4, 6);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(-20, 0, 0));
    node->setRotation(vector3df(90, 90, 0));
    node->addShadowVolumeSceneNode(mesh);

    mesh = sceneManager->addArrowMesh("Cylinder", SColor(255, 255, 0, 255), SColor(255, 255, 0, 255), 4, 8, 40, 39.999f, 4, 4);
    node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode(), -1, vector3df(0, -20, 0));
    node->setRotation(vector3df(0, 90, 0));
    node->addShadowVolumeSceneNode(mesh);
}
