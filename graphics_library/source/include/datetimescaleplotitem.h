#ifndef GRAPHICS_DATETIMESCALEPLOTITEM_H
#define GRAPHICS_DATETIMESCALEPLOTITEM_H

/*!
  * \file datetimescaleplotitem.h
  * \brief Объявление класса графического элемента временной шкалы.
  *
  * \file datetimescaleplotitem.cpp
  * \brief Реализация класса графического элемента временной шкалы.
  */

#include "commonprerequisites.h"
#include "standardplotitem.h"

namespace Graphics {

class DateTimeScalePlotItemPrivate;

//! Графический элемент для рисования временной шкалы.
class GRAPHICS_EXPORT DateTimeScalePlotItem : public StandardPlotItem {
    Q_DECLARE_PRIVATE(DateTimeScalePlotItem)
private:
    //! Указатель на реализацию.
    DateTimeScalePlotItemPrivate * const d_ptr;
public:
    //! Конструктор с указанием используемой временной шкалы \c datetime_scale.
    DateTimeScalePlotItem(DateTimeScale *datetime_scale = 0);
    //! Деструктор.
    ~DateTimeScalePlotItem();

    double beginCoordinateX() const;
    double beginCoordinateY() const;

    double endCoordinateX() const;
    double endCoordinateY() const;

    //! Флаг размещения подписей над шкалой.
    bool isReverted() const;
    //! Смена флага размещения подписей над шкалой.
    void setReverted(bool on);

    //! Используемая временная шкала.
    DateTimeScale *dateTimeScale() const;
    //! Смена использемой временной шкалы на \c datetime_scale.
    void setDateTimeScale(DateTimeScale *datetime_scale);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

} // namespace Graphics

#endif // GRAPHICS_DATETIMESCALEPLOTITEM_H
