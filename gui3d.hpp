#ifndef GUI3D_HPP
#define GUI3D_HPP

#include <QIrrlichtWidget.hpp>
#include <irrlicht/IMesh.h>

class Gui3D
{
public:
    Gui3D(QIrrlichtWidget *iw);
    void initializeIrrlicht();

private:
    QIrrlichtWidget *iw;

    // Meshes
    irr::scene::IMesh *sphere;
    irr::scene::ISceneNode *sphereNode;
};

#endif // GUI3D_HPP
