#define __STDC_LIMIT_MACROS 1
#include "movementcontroller.hpp"

#include "API.hpp"

#include <SDL2/SDL_gamecontroller.h>

MovementController::MovementController(kitrokopter::API *api, QObject *parent) :
    QObject(parent),
    api(api)
{
}

QVector3D MovementController::movementVector()
{
    return QVector3D((float)xmov / INT16_MAX, (float)ymov / INT16_MAX, (float)zmov / INT16_MAX);
}

void MovementController::notifyAPI()
{
    auto vector = movementVector();
    api->moveFormation(kitrokopter::Vector(vector.x(), vector.y(), vector.z()));

    if (rot) {
        // TODO: directional turning
        api->rotateFormation();
    }
}

/*
 * Axis bindings:
 *
 *  - Left analog stick controls x/y.
 *  - Right analog stick controls z, i.e. up/down.
 *  - Left trigger rotates counterclockwise, right trigger clockwise.
 */
void MovementController::axisValueChanged(int axis, int value)
{
    switch (axis) {
    case SDL_CONTROLLER_AXIS_LEFTX:
        xmov = value;
        break;
    case SDL_CONTROLLER_AXIS_LEFTY:
        ymov = value;
        break;
    case SDL_CONTROLLER_AXIS_RIGHTY:
        zmov = value;
        break;
    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
        rot = -value;
        break;
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        rot = +value;
        break;
    }

    notifyAPI();
}

/*
 * No button bindings at the moment.
 */
void MovementController::buttonValueChanged(int, bool)
{
    notifyAPI();
}
