#ifndef FORM_H
#define FORM_H

#include "Satelite.h"

#include <QtCharts>
#include <QTimer>
#include <QWidget>

namespace Ui {
class form;
}

class form : public QWidget
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr);
    ~form();

private:
    Ui::form *ui;
    QTimer *timer;
    QChart *chart;
    QLineSeries *series;
    Satelite *satelite;
    double totalTime;
    double timerInterval;
    void updateStatus();

private slots:
    void updateGraph();
    void on_start_clicked();
    void on_stop_clicked();
};

#endif // FORM_H
