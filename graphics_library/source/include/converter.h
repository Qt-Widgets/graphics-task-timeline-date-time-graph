#ifndef GRAPHICS_CONVERTER_H
#define GRAPHICS_CONVERTER_H

/*!
  * \file valueadapter.h
  * \brief Объявление классов адаптеров для конвертации значений шкал.
  *
  * \file valueadapter.cpp
  * \brief Реализация классов адаптеров для конвертации значений шкал.
  */

#include "commonprerequisites.h"

class QDateTime;

namespace Graphics {

//! Адаптер для конвертации дат и времени в числовые значения для шкал.
class GRAPHICS_EXPORT Converter {
public:
    //! Конвертация даты \c val в число.
    static double toScale(const QDateTime &val);
    //! Конвертация числа \c val в дату.
    static QDateTime fromScale(double val);
};

} // namespace Graphics

#endif // GRAPHICS_CONVERTER_H
