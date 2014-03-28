#include "guicamera.hpp"

GUICamera::GUICamera(ISceneNode *parent, const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(parent, positionVector, rotationMatrix, sceneManager)
{
    ISceneNode *node = sceneManager->addMeshSceneNode(sceneManager->getMesh(meshPath), getSceneNode());
    // ITexture *greenTexture = sceneManager->getVideoDriver()->getTexture("install/lib/gui_application/textures/green.png");
    // node->setMaterialTexture(0, greenTexture);
    node->setScale(vector3df(50, 50, 50));
    node->setRotation(vector3df(0, 90, 0));
}
