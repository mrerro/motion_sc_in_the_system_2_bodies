#include "form.h"
#include "ui_form.h"

using namespace QtCharts;

form::form(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::form)
{
	ui->setupUi(this);
    timerInterval = 10;
    timer = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    timer->setInterval(timerInterval); // Задаем интервал таймера
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGraph())); // Подключаем сигнал таймера к нашему слоту

    /*QLineSeries *series0 = new QLineSeries();
	QLineSeries *series1 = new QLineSeries();

	*series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
		<< QPointF(16, 7) << QPointF(18, 5);
	*series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
		<< QPointF(16, 4) << QPointF(18, 3);

	QAreaSeries *series = new QAreaSeries(series0, series1);
	series->setName("Batman");
	QPen pen(0x059605);
	pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
	gradient.setColorAt(0.0, 0x3cc63c);
	gradient.setColorAt(1.0, 0x26f626);
	gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);*/
    series = new QLineSeries();
    planet1 = new QScatterSeries();
    planet2 = new QScatterSeries();

    chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(planet1);
    chart->addSeries(planet2);
    chart->createDefaultAxes();
    auto xAxis = chart->axes(Qt::Horizontal);
    auto yAxis = chart->axes(Qt::Vertical);
    xAxis[0]->setRange(-250, 250);
    yAxis[0]->setRange(-250, 250);

    ui->graphicsView->setChart(chart);
    ui->start->setDisabled(false);
    ui->stop->setDisabled(true);
    ui->L->valueChanged(ui->L->value());
}

void form::updateGraph(){
    totalTime = satelite->Step(timerInterval);
    //totalTime = totalTime+timerInterval;
    series->append(satelite->GetX(),satelite->GetY());
    ui->graphicsView->update();
    updateStatus();
}
void form::updateStatus(){
    ui->status->setText("Время со старта : "+QString::number(totalTime)+" c dsafsdfsdfsdfsdfsdfsdf");
}

form::~form()
{
	delete ui;
    delete timer;
    delete chart;
    delete series;
}

void form::on_start_clicked()
{
    satelite = new Satelite(59.7, 417.0, 100.0, 0.0, 64, 1.57);
    timer->start(); // Запускаем таймер
    ui->start->setDisabled(true);
    ui->stop->setDisabled(false);
}

void form::on_stop_clicked()
{
    if(timer->isActive()){
        timer->stop();
        ui->start->setDisabled(false);
    }else{
        totalTime =0;
        ui->stop->setDisabled(true);
        series->clear();
        ui->graphicsView->update();
        updateStatus();
        //TODO очистка расчетов
    }
}

void form::on_L_valueChanged(double L)
{
    planet1->clear();
    planet2->clear();
    double x1 = - L*ui->M2->value()/(ui->M1->value()+ui->M2->value());
    double x2 = x1 + L;
    planet1->append(x1,0);
    planet2->append(x2,0);
    ui->graphicsView->update();
    //ui->status->setText(QString::number(x1)+" "+QString::number(x2));
}
