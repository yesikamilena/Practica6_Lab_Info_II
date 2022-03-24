#ifndef CUERPO_H
#define CUERPO_H

#define EX 600
#define EY 600

//#define G 6.67384 * pow(10,-11)
#define GRAV 1
#define DT 1

#include <QGraphicsItem>
#include <QPainter>

class cuerpo : public QGraphicsItem
{

private:
    float x, y, vx, vy, ax, ay, radio, masa;

    float t=0;

public:
    cuerpo();
    cuerpo(float _x, float _y, float _vx, float _vy, float _radio, float _masa);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // get
    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getAx() const;
    float getAy() const;
    float getRad() const;
    float getMasa() const;

    // set
    void setX(float value);
    void setY(float value);
    void setVx(float value);
    void setVy(float value);
    void setAx(float value);
    void setAy(float value);
    void setRad(float value);
    void setMasa(float value);

    // Funciones mvto
    void aceleracion();
    void velocidades();
    void posiciones();
};

#endif // CUERPO_H
