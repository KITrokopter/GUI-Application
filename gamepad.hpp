#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include <QObject>
#include <QMap>
#include <QTimer>
#include <SDL2/SDL.h>

class Gamepad : public QObject
{
    Q_OBJECT
public:
    /// The threshold for snapping axis input to zero.
    static const int THRESHOLD = 6000;


    explicit Gamepad(QObject *parent = 0);
    ~Gamepad();

    QMap<int, QString> getGamepadNames();

    bool open(int);
    void close();

signals:
    void axisValueChanged(int axis, int value);
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
