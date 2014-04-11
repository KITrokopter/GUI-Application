#include "gamepaddebugdialog.hpp"
#include "ui_gamepaddebugdialog.h"

#include "gamepad.hpp"

GamepadDebugDialog::GamepadDebugDialog(QWidget *parent, Gamepad *gamepad) :
	QDialog(parent),
	ui(new Ui::GamepadDebugDialog),
	gamepad(gamepad)
{
	ui->setupUi(this);

	QTableWidgetItem numHeader("Number"), valHeader("Value");
	ui->axisTable->setHorizontalHeaderItem(0, new QTableWidgetItem(numHeader));
	ui->axisTable->setHorizontalHeaderItem(1, new QTableWidgetItem(valHeader));
	ui->buttonTable->setHorizontalHeaderItem(0, new QTableWidgetItem(numHeader));
	ui->buttonTable->setHorizontalHeaderItem(1, new QTableWidgetItem(valHeader));

	QMap<int, QString> names = gamepad->getGamepadNames();
	for (QMap<int, QString>::const_iterator it = names.constBegin(); it != names.constEnd(); ++it) {
		ui->comboBox->addItem(it.value(), it.key());
	}

	connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(openGamepad(int)));
	connect(gamepad, SIGNAL(axisValueChanged(int,int)), this, SLOT(updateAxis(int,int)));
	connect(gamepad, SIGNAL(buttonValueChanged(int,bool)), this, SLOT(updateButton(int,bool)));
}

GamepadDebugDialog::~GamepadDebugDialog()
{
	delete ui;
}

void GamepadDebugDialog::openGamepad(int comboBoxId)
{
	gamepad->open(ui->comboBox->itemData(comboBoxId).toInt());
}

template<typename T>
void GamepadDebugDialog::updateTable(QTableWidget *table, int num, T val)
{
	if (table->rowCount() < num) {
		table->setRowCount(num + 1);
	}
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

void GamepadDebugDialog::updateAxis(int num, int val)
{
	updateTable(ui->axisTable, num, val);
}

void GamepadDebugDialog::updateButton(int num, bool val)
{
	updateTable(ui->buttonTable, num, val);
}

