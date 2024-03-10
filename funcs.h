#ifndef FUNCS_H
#define FUNCS_H

#include <QObject>

class Funcs : public QObject
{
    Q_OBJECT
public:
    explicit Funcs(QObject *parent = nullptr, double nn = 0, double mm = 1);
    ~Funcs();

    double getN();
    double getM();
    double (*func_cdf)(double);
    double (*func_pdf)(double fun(double), double , double);
    void setN(double);
    void setM(double);


    double (*func_erlang_cdf)(double, int, double);

signals:

private:
    double n;
    double m;
};

#endif // FUNCS_H
