#include "guicamera.hpp"
#include "lib/CQtReadFile.h"

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
    auto meshFile = new CQtReadFile(meshPath);
    IAnimatedMesh *mesh = sceneManager->getMesh(meshFile);
    meshFile->drop();
    IAnimatedMeshSceneNode *node = sceneManager->addAnimatedMeshSceneNode(mesh, getSceneNode());
    auto texture = new CQtReadFile(":/3d/textures/green.png");
    ITexture *greenTexture = sceneManager->getVideoDriver()->getTexture(texture);
    texture->drop();
    node->setMaterialTexture(0, greenTexture);
    node->setScale(vector3df(50, 50, 50));
    node->setRotation(vector3df(0, 90, -90));
    addShadowVolumeSceneNode(node->addShadowVolumeSceneNode());
}
