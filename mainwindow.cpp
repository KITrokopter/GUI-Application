#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "quadcoptermodel.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QuadcopterModel *model = new QuadcopterModel();
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
