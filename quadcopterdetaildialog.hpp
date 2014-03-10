#ifndef QUADCOPTERDETAILDIALOG_HPP
#define QUADCOPTERDETAILDIALOG_HPP

#include <QDialog>
#include <quadcoptermodel.hpp>

namespace Ui {
class QuadcopterDetailDialog;
}

class QuadcopterDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuadcopterDetailDialog(QWidget *parent = 0);
    ~QuadcopterDetailDialog();

    void setSourceModel(QuadcopterModel *model, int row);

private slots:
    void renderModel();

private:
    Ui::QuadcopterDetailDialog *ui;

    QuadcopterModel *model;
    int row;
};

#endif // QUADCOPTERDETAILDIALOG_HPP
