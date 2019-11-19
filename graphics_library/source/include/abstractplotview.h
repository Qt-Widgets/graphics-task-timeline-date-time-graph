#ifndef GRAPHICS_ABSTRACTPLOTVIEW_H
#define GRAPHICS_ABSTRACTPLOTVIEW_H

/*!
  * \file abstractplotview.h
  * \brief Объявление базового класса для виджета отображения графика.
  *
  * \file abstractplotview.cpp
  * \brief Реализация базового класса для виджета отображения графика.
  */

#include <QGraphicsView>
#include "commonprerequisites.h"

namespace Graphics {

//! Базовый класс для виджета отображения графика.
class GRAPHICS_EXPORT AbstractPlotView : public QGraphicsView {
    Q_OBJECT
protected:
    //! Конструктор с установкой родительского виджета \c parent.
    explicit AbstractPlotView(QWidget *parent = 0);
public:
    //! Деструктор.
    virtual ~AbstractPlotView();

    //! Графическая сцена.
    virtual AbstractPlotScene *plotScene() const = 0;
    //! Смена графической сцены на \c plot_scene.
    virtual void setPlotScene(AbstractPlotScene *plot_scene) = 0;

    //! Прокрутка графика к значениям шкал \c scale_values.
    virtual void scrollTo(const QPointF &scale_values) = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTPLOTVIEW_H
