#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    quadcopterModel(new QuadcopterModel),
    quadcopterDebugDialog(0)
{
    ui->setupUi(this);

    connect(ui->actionQuadcopters, SIGNAL(triggered()), this, SLOT(openQuadcopterDebugDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete quadcopterModel;
    if (quadcopterDebugDialog)
        delete quadcopterDebugDialog;
}

void MainWindow::openQuadcopterDebugDialog()
{
    if (!quadcopterDebugDialog) {
        quadcopterDebugDialog = new QuadcopterDebugDialog(this);
        quadcopterDebugDialog->setModel(quadcopterModel);
    }
    quadcopterDebugDialog->show();
    quadcopterDebugDialog->raise();
    quadcopterDebugDialog->activateWindow();
}
