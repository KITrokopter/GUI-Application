#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    quadcopterModel(new QuadcopterModel(this)),
    quadcopterDebugDialog(0),
    trackedFilter(new QuadcopterTrackedFilter(this)),
    untrackedFilter(new QuadcopterTrackedFilter(this))
{
    ui->setupUi(this);

    trackedFilter->setSourceModel(quadcopterModel);
    untrackedFilter->setSourceModel(quadcopterModel);
    trackedFilter->filterTracked();
    untrackedFilter->filterUntracked();
    ui->trackedList->setModel(trackedFilter);
    ui->untrackedList->setModel(untrackedFilter);

    connect(ui->actionQuadcopters, SIGNAL(triggered()), this, SLOT(openQuadcopterDebugDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
