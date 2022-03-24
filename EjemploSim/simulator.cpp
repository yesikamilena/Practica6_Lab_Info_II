#include "simulator.h"
#include "ui_simulator.h"
#include "math.h"


#include <iostream>

using namespace std;

Simulator::Simulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Simulator)
{
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


    for (r=0 ; r<1000 ; r++)
    {
       /* for(i=0; i<2; i++){
            for (j=0 ; j < sistema.length() ; j++)
            {
                sistema[i]->aceleracion();
                sistema[i]->velocidades();
                sistema[i]->posiciones();
            }
        }
        */


        //PRUEBA



         for(i=0; i < sistema.length(); i++){
             aceleracionx=0;
             aceleraciony=0;
             cout<<i<<" en x: "<<sistema[i]->getX()<<" en y: "<<sistema[i]->getY()<<endl;
             for (j=0 ; j < sistema.length() ; j++)
             {

                 if (i!=j){

      //               cout<<" powx "<<pow((sistema[j]->getX()-sistema[i]->getX()),2)<<endl;
      //               cout<<" powy "<<pow((sistema[j]->getY()-sistema[i]->getY()),2)<<endl;
      //              cout<<" sqrt "<<sqrt(pow((sistema[j]->getX()-sistema[i]->getX()),2)+pow((sistema[j]->getY()-sistema[i]->getY()),2));

                     radio=sqrt(pow((sistema[j]->getX()-sistema[i]->getX()),2)+pow((sistema[j]->getY()-sistema[i]->getY()),2));

//                     cout<<"radio "<<j+1<<" para el cuerpo "<<i+1<<radio<<endl;

                     para_tetha=(sistema[j]->getY()-sistema[i]->getY())/(sistema[j]->getX()-sistema[i]->getX());
                     tetha=atan(para_tetha);

  //                   cout<<"aceleracion en x antes "<<j+1<<" para el cuerpo "<<i+1<<aceleracionx<<endl;
    //                 cout<<"aceleracion en y antes "<<j+1<<" para el cuerpo "<<i+1<<aceleraciony<<endl;

                     aceleracionx=aceleracionx+(sistema[j]->getMasa()*cos(tetha)/pow(radio,2));
                     aceleraciony=aceleraciony+(sistema[j]->getMasa()*sin(tetha)/pow(radio,2));

      /*               cout<<"radio "<<j+1<<" para el cuerpo "<<i+1<<radio<<endl;
                     cout<<"interno del tetha de "<<j+1<<" para el cuerpo "<<i+1<<para_tetha<<endl;
                    cout<<"tetha "<<j+1<<" para el cuerpo "<<i+1<<tetha<<endl;
                     cout<<"aceleracion en x "<<j+1<<" para el cuerpo "<<i+1<<aceleracionx<<endl;
                     cout<<"pow(radio,2) "<<pow(radio,2)<<endl;
                     cout<<"sistema[j]->getMasa() "<<sistema[j]->getMasa()<<endl;
                     cout<<"aceleracion en y "<<j+1<<" para el cuerpo "<<i+1<<aceleraciony<<endl;
*/
                 }
             }

             sistema[i]->setAx(aceleracionx);
             sistema[i]->setAy(aceleraciony);
           //  sistema[i]->aceleracion();
             sistema[i]->velocidades();
             sistema[i]->posiciones();

             cout<<"posición en x: "<< sistema[i]->getX()<<"; posición en y: "<<sistema[i]->getY()<<endl;
         }

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



/*void Simulator::on_Start_clicked()
// cuando el usario de click al boton start se inicia la simulacion
{
    if (secuencia)
        timer->start(33);

}

void Simulator::on_Stop_clicked()
// para detener la simulacion
{
    timer->stop();
}*/




