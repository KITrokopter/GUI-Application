#include "gamepad.hpp"

#include <exception>

Gamepad::Gamepad(QObject *parent) :
    QObject(parent),
    controller(NULL)
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER)) {
        throw SDL_GetError();
    }
    SDL_GameControllerAddMapping("5e048e02000000000000504944564944,XBOX 360 For Windows (Controller),platform:Windows,x:b2,a:b0,b:b1,y:b3,back:b6,start:b7,dpleft:h0.8,dpdown:h0.0,dpdown:h0.4,dpright:h0.0,dpright:h0.2,dpup:h0.0,dpup:h0.1,leftshoulder:h0.0,leftshoulder:b4,lefttrigger:a2,rightshoulder:b5,dpup:h0.1,leftshoulder:h0.0,leftshoulder:b4,lefttrigger:a2,rightshoulder:b5,leftstick:b8,rightstick:b9,leftx:a0,lefty:a1,rightx:a3,righty:a4,");
    connect(&timer, SIGNAL(timeout()), this, SLOT(eventTick()));
}

Gamepad::~Gamepad()
{
    close();
}

QMap<int, QString> Gamepad::getGamepadNames()
{
    QMap<int, QString> map;
    for (int i = 0; i < SDL_NumJoysticks(); i++)
        if (SDL_IsGameController(i))
            map.insert(i, SDL_GameControllerNameForIndex(i));
    return map;
}

bool Gamepad::open(int pad)
{
    if (controller)
        close();

    controller = SDL_GameControllerOpen(pad);
    if (controller) {
        timer.start(25);
        return true;
    } else {
        return false;
    }
}

void Gamepad::close()
{
    timer.stop();
    if (controller)
        SDL_GameControllerClose(controller);
    controller = NULL;
}

void Gamepad::eventTick()
{
    if (!controller) return;

    SDL_GameControllerUpdate();

    for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++) {
        SDL_GameControllerAxis axis = (SDL_GameControllerAxis)i;
        Sint16 pos = SDL_GameControllerGetAxis(controller, axis);
        if (pos != axes[axis])
            emit axisValueChanged(axis, pos);
        axes[axis] = pos;
    }

    for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
        SDL_GameControllerButton button = (SDL_GameControllerButton)i;
        Uint8 status = SDL_GameControllerGetButton(controller, button);
        if (status != buttons[button])
            emit buttonValueChanged(button, (bool)status);
        buttons[button] = status;
    }
}
