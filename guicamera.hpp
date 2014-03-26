#ifndef GUICAMERA_H
#define GUICAMERA_H

#include "guiobject.hpp"

class GUICamera : public GUIObject
{
public:
    GUICamera(const char* meshPath, std::vector<double> positionVector, std::vector<double> rotationMatrix, ISceneManager *sceneManager);
};

#endif // GUICAMERA_H
