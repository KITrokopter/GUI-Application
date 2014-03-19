#include "joystickdebugdialog.hpp"
#include "ui_joystickdebugdialog.h"

#include <QMessageBox>

#include "gamepad.hpp"

JoystickDebugDialog::JoystickDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoystickDebugDialog),
    joystick(new Gamepad(this))
{
    ui->setupUi(this);

    QTableWidgetItem *numHeader, *valHeader;
    numHeader = new QTableWidgetItem("Number");
    valHeader = new QTableWidgetItem("Value");
    ui->axisTable->setHorizontalHeaderItem(0, numHeader);
    ui->buttonTable->setHorizontalHeaderItem(0, numHeader);
    ui->axisTable->setHorizontalHeaderItem(1, valHeader);
    ui->buttonTable->setHorizontalHeaderItem(1, valHeader);

    bool open = joystick->open(0);
    if (!open) {
        QMessageBox::critical(this, "Joystick Error", "Could not open Joystick 0.");
    }

    ui->comboBox->insertItems(0, joystick->getGamepadNames().values());

    connect(joystick, SIGNAL(axisValueChanged(int,int)), this, SLOT(updateAxis(int,int)));
    connect(joystick, SIGNAL(buttonValueChanged(int,bool)), this, SLOT(updateButton(int,bool)));
}

JoystickDebugDialog::~JoystickDebugDialog()
{
    delete ui;
}

template<typename T>
void JoystickDebugDialog::updateTable(QTableWidget *table, int num, T val)
{
    if (table->rowCount() < num)
        table->setRowCount(num + 1);
    QTableWidgetItem *numItem, *valItem;
    numItem = table->item(num, 0);
    valItem = table->item(num, 1);
    if (!numItem) {
        numItem = new QTableWidgetItem();
        valItem = new QTableWidgetItem();
        table->setItem(num, 0, numItem);
        table->setItem(num, 1, valItem);
    }
    numItem->setText(QVariant(num).toString());
    valItem->setText(QVariant(val).toString());
}

void JoystickDebugDialog::updateAxis(int num, int val)
{
    updateTable(ui->axisTable, num, val);
}

void JoystickDebugDialog::updateButton(int num, bool val)
{
    updateTable(ui->buttonTable, num, val);
}
