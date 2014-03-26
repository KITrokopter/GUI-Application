#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "aboutdialog.hpp"
#include "calibrationdialog.hpp"
#include "gamepaddebugdialog.hpp"
#include "gamepad.hpp"
#include "movementcontroller.hpp"
#include "quadcopterdebugdialog.hpp"
#include "quadcopterdetaildialog.hpp"
#include "quadcoptermodel.hpp"
#include "quadcoptertrackedfilter.hpp"

#include "QIrrlichtWidget.hpp"
#include "gui3d.hpp"

#include "API.hpp"
#include "APICameraSystem.hpp"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, kitrokopter::API *api) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    api(api),
    gamepad(new Gamepad(this)),
    quadcopterModel(new QuadcopterModel(this, api)),
    quadcopterDebugDialog(0),
    trackedFilter(new QuadcopterTrackedFilter(this)),
    untrackedFilter(new QuadcopterTrackedFilter(this)),
    calibrationDialog(0)
{
    ui->setupUi(this);

    ui->mainToolBar->hide();

    initGamepad();

    trackedFilter->setSourceModel(quadcopterModel);
    untrackedFilter->setSourceModel(quadcopterModel);
    trackedFilter->filterTracked();
    untrackedFilter->filterUntracked();
    ui->trackedList->setModel(trackedFilter);
    ui->untrackedList->setModel(untrackedFilter);

    irrlichtWidget = new QIrrlichtWidget(ui->superWidget);
    irrlichtWidget->setMinimumSize(QSize(640, 480));
    ui->superWidget->layout()->addWidget(irrlichtWidget);
    gui3d = new Gui3D(irrlichtWidget);

    connect(ui->launchButton, SIGNAL(clicked()), this, SLOT(launch()));
    connect(ui->deleteCalibrationButton, SIGNAL(clicked()), this, SLOT(deleteCalibration()));
    connect(ui->loadFormationButton, SIGNAL(clicked()), this, SLOT(loadFormation()));
    connect(ui->scanButton, SIGNAL(clicked()), this, SLOT(scanForQuadcopters()));
    connect(ui->actionShutdown_everything, SIGNAL(triggered()), this, SLOT(shutdownEverything()));

    connect(ui->actionQuadcopters, SIGNAL(triggered()), this, SLOT(openQuadcopterDebugDialog()));
    connect(ui->trackedList, SIGNAL(activated(QModelIndex)), this, SLOT(openQuadcopterDetailDialog(QModelIndex)));
    connect(ui->untrackedList, SIGNAL(activated(QModelIndex)), this, SLOT(openQuadcopterDetailDialog(QModelIndex)));

    connect(ui->calibrateCamerasButton, SIGNAL(clicked()), this, SLOT(openCalibrationDialog()));

    connect(ui->actionGamepad, SIGNAL(triggered()), this, SLOT(openGamepadDebugDialog()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
}

void MainWindow::initializeIrrlicht()
{
    gui3d->initializeIrrlicht();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Tries to open the first available gamepad, displaying an error message if this isn't possible.
 */
void MainWindow::initGamepad()
{
    QMap<int, QString> gamepads = gamepad->getGamepadNames();
    if (gamepads.empty()) {
        QMessageBox::critical(this, "Gamepad Error", "No suitable gamepad found.");
    } else {
        QMap<int, QString>::const_iterator it = gamepads.constBegin();
        gamepad->open(it.key());
        ui->statusBar->showMessage(QString("Gamepad %1 connected.").arg(it.value()));
    }
    // Wire up the movement controller.
    MovementController *ctrl = new MovementController(this);
    connect(gamepad, SIGNAL(axisValueChanged(int,int)), ctrl, SLOT(axisValueChanged(int,int)));
    connect(gamepad, SIGNAL(buttonValueChanged(int,bool)), ctrl, SLOT(buttonValueChanged(int,bool)));
}

void MainWindow::launch()
{
    api->launchQuadcopters(ui->launchHeightSpinBox->value());
}

void MainWindow::deleteCalibration()
{
    // TODO: This API call does not seem to exist.
    //api->getCameraSystem()->deleteFormation();
}

void MainWindow::loadFormation()
{
    // TODO: How to load a formation?
}

void MainWindow::scanForQuadcopters()
{
    api->scanChannels();
}

void MainWindow::shutdownEverything()
{
    api->shutdownSystem();
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
    dialog->setSourceModel(quadcopterModel, quadcopterModel->quadcopterFor(index.row()));
    dialog->resize(dialog->minimumSize());
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MainWindow::openCalibrationDialog()
{
    if (!calibrationDialog) {
        calibrationDialog = new CalibrationDialog(this, api->getCameraSystem());
    }
    calibrationDialog->show();
    calibrationDialog->raise();
    calibrationDialog->activateWindow();
}

void MainWindow::openGamepadDebugDialog()
{
    GamepadDebugDialog *dialog = new GamepadDebugDialog(this, gamepad);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MainWindow::openAboutDialog()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
