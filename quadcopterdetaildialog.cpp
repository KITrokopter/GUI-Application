#include "quadcopterdetaildialog.hpp"
#include "ui_quadcopterdetaildialog.h"

#include "APIQuadcopter.hpp"

#include <QLabel>

QuadcopterDetailDialog::QuadcopterDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuadcopterDetailDialog),
    model(NULL)
{
    ui->setupUi(this);
}

QuadcopterDetailDialog::~QuadcopterDetailDialog()
{
    delete ui;

    if (quadcopter)
        quadcopter->removeQuadcopterListener(this);
}

void QuadcopterDetailDialog::setSourceModel(QuadcopterModel *model, kitrokopter::APIQuadcopter *quadcopter)
{
    if (this->model)
        disconnect(this->model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(renderModel()));
    if (this->quadcopter)
        this->quadcopter->removeQuadcopterListener(this);
    this->model = model;
    this->quadcopter = quadcopter;
    renderModel();
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(renderModel()));
    quadcopter->addQuadcopterListener(this);
}

void QuadcopterDetailDialog::renderModel()
{
    int labelnum;
    int row = model->rowFor(quadcopter);
    for (int col = 0; col < model->columnCount(QModelIndex()); ++col) {
        labelnum = col * 2;
        QLabel *label, *content;
        if (labelnum < ui->attributes->count()) {
            label = dynamic_cast<QLabel*>(ui->attributes->itemAt(labelnum)->widget());
            content = dynamic_cast<QLabel*>(ui->attributes->itemAt(labelnum + 1)->widget());
        } else {
            label = new QLabel(this);
            content = new QLabel(this);
            ui->attributes->addWidget(label, col, 0);
            ui->attributes->addWidget(content, col, 1);
        }
        QModelIndex index = model->index(row, col);
        label->setText(model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString());
        content->setText(model->data(index, Qt::DisplayRole).toString());
    }

    // Set Dialog title to the quadcopter's name.
    setWindowTitle(QString("%1 Status").arg(model->data(model->index(row, 0)).toString()));
}

void QuadcopterDetailDialog::updateQuadcopterValues(kitrokopter::APIQuadcopterUpdateEvent e)
{
    renderModel();
}

void QuadcopterDetailDialog::setFlightSelection(bool select)
{
    quadcopter->setSelectedForFlight(select);
}

void QuadcopterDetailDialog::blink()
{
    quadcopter->blink();
}
