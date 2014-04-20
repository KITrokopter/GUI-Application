#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include <QObject>
#include <QMap>
#include <QTimer>

// Fix warnings about main redefinition.
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

/**
 * Gamepad adapts the SDL gamecontroller functions for Qt.
 *
 * It uses polling with a fixed interval to check for input. The analog stick
 * axes are snapped to zero if they fall under THRESHOLD.
 *
 * Use SDL_GameControllerAddMapping if your gamepad isn't supported by SDL
 * natively.
 *
 * @see https://wiki.libsdl.org/SDL_GameControllerAddMapping
 */
class Gamepad : public QObject {
	Q_OBJECT
public:
	/// The threshold for snapping axis input to zero.
	static const int THRESHOLD = 6000;


	explicit Gamepad(QObject *parent = 0);
	~Gamepad();

	/**
	 * Returns a map of gamepad id -> gamepad name.
	 */
	QMap<int, QString> getGamepadNames();

	/**
	 * Opens the gamepad with the given id.
	 */
	bool open(int);

	/**
	 * Closes the gamepad which is currently opened.
	 *
	 * Doesn't do anything if there is no opened gamepad.
	 */
	void close();

signals:
	/**
	 * Signals a change in a single axis value.
	 *
	 * @param axis The axis identifier, see the SDL enum.
	 * @param value The new axis value, which is a signed 16bit integer.
	 */
	void axisValueChanged(int axis, int value);

	/**
	 * Signals a change in a button value.
	 *
	 * @param button The button identifier, see the SDL enum.
	 * @param value The new button status.
	 */
	void buttonValueChanged(int button, bool value);

private slots:
	void eventTick();

private:
	SDL_GameController *controller;
	QTimer timer;

	QMap<SDL_GameControllerAxis, Sint16> axes;
	QMap<SDL_GameControllerButton, Uint8> buttons;
};

#endif // GAMEPAD_HPP
