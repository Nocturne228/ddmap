#include "passenger.h"

Passenger::Passenger(const QPointF &position, int state, const QString &iconPath)
    : position(position), state(state), icon(iconPath)
{
}

Passenger::Passenger() {}

QPointF Passenger::getPosition() const
{
    return position;
}

void Passenger::setPosition(const QPointF &position)
{
    this->position = position;
}

int Passenger::getState() const
{
    return state;
}

void Passenger::setState(int state)
{
    this->state = state;
}

QPixmap Passenger::getIcon() const
{
    return icon;
}

void Passenger::setIcon(const QString &iconPath)
{
    icon = QPixmap(iconPath);
}
