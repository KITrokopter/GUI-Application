#ifndef GAMEPADDEBUGDIALOG_HPP
#define GAMEPADDEBUGDIALOG_HPP

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class GamepadDebugDialog;
}

class Gamepad;

/**
 * The gamepad debug dialog allows testing the controller binding as well as
 * selecting which controller should be used.
 *
 * @see Gamepad
 */
class GamepadDebugDialog : public QDialog {
	Q_OBJECT

public:
	/**
	 * Constructs a gamepad debug dialog for the given gamepad.
	 */
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
