#include "quadcopterdebugdialog.hpp"
#include "ui_quadcopterdebugdialog.h"

QuadcopterDebugDialog::QuadcopterDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuadcopterDebugDialog)
{
    ui->setupUi(this);
}

QuadcopterDebugDialog::~QuadcopterDebugDialog()
{
    delete ui;
}

void QuadcopterDebugDialog::setModel(QuadcopterModel *model)
{
    ui->tableView->setModel(model);
}
