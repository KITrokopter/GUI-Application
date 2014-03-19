#include "joystickdebugdialog.hpp"
#include "ui_joystickdebugdialog.h"

#include "gamepad.hpp"

JoystickDebugDialog::JoystickDebugDialog(QWidget *parent, Gamepad *gamepad) :
    QDialog(parent),
    ui(new Ui::JoystickDebugDialog),
    joystick(gamepad)
{
    ui->setupUi(this);

    QTableWidgetItem *numHeader, *valHeader;
    numHeader = new QTableWidgetItem("Number");
    valHeader = new QTableWidgetItem("Value");
    ui->axisTable->setHorizontalHeaderItem(0, numHeader);
    ui->buttonTable->setHorizontalHeaderItem(0, numHeader);
    ui->axisTable->setHorizontalHeaderItem(1, valHeader);
    ui->buttonTable->setHorizontalHeaderItem(1, valHeader);

    QMap<int, QString> names = joystick->getGamepadNames();
    for (QMap<int, QString>::const_iterator it = names.constBegin(); it != names.constEnd(); ++it) {
        ui->comboBox->addItem(it.value(), it.key());
    }

    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(openGamepad(int)));
    connect(joystick, SIGNAL(axisValueChanged(int,int)), this, SLOT(updateAxis(int,int)));
    connect(joystick, SIGNAL(buttonValueChanged(int,bool)), this, SLOT(updateButton(int,bool)));
}

JoystickDebugDialog::~JoystickDebugDialog()
{
    delete ui;
}

void JoystickDebugDialog::openGamepad(int comboBoxId)
{
    joystick->open(ui->comboBox->itemData(comboBoxId).toInt());
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
