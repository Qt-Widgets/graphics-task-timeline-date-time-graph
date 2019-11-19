#ifndef GRAPHICS_STANDARDPLOTITEM_H
#define GRAPHICS_STANDARDPLOTITEM_H

/*!
  * \file standardplotitem.h
  * \brief Объявление класса элемента графика.
  *
  * \file standardplotitem.cpp
  * \brief Реализация класса элемента графика.
  */

#include "commonprerequisites.h"
#include "abstractplotitem.h"

namespace Graphics {

class StandardPlotItemPrivate;

//! Класс элемента графика.
class GRAPHICS_EXPORT StandardPlotItem : public AbstractPlotItem {
    Q_DECLARE_PRIVATE(StandardPlotItem)
    Q_DISABLE_COPY(StandardPlotItem)

    //! Указатель на реализацию.
    StandardPlotItemPrivate * const d_ptr;
protected:
    //! Конструктор.
    StandardPlotItem();
public:
    //! Деструктор.
    virtual ~StandardPlotItem();

    QPointF beginCoordinates() const;
    void setBeginCoordinates(double x, double y);
    void setBeginCoordinates(const QPointF &coordinates);

    double beginCoordinateX() const;
    void setBeginCoordinateX(double x);

    double beginCoordinateY() const;
    void setBeginCoordinateY(double y);

    QPointF endCoordinates() const;
    void setEndCoordinates(double x, double y);
    void setEndCoordinates(const QPointF &coordinates);

    double endCoordinateX() const;
    void setEndCoordinateX(double x);

    double endCoordinateY() const;
    void setEndCoordinateY(double y);

    bool isWidthCalculated() const;
    void setWidthCalculated(bool on);

    bool isHeightCalculated() const;
    void setHeightCalculated(bool on);

    QSizeF size() const;
    void setSize(double width, double height);
    void setSize(const QSizeF &size);

    double width() const;
    void setWidth(double width);

    double height() const;
    void setHeight(double height);

    AbstractPlotScene *plotScene() const;
    void setPlotScene(AbstractPlotScene *plot_scene);

    QRectF boundingRect() const;
};

} // namespace Graphics

#endif // GRAPHICS_STANDARDPLOTITEM_H
