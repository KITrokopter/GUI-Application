#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "quadcopterdetaildialog.hpp"
#include "joystickdebugdialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    quadcopterModel(new QuadcopterModel(this)),
    quadcopterDebugDialog(0),
    trackedFilter(new QuadcopterTrackedFilter(this)),
    untrackedFilter(new QuadcopterTrackedFilter(this)),
    calibrationDialog(0)
{
    ui->setupUi(this);

    trackedFilter->setSourceModel(quadcopterModel);
    untrackedFilter->setSourceModel(quadcopterModel);
    trackedFilter->filterTracked();
    untrackedFilter->filterUntracked();
    ui->trackedList->setModel(trackedFilter);
    ui->untrackedList->setModel(untrackedFilter);

    connect(ui->actionQuadcopters, SIGNAL(triggered()), this, SLOT(openQuadcopterDebugDialog()));
    connect(ui->trackedList, SIGNAL(activated(QModelIndex)), this, SLOT(openQuadcopterDetailDialog(QModelIndex)));
    connect(ui->untrackedList, SIGNAL(activated(QModelIndex)), this, SLOT(openQuadcopterDetailDialog(QModelIndex)));

    connect(ui->calibrateCamerasButton, SIGNAL(clicked()), this, SLOT(openCalibrationDialog()));

    connect(ui->actionJoystick, SIGNAL(triggered()), this, SLOT(openJoystickDebugDialog()));
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

void MainWindow::openQuadcopterDetailDialog(const QModelIndex &index)
{
    QuadcopterDetailDialog *dialog = new QuadcopterDetailDialog(this);
    dialog->setSourceModel(index.model(), index.row());
    dialog->resize(dialog->minimumSize());
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MainWindow::openCalibrationDialog()
{
    if (!calibrationDialog) {
        calibrationDialog = new CalibrationDialog(this);
    }
    calibrationDialog->show();
    calibrationDialog->raise();
    calibrationDialog->activateWindow();
}

void MainWindow::openJoystickDebugDialog()
{
    JoystickDebugDialog *dialog = new JoystickDebugDialog(this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
