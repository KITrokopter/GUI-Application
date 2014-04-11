#include "gamepad.hpp"

#include <exception>

Gamepad::Gamepad(QObject *parent) :
	QObject(parent),
	controller(NULL)
{
	if (SDL_Init(SDL_INIT_GAMECONTROLLER)) {
		throw SDL_GetError();
	}
	connect(&timer, SIGNAL(timeout()), this, SLOT(eventTick()));
}

Gamepad::~Gamepad()
{
	close();
}

QMap<int, QString> Gamepad::getGamepadNames()
{
	QMap<int, QString> map;
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			map.insert(i, SDL_GameControllerNameForIndex(i));
		}
	}
	return map;
}

bool Gamepad::open(int pad)
{
	if (controller) {
		close();
	}

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
	if (controller) {
		SDL_GameControllerClose(controller);
	}
	controller = NULL;
}

void Gamepad::eventTick()
{
	if (!controller) {
		return;
	}

	SDL_GameControllerUpdate();

	for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++) {
		SDL_GameControllerAxis axis = (SDL_GameControllerAxis)i;
		Sint16 pos = SDL_GameControllerGetAxis(controller, axis);
		// Snap axis to 0 for the two analog sticks, but not for the triggers.
		if (abs(pos) < THRESHOLD && axis < SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
			pos = 0;
		}
		if (pos != axes[axis]) {
			emit axisValueChanged(axis, pos);
		}
		axes[axis] = pos;
	}

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
		SDL_GameControllerButton button = (SDL_GameControllerButton)i;
		Uint8 status = SDL_GameControllerGetButton(controller, button);
		if (status != buttons[button]) {
			emit buttonValueChanged(button, (bool)status);
		}
		buttons[button] = status;
	}
}

