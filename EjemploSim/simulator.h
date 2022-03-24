#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>

using namespace std;

#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <fstream>
#include <sstream>
#include <string>

#include "cuerpo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Simulator; }
QT_END_NAMESPACE

class Simulator : public QMainWindow
{
    Q_OBJECT

public:
    Simulator(QWidget *parent = nullptr);
    ~Simulator();

public slots:
    void Actualizar();

private slots:
    //void on_Start_clicked();

    //void on_Stop_clicked();

    void on_lanzamiento1_btn_clicked();

    void on_lanzamiento2_btn_clicked();

    void on_finalizar_btn_clicked();

private:
    Ui::Simulator *ui;

    // puntero de mi escena
    QGraphicsScene *scene;

    // temporizador para el pulso
    QTimer *timer;

    //limites
    QGraphicsLineItem *l1;
    QGraphicsLineItem *l2;
    QGraphicsLineItem *l3;
    QGraphicsLineItem *l4;

    //lista de objetos
    QList <cuerpo*> sistema;

    //booleano para controlar la simulación
    bool secuencia;

    //variables para la aceleración
    double radio;
    double para_tetha;
    double tetharad=0;
    double tetha=0;
    float aceleracionx;
    float aceleraciony;

    float x[20];
    float y[20];


    ofstream datos;
    string nombre_txt;



};
#endif // SIMULATOR_H
