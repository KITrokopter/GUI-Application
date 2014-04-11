#ifndef QUADCOPTERDEBUGDIALOG_HPP
#define QUADCOPTERDEBUGDIALOG_HPP

#include <QDialog>

#include "quadcoptermodel.hpp"

namespace Ui {
class QuadcopterDebugDialog;
}

class QuadcopterDebugDialog : public QDialog {
	Q_OBJECT

public:
	explicit QuadcopterDebugDialog(QWidget *parent = 0);
	~QuadcopterDebugDialog();

	void setModel(QuadcopterModel *model);

private:
	Ui::QuadcopterDebugDialog *ui;
};

#endif // QUADCOPTERDEBUGDIALOG_HPP
