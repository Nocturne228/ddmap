#ifndef PASSENGER_H
#define PASSENGER_H

#include <QPointF>
#include <QPixmap>

class Passenger
{
public:
    Passenger(const QPointF &position, int state, const QString &iconPath);
    Passenger();

    QPointF getPosition() const;
    void setPosition(const QPointF &position);

    int getState() const;
    void setState(int state);

    QPixmap getIcon() const;
    void setIcon(const QString &iconPath);

    bool getIsVisible() const;
    void setIsVisible(bool value);

private:
    QPointF position;
    int state;
    QPixmap icon;

    bool isVisible;

};

#endif // PASSENGER_H
