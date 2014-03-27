#include "guiquadcopter.hpp"

GUIQuadcopter::GUIQuadcopter(const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager)
    : GUIObject(positionVector, rotationMatrix, sceneManager)
{
    // getSceneNode()->setMesh(sceneManager->getMesh(meshPath));
    ISceneNode *node = sceneManager->addMeshSceneNode(sceneManager->getGeometryCreator()->createSphereMesh(), getSceneNode());
    ITexture *greenTexture = sceneManager->getVideoDriver()->getTexture("install/lib/gui_application/textures/green.png");
    node->setMaterialTexture(0, greenTexture);
}