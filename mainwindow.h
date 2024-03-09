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
    void show_cdf(QVector<double>, QVector<double>, double, double);
    void show_pdf(QVector<double>, QVector<double>, double, double);


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Funcs* fobj;
};
#endif // MAINWINDOW_H
