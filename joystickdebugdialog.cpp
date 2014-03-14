#include "joystickdebugdialog.hpp"
#include "ui_joystickdebugdialog.h"

#include <QMessageBox>

#include "joystick.hpp"

JoystickDebugDialog::JoystickDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoystickDebugDialog)
{
    ui->setupUi(this);

    Joystick *joystick = new Joystick(this);
    bool open = joystick->open(0);
    if (!open) {
        QMessageBox::critical(this, "Joystick Error", "Could not open Joystick 0.");
    }

    connect(joystick, SIGNAL(axisValueChanged(int,int)), this, SLOT(updateAxis(int,int)));
    connect(joystick, SIGNAL(buttonValueChanged(int,bool)), this, SLOT(updateButton(int,bool)));
}

JoystickDebugDialog::~JoystickDebugDialog()
{
    delete ui;
}

void JoystickDebugDialog::updateAxis(int num, int val)
{
    ui->axisNum->setText(QVariant(num).toString());
    ui->axisVal->setText(QVariant(val).toString());
}

void JoystickDebugDialog::updateButton(int num, bool val)
{
    ui->buttonNum->setText(QVariant(num).toString());
    ui->buttonVal->setText(QVariant(val).toString());
}
