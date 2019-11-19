#include "include/numericscale.h"
#include "include/abstractplotitem.h"


namespace Graphics {

//! Релизация класса числовой шкалы.
class NumericScalePrivate {
    friend class NumericScale;

    //! Минимальное значение.
    double minimum;
    //! Максимальное значение.
    double maximum;
    //! Длина.
    double length;
    //! Ориентация.
    Qt::Orientation orientation;
    //! Точность представления для дробных чисел.
    uint precision;

    //! Конструктор.
    NumericScalePrivate() :
        minimum(0.0), maximum(0.0),
        length(0.0), orientation(Qt::Horizontal),
        precision(3)
    {}

    //! Деструктор.
    ~NumericScalePrivate() {}
};



NumericScale::NumericScale() :
    AbstractScale(),
    d_ptr(new NumericScalePrivate())
{
}

NumericScale::~NumericScale()
{
    delete d_ptr;
}

uint NumericScale::precision() const
{
    Q_D(const NumericScale);
    return d->precision;
}

void NumericScale::setPrecision(uint prec)
{
    Q_D(NumericScale);
    d->precision = prec;
}

Qt::Orientation NumericScale::orientation() const
{
    Q_D(const NumericScale);
    return d->orientation;
}

void NumericScale::setOrientation(Qt::Orientation orientation)
{
    Q_D(NumericScale);
    d->orientation = orientation;
}

double NumericScale::length() const
{
    Q_D(const NumericScale);
    return d->length;
}

void NumericScale::setLength(double length)
{
    Q_D(NumericScale);
    d->length = length;
}

double NumericScale::minimum() const
{
    Q_D(const NumericScale);
    return d->minimum;
}

void NumericScale::setMinimum(double min)
{
    Q_D(NumericScale);
    d->minimum = min;
}

double NumericScale::maximum() const
{
    Q_D(const NumericScale);
    return d->maximum;
}

void NumericScale::setMaximum(double max)
{
    Q_D(NumericScale);
    d->maximum = max;
}

void NumericScale::setRange(double min, double max)
{
    Q_D(NumericScale);
    d->minimum = min;
    d->maximum = max;
}

double NumericScale::position(double value) const
{
    Q_D(const NumericScale);
    return ((value - d->minimum) / (d->maximum - d->minimum) * d->length);
}

double NumericScale::value(double position) const
{
    Q_D(const NumericScale);
    return (d->minimum + position / d->length * (d->maximum - d->minimum));
}

double NumericScale::position(const AbstractPlotItem *item) const
{
    Q_D(const NumericScale);
    return (d->orientation == Qt::Horizontal) ? (position(item->beginCoordinateX()) + item->width() * 0.5)
                                              : (position(item->beginCoordinateY()) + item->height() * 0.5);
}

double NumericScale::distance(double value_from, double value_to) const
{
    return qAbs(position(value_to) - position(value_from));
}

QString NumericScale::label(double position) const
{
    Q_D(const NumericScale);
    return QString::number(value(position), 'f', d->precision);
}

} // namespace Graphics
