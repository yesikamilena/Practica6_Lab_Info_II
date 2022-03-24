#include "cuerpo.h"

cuerpo::cuerpo(float _x, float _y, float _vx, float _vy, float _rad, float _masa)
{
    x = _x;
    y = _y;
    vx = _vx;
    vy = _vy;
    ax = 0;
    ay = 0;
    radio = _rad;
    masa = _masa;

    t=t+DT;

    // sin ajustar los cuadrantes
    // setPos((x/EX), (y/EY));

    // ajustando los cuadrates
    setPos((x/EX), (-y/EY));
}

QRectF cuerpo::boundingRect() const
{
    return QRect(-radio, -radio, radio*2, radio*2);
}

void cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}


float cuerpo::getX() const
{
    return x;
}
float cuerpo::getY() const
{
    return y;
}
float cuerpo::getVx() const
{
    return vx;
}
float cuerpo::getVy() const
{
    return vy;
}
float cuerpo::getAx() const
{
    return ax;
}
float cuerpo::getAy() const
{
    return ay;
}
float cuerpo::getRad() const
{
    return radio;
}
float cuerpo::getMasa() const
{
    return masa;
}


void cuerpo::setX(float value)
{
    x = value;
}
void cuerpo::setY(float value)
{
    y = value;
}
void cuerpo::setVx(float value)
{
    vx = value;
}
void cuerpo::setVy(float value)
{
    vy = value;
}
void cuerpo::setAx(float value)
{
    ax = value;
}
void cuerpo::setAy(float value)
{
    ay = value;
}
void cuerpo::setRad(float value)
{
    radio = value;
}
void cuerpo::setMasa(float value)
{
    masa = value;
}


void cuerpo::aceleracion()
{
    ax += 0;
    ay = GRAV;

}

void cuerpo::velocidades()
// calcula las aceleraciones
{
    vx = vx + (ax*t);
    vy = vy + (ay*t);
}

void cuerpo::posiciones()
// calcula y Actualiza las posiciones
{
    x = x + (vx * t) + (0.5 * ax * pow(t,2));
    y = y + (vy * t) + (0.5 * ay * pow(t,2));

    // sin ajustar los cuadrantes
    // setPos((x/EX), (y/EY));

    // ajustando los cuadrantes
    setPos((x/EX), (-y/EY));
}

