#ifndef JOYSTICKDEBUGDIALOG_HPP
#define JOYSTICKDEBUGDIALOG_HPP

#include <QDialog>

namespace Ui {
class JoystickDebugDialog;
}

class JoystickDebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JoystickDebugDialog(QWidget *parent = 0);
    ~JoystickDebugDialog();

private slots:
    void updateAxis(int, int);
    void updateButton(int, bool);

private:
    Ui::JoystickDebugDialog *ui;
};

#endif // JOYSTICKDEBUGDIALOG_HPP
