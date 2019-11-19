#ifndef GRAPHICS_STANDARDPLOTLAYOUT_H
#define GRAPHICS_STANDARDPLOTLAYOUT_H

/*!
  * \file standardplotlayout.h
  * \brief Объявление класса для позиционирования объектов на графике.
  *
  * \file standardplotlayout.cpp
  * \brief Реализация класса для позиционирования объектов на графике.
  */

#include "commonprerequisites.h"
#include "abstractplotlayout.h"

namespace Graphics {

class StandardPlotLayoutPrivate;

//! Класс для позиционирования объектов на графике.
class GRAPHICS_EXPORT StandardPlotLayout : public AbstractPlotLayout {
    Q_DISABLE_COPY(StandardPlotLayout)
    Q_DECLARE_PRIVATE(StandardPlotLayout)

    //! Указатель на реализацию.
    StandardPlotLayoutPrivate * const d_ptr;
public:
    //! Конструктор.
    StandardPlotLayout();
    //! Деструктор.
    ~StandardPlotLayout();

    AbstractPlotScene *plotScene() const;
    void setPlotScene(AbstractPlotScene *plot_scene);

    void refresh();
    void refresh(AbstractPlotItem *item);
};

} // namespace Graphics

#endif // GRAPHICS_STANDARDPLOTLAYOUT_H
