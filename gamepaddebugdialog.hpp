#ifndef GAMEPADDEBUGDIALOG_HPP
#define GAMEPADDEBUGDIALOG_HPP

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class GamepadDebugDialog;
}

class Gamepad;

class GamepadDebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GamepadDebugDialog(QWidget *parent, Gamepad *gamepad);
    ~GamepadDebugDialog();

private slots:
    void openGamepad(int);
    void updateAxis(int, int);
    void updateButton(int, bool);

private:
    Ui::GamepadDebugDialog *ui;

    Gamepad *gamepad;

    template<typename T>
    void updateTable(QTableWidget *table, int num, T val);
};

#endif // GAMEPADDEBUGDIALOG_HPP
