#include "guicamera.hpp"

GUICamera::GUICamera(ISceneNode *parent, const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, rotationMatrix, sceneManager)
{
    createMesh(sceneManager, meshPath);
}

GUICamera::GUICamera(ISceneNode *parent, const char* meshPath, vector3df positionVector, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, sceneManager)
{
    createMesh(sceneManager, meshPath);
}

void GUICamera::createMesh(ISceneManager *sceneManager, const char* meshPath)
{
    IAnimatedMesh *mesh = sceneManager->getMesh(meshPath);
    IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode());
    ITexture *greenTexture = sceneManager->getVideoDriver()->getTexture("install/lib/gui_application/textures/green.png");
    node->setMaterialTexture(0, greenTexture);
    node->setScale(vector3df(50, 50, 50));
    node->setRotation(vector3df(0, 90, -90));
    addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());
}
