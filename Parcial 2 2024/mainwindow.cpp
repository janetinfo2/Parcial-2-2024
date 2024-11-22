#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_volt, SIGNAL(clicked()), this, SLOT(plot_volt()) );
    connect(ui->btn_current, SIGNAL(clicked()), this, SLOT(plot_current()) );
    connect(ui->btn_dat, SIGNAL(clicked()), this, SLOT(seedats()) );

    double angulo = Angulo();
    Potencia();
    Vrms = RMS(dat.volt,dat.time);
    Irms = RMS(dat.current, dat.time);
    qDebug()<<"Vrms es:"<<Vrms;
    qDebug()<<"Irms es:"<<Irms;
    pot = pot_mecanica(Vrms,Irms,angulo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_file()
{
    FILE *f = fopen("C:\\Users\\schme\\OneDrive\\Escritorio\\Parcial 2 2024\\vi_1.dat","rb");

    if (f==nullptr)
    {
        qDebug() << "No se pudo abrir el archivo" ;
        return;
    }

    fseek(f,0,SEEK_END);
    t = ftell(f)/sizeof(double);
    fseek(f,0,SEEK_SET);


    double d;

    while(fread(&d, sizeof(double), 1, f))
    {
        dat.time.append(d);

        (fread(&d, sizeof(double), 1, f));
         dat.volt.append(d);

        (fread(&d, sizeof(double), 1, f));
        dat.current.append(d);
    }
    fclose(f);

    qDebug()<<"datos recolectados correctamente.";


    qDebug() << "Tamaño de tiempo:" << dat.time.size();
    qDebug() << "Tamaño de tension:" << dat.volt.size();
    qDebug() << "Tamaño de corriente:" << dat.current.size();

/*
    for(int i=0;i<dat.time.size;i++)
    {
        qDebug() << "vector tiempo:"<<dat.time[i];
    }
    for(int i=0;i<dat.volt.size;i++)
    {
        qDebug() << "vector tension:"<<dat.volt[i];
    }
    for(int i=0;i<dat.current.size;i++)
    {
        qDebug() << "vector corriente:"<<dat.current[i];
    }
*/

}

void MainWindow::plot_volt()
{
    if (dat.time.isEmpty() || dat.volt.isEmpty() )
    {
        open_file();
        if (dat.time.isEmpty() || dat.volt.isEmpty())
        {
            qDebug() << "No se pudieron cargar los datos.";
            return;
        }
    }

    ui->graphic->clearGraphs();
    if(ui->graphic->graphCount()==0)
        ui->graphic->addGraph();
    ui->graphic->graph(0)->setData(dat.time,dat.volt);
    ui->graphic->graph(0)->setPen(QPen(Qt::blue));
    ui->graphic->rescaleAxes();
    ui->graphic->replot();

}
void MainWindow::plot_current()
{
    if (dat.time.isEmpty() || dat.current.isEmpty() )
    {
        open_file();
        if (dat.time.isEmpty() || dat.current.isEmpty())
        {
            qDebug() << "No se pudieron cargar los datos.";
            return;
        }
    }


    if(ui->graphic->graphCount()==1)
        ui->graphic->addGraph();
    ui->graphic->graph(1)->setData(dat.time,dat.current);
    ui->graphic->graph(1)->setPen(QPen(Qt::red));
    ui->graphic->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
    ui->graphic->rescaleAxes();
    ui->graphic->replot();

}


double MainWindow::Angulo()
{
    double timeVolt = 0.0;
    double timeCurrent = 0.0;

    //Determino el tiempo donde la tensión está más cerca de cero
    for (int i = 1; i < dat.volt.size(); i++)
    {
        if ((dat.volt[i - 1] < 0 && dat.volt[i] >= 0) || (dat.volt[i - 1] > 0 && dat.volt[i] <= 0))
        {
            // Aplico interpolación lineal para encontrar el cruce
            double t1 = dat.time[i - 1], t2 = dat.time[i];
            double v1 = dat.volt[i - 1], v2 = dat.volt[i];
            timeVolt = t1 + (0.0 - v1) * (t2 - t1) /( (v2 - v1)*1.0);//t seria mi eje x y v mi eje y
            break;
        }
    }

    //Determino el tiempo donde la corriente cruza por cero
    for (int i = 1; i < dat.current.size(); i++)
    {
        if ((dat.current[i - 1] < 0 && dat.current[i] >= 0) || (dat.current[i - 1] > 0 && dat.current[i] <= 0))
        {
            // Aplico lo mismo
            double t1 = dat.time[i - 1], t2 = dat.time[i];
            double c1 = dat.current[i - 1], c2 = dat.current[i];
            timeCurrent = t1 + (0.0 - c1) * (t2 - t1) /( (c2 - c1)*1.0);
            break;
        }
    }

    double desfase = qAbs(timeCurrent - timeVolt);

    double angulo = (180.0 / 0.01) * desfase;


    qDebug() << "Tiempo cerca de 0:" << timeVolt;
    qDebug() << "Tiempo del cruce por cero de la corriente:" << timeCurrent;
    qDebug() << "Desfasaje en tiempo:" << desfase;
    qDebug() << "El ángulo calculado es:" << angulo;

    return angulo;
}

double MainWindow::Potencia()
{
    // Verifico que los datos no estén vacíos
    if (dat.time.isEmpty() || dat.volt.isEmpty() || dat.current.isEmpty())
    {
        qDebug()<<"algun vector esta vacío.";
        return -1.0;
    }

    double pot_total = 0.0;
    int N = dat.time.size();
    double tMin = dat.time.first();
    double tMax = dat.time.last();

    // Calculo la integral
    for (int i = 0; i < N - 1; ++i)
    {
        if (dat.time[i] >= tMin && dat.time[i + 1] <= tMax)
        {
            double delta_t = dat.time[i + 1] - dat.time[i];
            double prod = dat.volt[i] * dat.current[i];
            pot_total += delta_t * prod;
        }
    }

    double potencia = pot_total / (tMax - tMin);

    qDebug() << "Potencia calculada:" << potencia;

    return potencia;
}

double MainWindow::RMS(const QVector<double>&datos, const QVector<double>& time)
{

    if (datos.isEmpty() || time.isEmpty())
    {
        qDebug()<<"Los vectores de señal o tiempo están vacíos.";
        return -1.0;
    }

    double integral = 0.0;
    int N = time.size();
    double tMin = time.first();
    double tMax = time.last();


    // Calculo la integral  de x^2
    for (int i = 0; i < N - 1; i++)
    {
        if (time[i] >= tMin && time[i + 1] <= tMax)
        {
            double delta_t = time[i + 1] - time[i];
            double prod = datos[i] * datos[i];
            integral += prod * delta_t;
        }
    }


    double rms = qSqrt(integral / (tMax - tMin));


    return rms;
}


double MainWindow::pot_mecanica(double &Vrms, double &Irms, double &angulo)
{
    double rad = angulo * M_PI / 180.0;

    double potencia = Vrms * Irms * std::cos(rad);

    qDebug() << "Potencia calculada:" << potencia;

    return potencia;
}

void MainWindow::seedats()
{
    ui->vrms->setText(QString::number(Vrms));
    ui->irms->setText(QString::number(Irms));
    ui->pot->setText(QString::number(pot));
}


