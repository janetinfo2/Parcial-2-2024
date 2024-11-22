#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muParser.h"

struct file
{
    QVector<double> time;
    QVector<double> volt;
    QVector<double> current;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void plot_volt();
    void plot_current();
    void seedats();

private:
    Ui::MainWindow *ui;
    int t;
    void open_file();
    file dat;
    double Angulo();
    double Potencia();
    double RMS(const QVector<double>&datos, const QVector<double>& time);
    double pot_mecanica(double &Vrms, double &Irms, double &angulo);
    double Vrms;
    double Irms;
    double pot;
};
#endif // MAINWINDOW_H
