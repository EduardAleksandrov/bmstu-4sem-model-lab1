#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "funcs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static double func_cdf(double x);
    static double func_pdf(double fun(double), double x, double h);
    static double func_erlang_cdf(double x, int k, double labda);
    static double func_erlang_pdf(double fun(double, int, double), double x, double h, int k, double labda);

    void show_cdf(QVector<double>, QVector<double>, double, double);
    void show_pdf(QVector<double>, QVector<double>, double, double);

    static int factorial(int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Funcs* fobj;
};
#endif // MAINWINDOW_H
