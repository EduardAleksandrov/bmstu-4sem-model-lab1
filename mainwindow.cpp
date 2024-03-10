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

    fobj = new Funcs(this); // задаем n, m
    fobj->func_cdf = func_cdf;
    fobj->func_pdf = func_pdf;
    fobj->func_erlang_cdf = func_erlang_cdf;
    fobj->func_erlang_pdf = func_erlang_pdf;
//    qDebug() << fobj->getN() << " " << fobj->getM() << fobj->func_cdf(8)<< " "<< fobj->func_pdf(fobj->func_cdf,8,0.002);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::func_cdf(double x)
{
//    double f = pow(x,2)/64; // 0 8
    double f = (x-5)/(8-5);   // 5 8
    return f;
}

double MainWindow::func_pdf(double fun(double), double x, double h)
{
    double f = (fun(x+h)-fun(x))/h;
    return f;
}

double MainWindow::func_erlang_cdf(double x, int k, double lambda)
{
    double sum {0};
    for(int n = 0; n <= k-1; n++)
    {
        sum+=exp(-1.0*lambda*x)*pow(lambda*x,n)/factorial(n);
    }
    double f = 1.0 - sum;
    return f;
}

double MainWindow::func_erlang_pdf(double fun(double, int, double), double x, double h, int k, double lambda)
{
    double f = (fun(x+h, k, lambda)-fun(x, k, lambda))/h;
//    double f = (pow(lambda,k)*pow(x, k-1)*exp(-1.0*lambda*x))/factorial(k-1);
    return f;
}

int MainWindow::factorial(int num)
{
    if (num == 0) return 1;
    else return(num * factorial(num - 1));
}


void MainWindow::on_pushButton_clicked()
{
    fobj->setN(5);
    fobj->setM(8);

    ui->textBrowser->clear();
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    double aa = a.toDouble();
    double bb = b.toDouble();
//    qDebug() << aa << " " << bb;
    if(a == "" || b == "")
    {
        ui->textBrowser->setText("Введите диапазон");
        return;
    }
    if(aa == bb)
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
    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
    int N = (j - i) / h+1;//Вычисляем количество точек, которые будем отрисовывать
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
//        qDebug() << xx[ii-1] << " "<< yy[ii-1];
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
//    ui->widget_cdf->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
//    ui->widget_cdf->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии

    //формируем вид точек
//    ui->widget_cdf->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));


    //Подписываем оси Ox и Oy
    ui->widget_cdf->xAxis->setLabel("x");
    ui->widget_cdf->yAxis->setLabel("F(x)");

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
    if(floor( minY*100 )/100 == floor( maxY*100 )/100) minY = 0.0;
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
//    ui->widget_pdf->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
//    ui->widget_pdf->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии

    //формируем вид точек
//    ui->widget_pdf->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));


    //Подписываем оси Ox и Oy
    ui->widget_pdf->xAxis->setLabel("x");
    ui->widget_pdf->yAxis->setLabel("f(x)");

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
    if(floor( minY*100 )/100 == floor( maxY*100 )/100) minY = 0.0;
    ui->widget_pdf->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget_pdf->replot();
}

void MainWindow::on_pushButton_2_clicked()
{
    fobj->setN(0.01);
    fobj->setM(20);

    ui->textBrowser->clear();
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    double aa = a.toDouble();
    double bb = b.toDouble();
//    qDebug() << aa << " " << bb;
    if(a == "" || b == "")
    {
        ui->textBrowser->setText("Введите диапазон");
        return;
    }
    if(aa == bb)
    {
        ui->textBrowser->setText("Введите диапазон");
        return;
    }
    if(aa>bb)
    {
        ui->textBrowser->setText("Введите диапазон правильно");
        return;
    }
    if(aa<0)
    {
        ui->textBrowser->setText("a должен быть больше или равен нулю");
        return;
    }
    QString k = ui->lineEdit_3->text();
    QString lambda = ui->lineEdit_4->text();
    int kk = k.toInt();
    double llambda = lambda.toDouble();
    if(kk < 1)
    {
        ui->textBrowser->setText("Введите k >= 1, натуральные");
        return;
    }
    if(llambda <= 0.0)
    {
        ui->textBrowser->setText("Введите lambda > 0");
        return;
    }

    double i = fobj->getN();
    double j = fobj->getM();
    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
    int N = (j - i) / h+1;//Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N);
    QVector<double> y(N);
    //Вычисляем наши данные
    int ii=0;
    //Пробегаем по всем точкам
    for (double X = i; X <= j; X += h) {
        x[ii] = X;
        y[ii] = fobj->func_erlang_cdf(X, kk, llambda);
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
        yy[ii] = fobj->func_erlang_pdf(fobj->func_erlang_cdf, X ,0.002, kk, llambda);
        ii++;
    }

    show_pdf(xx, yy, aa, bb);

}

