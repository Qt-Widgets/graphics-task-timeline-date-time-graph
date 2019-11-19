#ifndef GRAPHICS_DATETIMESCALE_H
#define GRAPHICS_DATETIMESCALE_H

/*!
  * \file datetimescale.h
  * \brief Объявление класса временной шкалы.
  *
  * \file datetimescale.cpp
  * \brief Реализация класса временной шкалы.
  */

#include "commonprerequisites.h"
#include "numericscale.h"

class QDateTime;

namespace Graphics {

class DateTimeScalePrivate;

//! Класс временной шкалы.
class GRAPHICS_EXPORT DateTimeScale : public NumericScale {
    Q_DECLARE_PRIVATE(DateTimeScale)
    Q_DISABLE_COPY(DateTimeScale)

    //! Указатель на реализацию.
    DateTimeScalePrivate * const d_ptr;
public:
    //! Конструктор.
    DateTimeScale();
    //! Деструктор.
    ~DateTimeScale();

    //! Формат подписей.
    QString format() const;
    //! Смена формата подписей на \c format.
    void setFormat(const QString &format);

    QString label(double position) const;
};

} // namespace Graphics

#endif // GRAPHICS_DATETIMESCALE_H
