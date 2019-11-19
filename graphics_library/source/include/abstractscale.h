#ifndef GRAPHICS_ABSTRACTSCALE_H
#define GRAPHICS_ABSTRACTSCALE_H

/*!
  * \file abstractscale.h
  * \brief Объявление базового класса шкалы графика.
  */

#include <Qt>
#include "commonprerequisites.h"

class QString;

namespace Graphics {

//! Базовый класс шкалы графика.
class GRAPHICS_EXPORT AbstractScale {
protected:
    //! Конструктор.
    AbstractScale() {}
public:
    //! Деструктор.
    virtual ~AbstractScale() {}

    //! Ориентация шкалы.
    virtual Qt::Orientation orientation() const = 0;
    //! Смена ориентации шкалы на \c orientation.
    virtual void setOrientation(Qt::Orientation orientation) = 0;

    //! Длина шкалы.
    virtual double length() const = 0;
    //! Смена длины шкалы на \c length.
    virtual void setLength(double length) = 0;

    //! Минимальное значение шкалы.
    virtual double minimum() const = 0;
    //! Смена минимального значения шкалы на \c min.
    virtual void setMinimum(double min) = 0;

    //! Максимальное значение шкалы.
    virtual double maximum() const = 0;
    //! Смена максимального значения шкалы на \c max.
    virtual void setMaximum(double max) = 0;

    //! Смена диапазона допустимых значений шкалы на \c min и \c max.
    virtual void setRange(double min, double max) = 0;

    //! Положение значения \c value.
    virtual double position(double value) const = 0;
    //! Значение на позиции \c position.
    virtual double value(double position) const = 0;

    //! Положение графического элемента \c item.
    virtual double position(const AbstractPlotItem *item) const = 0;

    //! Расстояние между значениями \c value_from и \c value_to.
    virtual double distance(double value_from, double value_to) const = 0;

    //! Подпись значения на позиции \c position.
    virtual QString label(double position) const = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTSCALE_H
