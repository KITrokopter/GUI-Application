#include "joystickdebugdialog.hpp"
#include "ui_joystickdebugdialog.h"

#include <QMessageBox>

#include "joystick.hpp"

JoystickDebugDialog::JoystickDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoystickDebugDialog)
{
    ui->setupUi(this);

    QTableWidgetItem *numHeader, *valHeader;
    numHeader = new QTableWidgetItem("Number");
    valHeader = new QTableWidgetItem("Value");
    ui->axisTable->setHorizontalHeaderItem(0, numHeader);
    ui->buttonTable->setHorizontalHeaderItem(0, numHeader);
    ui->axisTable->setHorizontalHeaderItem(1, valHeader);
    ui->buttonTable->setHorizontalHeaderItem(1, valHeader);

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
    if (ui->axisTable->rowCount() < num)
        ui->axisTable->setRowCount(num + 1);
    QTableWidgetItem *numItem, *valItem;
    numItem = ui->axisTable->item(num, 0);
    valItem = ui->axisTable->item(num, 1);
    if (!numItem) {
        numItem = new QTableWidgetItem();
        valItem = new QTableWidgetItem();
        ui->axisTable->setItem(num, 0, numItem);
        ui->axisTable->setItem(num, 1, valItem);
    }
    numItem->setText(QVariant(num).toString());
    valItem->setText(QVariant(val).toString());
}

void JoystickDebugDialog::updateButton(int num, bool val)
{
    if (ui->buttonTable->rowCount() < num)
        ui->buttonTable->setRowCount(num + 1);
    QTableWidgetItem *numItem, *valItem;
    numItem = ui->buttonTable->item(num, 0);
    valItem = ui->buttonTable->item(num, 1);
    if (!numItem) {
        numItem = new QTableWidgetItem();
        valItem = new QTableWidgetItem();
        ui->buttonTable->setItem(num, 0, numItem);
        ui->buttonTable->setItem(num, 1, valItem);
    }
    numItem->setText(QVariant(num).toString());
    valItem->setText(QVariant(val).toString());
}
