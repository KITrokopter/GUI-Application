#ifndef QUADCOPTERDETAILDIALOG_HPP
#define QUADCOPTERDETAILDIALOG_HPP

#include <QDialog>
#include "quadcoptermodel.hpp"

#include "APIQuadcopterListener.hpp"

namespace Ui {
class QuadcopterDetailDialog;
}

namespace kitrokopter {
class APIQuadcopter;
}

class QuadcopterDetailDialog : public QDialog, public kitrokopter::APIQuadcopterListener
{
    Q_OBJECT

public:
    explicit QuadcopterDetailDialog(QWidget *parent = 0);
    ~QuadcopterDetailDialog();

    void setSourceModel(QuadcopterModel *model, kitrokopter::APIQuadcopter *quadcopter);
    void updateQuadcopterValues(kitrokopter::APIQuadcopterUpdateEvent e);

private slots:
    void renderModel();

    // Input slots
    void setFlightSelection(bool);
    void blink();

private:
    Ui::QuadcopterDetailDialog *ui;

    QuadcopterModel *model;
    kitrokopter::APIQuadcopter *quadcopter;
};

#endif // QUADCOPTERDETAILDIALOG_HPP
