#pragma once
#include <QWidget>
#include <QPushButton>
#include "Service.h"
#include "BarChart.h"

class StartWindow : public QWidget {
	Q_OBJECT
private:
	Service& service;
	QPushButton* admin_mode;
	QPushButton* user_mode;
	QPushButton* exit_button;
	QPushButton* chart_button;
public:
	StartWindow(Service& s);
	void init();
private slots:
	void launch_admin_mode();
	void launch_user_mode();
	void launch_chart();

};