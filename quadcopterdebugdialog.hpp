#ifndef QUADCOPTERDEBUGDIALOG_HPP
#define QUADCOPTERDEBUGDIALOG_HPP

#include <QDialog>

#include "quadcoptermodel.hpp"

namespace Ui {
class QuadcopterDebugDialog;
}

/**
 * Shows all quadcopter data in a single table.
 *
 * @see QuadcopterModel
 */
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
