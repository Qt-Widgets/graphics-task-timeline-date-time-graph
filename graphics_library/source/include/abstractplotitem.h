#ifndef GRAPHICS_ABSTRACTPLOTITEM_H
#define GRAPHICS_ABSTRACTPLOTITEM_H

/*!
  * \file abstractplotitem.h
  * \brief Объявление базового класса элементов графика.
  *
  * \file abstractplotitem.cpp
  * \brief Реализация базового класса элементов графика.
  */

#include <QGraphicsItem>
#include "commonprerequisites.h"

namespace Graphics {

//! Базовый класс элементов графика.
class GRAPHICS_EXPORT AbstractPlotItem : public QGraphicsItem {
    Q_DISABLE_COPY(AbstractPlotItem)
protected:
    //! Конструктор.
    AbstractPlotItem();
public:
    //! Деструктор.
    virtual ~AbstractPlotItem();

    //! Координаты начала элемента.
    virtual QPointF beginCoordinates() const = 0;
    //! Установка координат начала элемента в (x, y).
    virtual void setBeginCoordinates(double x, double y) = 0;
    //! Установка координат начала элемента в точку \c coordinates.
    virtual void setBeginCoordinates(const QPointF &coordinates) = 0;

    //! Координата \c x начала элемента.
    virtual double beginCoordinateX() const = 0;
    //! Установка координаты \c x начала элемента.
    virtual void setBeginCoordinateX(double x) = 0;

    //! Координата \c y начала элемента.
    virtual double beginCoordinateY() const = 0;
    //! Установка координаты \c y начала элемента.
    virtual void setBeginCoordinateY(double y) = 0;

    //! Координаты конца элемента.
    virtual QPointF endCoordinates() const = 0;
    //! Установка координат конца элемента в (x, y).
    virtual void setEndCoordinates(double x, double y) = 0;
    //! Установка координат конца элемента в точку \c coordinates.
    virtual void setEndCoordinates(const QPointF &coordinates) = 0;

    //! Координата \c x конца элемента.
    virtual double endCoordinateX() const = 0;
    //! Установка координаты \c x конца элемента.
    virtual void setEndCoordinateX(double x) = 0;

    //! Координата \c y конца элемента.
    virtual double endCoordinateY() const = 0;
    //! Установка координаты \c y конца элемента.
    virtual void setEndCoordinateY(double y) = 0;

    //! Флаг необходимости расчета ширины элемента на основе координаты \c x его начала и конца.
    virtual bool isWidthCalculated() const = 0;
    //! Смена флага необходимости расчета ширины элемента на основе координаты \c x его начала и конца на \c on.
    virtual void setWidthCalculated(bool on) = 0;

    //! Флаг необходимости расчета высоты элемента на основе координаты \c y его начала и конца.
    virtual bool isHeightCalculated() const = 0;
    //! Смена флага необходимости расчета высоты элемента на основе координаты \c y его начала и конца на \c on.
    virtual void setHeightCalculated(bool on) = 0;

    //! Размер элемента.
    virtual QSizeF size() const = 0;
    //! Смена размера элемента на (width, height).
    virtual void setSize(double width, double height) = 0;
    //! Смена размера элемента на \c size.
    virtual void setSize(const QSizeF &size) = 0;

    //! Ширина элемента.
    virtual double width() const = 0;
    //! Смена ширины элемента на \c width.
    virtual void setWidth(double width) = 0;

    //! Высота элемента.
    virtual double height() const = 0;
    //! Смена высоты элемента на \c height.
    virtual void setHeight(double height) = 0;

    //! Сцена графика, на котором размещен элемент.
    virtual AbstractPlotScene *plotScene() const = 0;
    //! Установка сцены графика, на котором размещен элемент.
    virtual void setPlotScene(AbstractPlotScene *plot_scene) = 0;

    //! Описывающий прямоугольник элемента.
    virtual QRectF boundingRect() const = 0;
    //! Рисование элемента с помощью \c painter, используя настройку стиля \c option и родительский виджет \c widget.
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTPLOTITEM_H
