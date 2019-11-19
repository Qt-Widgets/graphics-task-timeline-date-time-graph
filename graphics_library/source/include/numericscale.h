#ifndef GRAPHICS_NUMERICSCALE_H
#define GRAPHICS_NUMERICSCALE_H

/*!
  * \file numericscale.h
  * \brief Объявление класса числовой шкалы.
  *
  * \file numericscale.cpp
  * \brief Реаилзация класса числовой шкалы.
  */

#include <QObject>
#include "commonprerequisites.h"
#include "abstractscale.h"

namespace Graphics {

class NumericScalePrivate;

//! Класс числовой шкалы.
class GRAPHICS_EXPORT NumericScale : public AbstractScale {
    Q_DECLARE_PRIVATE(NumericScale)
    Q_DISABLE_COPY(NumericScale)

    //! Указатель на реализацию.
    NumericScalePrivate * const d_ptr;
public:
    //! Конструктор.
    NumericScale();
    //! Деструктор.
    ~NumericScale();

    //! Точность представления для дробных чисел.
    uint precision() const;
    //! Смена точности представления дробных чисел на \c prec знаков после запятой.
    void setPrecision(uint prec);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    double length() const;
    void setLength(double length);

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setRange(double min, double max);

    double position(double value) const;
    double value(double position) const;

    double position(const AbstractPlotItem *item) const;

    double distance(double value_from, double value_to) const;

    QString label(double position) const;
};

} // namespace Graphics

#endif // GRAPHICS_NUMERICSCALE_H
