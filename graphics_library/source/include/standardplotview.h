#ifndef GRAPHICS_STANDARDPLOTVIEW_H
#define GRAPHICS_STANDARDPLOTVIEW_H

/*!
  * \file standardplotview.h
  * \brief Объявление класса виджета для отображения графика.
  *
  * \file standardplotview.cpp
  * \brief Реализация класса виджета для отображения графика.
  */

#include "commonprerequisites.h"
#include "abstractplotview.h"

namespace Graphics {

class StandardPlotViewPrivate;

//! Класс виджета для отображения графика.
class GRAPHICS_EXPORT StandardPlotView : public AbstractPlotView {
    Q_OBJECT
    Q_DECLARE_PRIVATE(StandardPlotView)

    //! Указатель на реализацию.
    StandardPlotViewPrivate * const d_ptr;
public:
    //! Конструктор с установкой родительского виджета \c parent.
    explicit StandardPlotView(QWidget *parent = 0);
    //! Деструктор.
    ~StandardPlotView();

    AbstractPlotScene *plotScene() const;
    void setPlotScene(AbstractPlotScene *plot_scene);

    //! Ориентация графика.
    Qt::Orientation plotSceneOrientation() const;
    //! Смена ориентации графика на \c orientation.
    void setPlotSceneOrientation(Qt::Orientation orientation);

    //! Флаг возможности масштабирования графика.
    bool isZoomEnabled() const;
    //! Смена флага возможности масштабирования графика на \c on.
    void setZoomEnabled(bool on);

    //! Клавиша-модификатор для масштабирования.
    Qt::KeyboardModifier zoomKeyboardModifier() const;
    //! Смена клавиши-модификатора для масштабирования на \c modifier.
    void setZoomKeyboardModifier(Qt::KeyboardModifier modifier);

    //! Прокрутка графика на \c steps_count шагов.
    void scrollPlot(int steps_count);
    //! Увеличение масштаба графика.
    void zoomIn();
    //! Уменьшение масштаба графика.
    void zoomOut();

    void scrollTo(const QPointF &scale_values);
protected:
    //! Обработка события \c event отображения виджета графика.
    void showEvent(QShowEvent *event);
    //! Обработка события \c event прокрутки колеса мыши.
    void wheelEvent(QWheelEvent *event);
};

} // namespace Graphics

#endif // GRAPHICS_STANDARDPLOTVIEW_H
