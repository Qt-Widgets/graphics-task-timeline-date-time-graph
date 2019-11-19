#ifndef GRAPHICS_ABSTRACTPLOTLAYOUT_H
#define GRAPHICS_ABSTRACTPLOTLAYOUT_H

/*!
  * \file abstractplotlayout.h
  * \brief Объявление базового класса для позоционирования элементов графика.
  */

#include <QObject>
#include "commonprerequisites.h"

namespace Graphics {

//! Базовый класс для позиционирования объектов на графике.
class GRAPHICS_EXPORT AbstractPlotLayout {
    Q_DISABLE_COPY(AbstractPlotLayout)
protected:
    //! Конструктор.
    AbstractPlotLayout() {}
public:
    //! Деструктор.
    virtual ~AbstractPlotLayout() {}

    //! Сцена графика.
    virtual AbstractPlotScene *plotScene() const = 0;
    //! Смена сцены графика на \c plot_scene.
    virtual void setPlotScene(AbstractPlotScene *plot_scene) = 0;

    //! Пересчет позиций всех элементов графика.
    virtual void refresh() = 0;
    //! Пересчет позиции элемента \c item.
    virtual void refresh(AbstractPlotItem *item) = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTPLOTLAYOUT_H
