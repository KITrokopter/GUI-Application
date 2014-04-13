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

/**
 * Shows detail information for a single quadcopter.
 *
 * Additionally, allows setting tracking colors, blinking and flight selection.
 */
class QuadcopterDetailDialog : public QDialog, public kitrokopter::APIQuadcopterListener {
	Q_OBJECT

public:
	explicit QuadcopterDetailDialog(QWidget *parent = 0);
	~QuadcopterDetailDialog();

	void setSourceModel(QuadcopterModel *model, kitrokopter::APIQuadcopter *quadcopter);
	void updateQuadcopterValues(kitrokopter::APIQuadcopterUpdateEvent e);

private slots:
	void renderModel();

	// Input slots
	void selectMinColor();
	void selectMaxColor();
	void setFlightSelection(bool);
	void blink();

private:
	Ui::QuadcopterDetailDialog *ui;

	QuadcopterModel *model;
	kitrokopter::APIQuadcopter *quadcopter;
};

#endif // QUADCOPTERDETAILDIALOG_HPP
