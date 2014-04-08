#ifndef GUICAMERA_H
#define GUICAMERA_H

#include "guiobject.hpp"

class GUICamera : public GUIObject
{
public:
    GUICamera(ISceneNode *parent, const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager);
    GUICamera(ISceneNode *parent, const char* meshPath, vector3df positionVector, ISceneManager *sceneManager);

protected:
    void createMesh(ISceneManager *sceneManager, const char* meshPath);
};

#endif // GUICAMERA_H
