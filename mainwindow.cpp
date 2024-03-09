#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <cmath>
#include <vector>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fobj = new Funcs(this, 0, 8); // задаем n, m
    fobj->func_cdf = func_cdf;
    fobj->func_pdf = func_pdf;
    qDebug() << fobj->getN() << " " << fobj->getM() << fobj->func_cdf(8)<< " "<< fobj->func_pdf(fobj->func_cdf,8,0.002);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::func_cdf(double x)
{
    double f = pow(x,2)/64;
    return f;
}

double MainWindow::func_pdf(double fun(double), double x, double h)
{
    double f = (fun(x+h)-fun(x))/h;
    return f;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    double aa = a.toDouble();
    double bb = b.toDouble();
    qDebug() << aa << " " << bb;
    if(a == "" || b == "")
    {
        ui->textBrowser->setText("Введите диапазон");
        return;
    }
    if(aa == 0 && bb == 0)
    {
        ui->textBrowser->setText("Введите диапазон");
        return;
    }
    if(aa>bb)
    {
        ui->textBrowser->setText("Введите диапазон правильно");
        return;
    }

    double i = fobj->getN();
    double j = fobj->getM();
    double h = 0.1; //Шаг, с которым будем пробегать по оси Ox
    int N = (j - i) / h + 2;//Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N);
    QVector<double> y(N);
    //Вычисляем наши данные
    int ii=0;
    //Пробегаем по всем точкам
    for (double X = i; X <= j; X += h) {
        x[ii] = X;
        y[ii] = fobj->func_cdf(X);
        ii++;
    }
    show_cdf(x, y, aa, bb);

    QVector<double> xx(N);
    QVector<double> yy(N);
    //Вычисляем наши данные
    ii=0;
    //Пробегаем по всем точкам
    for (double X = i; X <= j; X += h) {
        xx[ii] = X;
        yy[ii] = fobj->func_pdf(fobj->func_cdf,X,0.002);
        ii++;
//        qDebug() << y[ii];
    }
    show_pdf(xx, yy, aa, bb);
}

void MainWindow::show_cdf(QVector<double> x, QVector<double> y, double a, double b)
{
//    double a = -1; //Начало интервала, где рисуем график по оси Ox
//    double b =  1; //Конец интервала, где рисуем график по оси Ox
//    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
//    int N = (b - a) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
//    QVector<double> x(N), y(N); //Массивы координат точек

//    //Вычисляем наши данные
//    int i=0;
//    //Пробегаем по всем точкам
//    for (double X = a; X <= b; X += h) {
//      x[i] = X;
//      y[i] = X * X;//Формула нашей функции
//      i++;
//    }
    ui->widget_cdf->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->widget_cdf->addGraph();

    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget_cdf->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget_cdf->xAxis->setLabel("x");
    ui->widget_cdf->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    ui->widget_cdf->xAxis->setRange(a, b);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
//    if(y.size() == 0) return;
    double minY = y[0], maxY = y[0];
    for (int i = 1; i < y.size(); i++) {
      if (y[i] < minY) minY = y[i];
      if (y[i] > maxY) maxY = y[i];
    }
    ui->widget_cdf->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget_cdf->replot();
}


void MainWindow::show_pdf(QVector<double> x, QVector<double> y, double a, double b)
{
    ui->widget_pdf->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->widget_pdf->addGraph();

    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget_pdf->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget_pdf->xAxis->setLabel("x");
    ui->widget_pdf->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    ui->widget_pdf->xAxis->setRange(a, b);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
//    if(y.size() == 0) return;
    double minY = y[0], maxY = y[0];
    for (int i = 1; i < y.size(); i++) {
      if (y[i] < minY) minY = y[i];
      if (y[i] > maxY) maxY = y[i];
    }
    ui->widget_pdf->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget_pdf->replot();
}
