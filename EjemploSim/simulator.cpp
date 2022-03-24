#include "simulator.h"
#include "ui_simulator.h"
#include "math.h"

#include <iostream>
using namespace std;



Simulator::Simulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Simulator)
{
    datos.open("datos.txt", std::ios_base::out);
    if(!datos.is_open()){
        cout<<"No se pudo abrir el archivo";
    }


    ui->setupUi(this);
    // se agrega la escena
    scene = new QGraphicsScene(-6000, -6000, 12000, 12000);
    ui->graphicsView->setScene(scene);

    /*ui->graphicsView->setRenderHint(QPainter::Antialiasing);*/

    // limites de la escena
    l1 = new QGraphicsLineItem(-500,-250,500,-250);
    l2 = new QGraphicsLineItem(-500,250,500,250);
    l3 = new QGraphicsLineItem(-500,-250,-500,250);
    l4 = new QGraphicsLineItem(500,-250,500,250);

    // Se agregan los limites a la escena
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);

    secuencia = false;

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()), this, SLOT(Actualizar()));

}

Simulator::~Simulator()
{
    delete ui;
}


void Simulator::Actualizar()
//Actualiza las velocidades y posiciones del cuerpo
{

    int i=0, j=0,r=0;


    for (r=0 ; r<10 ; r++)
    {


        //PRUEBA

        for(i=0; i < sistema.length(); i++){

            x[i]=sistema[i]->getX();
            y[i]=sistema[i]->getY();
        }


            for(i=0; i < sistema.length(); i++){

             aceleracionx=0;
             aceleraciony=0;

                      cout<<i<<" en x: "<<sistema[i]->getX()<<" en y: "<<sistema[i]->getY()<<endl;
                   //   cout<<i<<" en x: "<<x[i]<<" en y: "<<y[i]<<endl;

                           datos << sistema[i]->getX()<<"   "<<sistema[i]->getY()<<"   ";


             for (j=0 ; j < sistema.length() ; j++)
             {

                 if (i!=j){


                     radio=sqrt(pow((sistema[j]->getX()-sistema[i]->getX()),2)+pow((sistema[j]->getY()-sistema[i]->getY()),2));

                   //  radio=sqrt(pow((x[j]-x[i]),2)+pow((y[j]-y[i]),2));

                 //    para_tetha=(y[j]-y[i])/(x[j]-x[i]);
                  //   tetharad=atan2((y[j]-y[i]),(x[j]-x[i]));

                     para_tetha=(sistema[j]->getY()-sistema[i]->getY())/(sistema[j]->getX()-sistema[i]->getX());
                     tetharad=atan2((sistema[j]->getY()-sistema[i]->getY()),(sistema[j]->getX()-sistema[i]->getX()));


                     //tetha=180*tetha/3.14159265359;

                     aceleracionx=aceleracionx+(sistema[j]->getMasa()*cos(tetharad)/pow(radio,2));
                     aceleraciony=aceleraciony+(sistema[j]->getMasa()*sin(tetharad)/pow(radio,2));
               }
             }

            sistema[i]->setAx(aceleracionx);
             sistema[i]->setAy(aceleraciony);
             sistema[i]->velocidades();
             sistema[i]->posiciones();
 }
            datos << '\n';
        //PRUEBA
    }

}



void Simulator::on_lanzamiento1_btn_clicked()
// Lanza el cuerpo 1 en mvto parabolico
{
    // Cuerpo 1
    timer->start(2);
    if (!secuencia)
    {
 //       sistema.append(new cuerpo(10,10,300,200,20,700));   //x, y, vx, vy, radio, masa
 //       scene->addItem(sistema.last());


               sistema.append(new cuerpo(0,-7000,2,0,120,70));   //x, y, vx, vy, radio, masa
               scene->addItem(sistema.last());
               sistema.append(new cuerpo(0,0,0,0,300,70000));   //x, y, vx, vy, radio, masa
               scene->addItem(sistema.last());
               sistema.append(new cuerpo(4000,5000,-1.6,1.2,100,25));   //x, y, vx, vy, radio, masa
               scene->addItem(sistema.last());


        secuencia = true;
    }

}


void Simulator::on_lanzamiento2_btn_clicked()
//Lanza el cuerpo 2 en mvto parabolico
{
    // Cuerpo 2
    timer->start(10);
    if (!secuencia)
    {
    //    sistema.append(new cuerpo(-500,-250,500,100,20,700));
    //    scene->addItem(sistema.last());

        sistema.append(new cuerpo(0,0,0,0,200,50000));  //x, y, vx, vy, radio, masa
        scene->addItem(sistema.last());
        sistema.append(new cuerpo(-5000,0,0,-1,70,70));
        scene->addItem(sistema.last());
        sistema.append(new cuerpo(5000,0,0,2,70,70));
        scene->addItem(sistema.last());
        sistema.append(new cuerpo(0,-5000,2,0,70,70));
        scene->addItem(sistema.last());
        sistema.append(new cuerpo(0,5000,-2,0,70,70));
        scene->addItem(sistema.last());

        secuencia = true;
    }
}


void Simulator::on_finalizar_btn_clicked()
//para finalizar la simulacion
{
    int i=0;

    timer->stop();

    for (i=0 ; i < sistema.length() ; i++)
        scene->removeItem(sistema[i]);

    sistema.clear();

    secuencia = false;
}




