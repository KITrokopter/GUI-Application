#include "quadcopterdetaildialog.hpp"
#include "ui_quadcopterdetaildialog.h"

#include <QLabel>

QuadcopterDetailDialog::QuadcopterDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuadcopterDetailDialog)
{
    ui->setupUi(this);
}

QuadcopterDetailDialog::~QuadcopterDetailDialog()
{
    delete ui;
}

void QuadcopterDetailDialog::setSourceModel(QuadcopterModel *model, int row)
{
    this->model = model;
    this->row = row;
    renderModel();
}

void QuadcopterDetailDialog::renderModel()
{
    int labelnum;
    for (int col = 0; col < model->columnCount(QModelIndex()); ++col) {
        labelnum = col * 2;
        QLabel *label, *content;
        if (labelnum < ui->attributes->count()) {
            label = dynamic_cast<QLabel*>(ui->attributes->itemAt(labelnum)->widget());
            content = dynamic_cast<QLabel*>(ui->attributes->itemAt(labelnum + 1)->widget());
        } else {
            label = new QLabel(this);
            content = new QLabel(this);
            ui->attributes->addWidget(label);
            ui->attributes->addWidget(content);
        }
        QModelIndex index = model->index(row, col);
        label->setText(model->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString());
        content->setText(model->data(index, Qt::DisplayRole).toString());
    }
}
