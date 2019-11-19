#ifndef GRAPHICS_ABSTRACTPLOTSCENE_H
#define GRAPHICS_ABSTRACTPLOTSCENE_H

/*!
  * \file abstractplotscene.h
  * \brief Объявление базового класс сцены графика.
  *
  * \file abstractplotscene.cpp
  * \brief Реализация базового класса сцены графика.
  */

#include <QGraphicsScene>
#include "commonprerequisites.h"

namespace Graphics {

//! Базовый класс сцены графика.
class GRAPHICS_EXPORT AbstractPlotScene : public QGraphicsScene {
    Q_OBJECT
protected:
    //! Конструктор с установкой родительского объекта \c parent.
    explicit AbstractPlotScene(QObject *parent = 0);
public:
    //! Деструктор.
    virtual ~AbstractPlotScene();

    //! X-шкала графика.
    virtual AbstractScale *xScale() const = 0;
    //! Смена X-шкалы графика на \c scale.
    virtual void setXScale(AbstractScale *scale) = 0;

    //! Y-шкала графика.
    virtual AbstractScale *yScale() const = 0;
    //! Смена Y-шкалы графика на \c scale.
    virtual void setYScale(AbstractScale *scale) = 0;

    //! Объекта позиционирования элементов графика.
    virtual AbstractPlotLayout *layout() const = 0;
    //! Смена объекта позиционирования элементов графика на \c layout.
    virtual void setLayout(AbstractPlotLayout *layout) = 0;

    //! Ориентация графической сцены.
    virtual Qt::Orientation sceneOrientation() const = 0;
    //! Смена ориентации графической сцены на \c orientation.
    virtual void setSceneOrientation(Qt::Orientation orientation) = 0;

    //! Шаг масштабирования графика.
    virtual double zoomExtent() const = 0;
    //! Смена шага масштабирования графика на \c extent.
    virtual void setZoomExtent(double extent) = 0;

    //! Добавление элемента \c item на график.
    virtual void addPlotItem(AbstractPlotItem *item) = 0;
    //! Удаление элемента \c item с графика.
    virtual void removePlotItem(AbstractPlotItem *item) = 0;

    //! Элементы графика.
    virtual QList<AbstractPlotItem *> plotItems() const = 0;
    //! Элементы графика, расположенные в точке \c scale_values.
    virtual QList<AbstractPlotItem *> plotItems(const QPointF &scale_values, bool exact = true) const = 0;
    //! Элементы графика, расположенные в прямоугольнике \c value_rect.
    virtual QList<AbstractPlotItem *> plotItems(const QRectF &value_rect, bool exact = true) const = 0;

    //! Обновление графика.
    virtual void refresh() = 0;
    //! Обновление элемента \c item.
    virtual void refresh(AbstractPlotItem *item) = 0;

    //! Увеличение масштаба.
    virtual void zoomIn() = 0;
    //! Уменьшение масштаба.
    virtual void zoomOut() = 0;
    //! Сброс масштабирования.
    virtual void resetZoom() = 0;

    //! Текущий шаг масштабирования.
    virtual int zoomStep() const = 0;
    //! Смена текущего шага масштабирования на \c step.
    virtual void setZoomStep(int step) = 0;

    //! Минимальный шаг масштабирования.
    virtual int minimumZoomStep() const = 0;
    //! Смена мнимального шага масштабирования на \c step.
    virtual void setMinimumZoomStep(int step) = 0;

    //! Максимальный шаг масштабирования.
    virtual int maximumZoomStep() const = 0;
    //! Смена максимального шага масштабирования на \c step.
    virtual void setMaximumZoomStep(int step) = 0;

    //! Отображение прямоугольника \c visible_scene_rect на графике.
    virtual void visualize(const QRectF &visible_scene_rect);
    //! Прокрутка графика для отображения прямоугольника \c visible_scene_rect.
    virtual void scrollBack(const QRectF &visible_scene_rect);
    //! Прокрутка графика для отображения прямоугольника \c visible_scene_rect.
    virtual void scrollForward(const QRectF &visible_scene_rect);

    //! Прокутка графика с отображаемой областью \c visible_scene_rect в точку \c scale_values.
    virtual void scrollTo(const QRectF &visible_scene_rect, const QPointF &scale_values);

    //! Обработка вхождения курсора мыши в область элемента \c item в точке \c scene_pos.
    virtual void plotItemHoverEnter(AbstractPlotItem *item, const QPointF &scene_pos);
    //! Обработка движения курсора мыши в области элемента \c item в точке \c scene_pos.
    virtual void plotItemHoverMove(AbstractPlotItem *item, const QPointF &scene_pos);
    //! Обработка выхода курсора мыши из области элемента \c item в точке \c scene_pos.
    virtual void plotItemHoverLeave(AbstractPlotItem *item, const QPointF &scene_pos);

    //! Обработка двойного нажатия кнопки мыши \c button в области элемента \c item в точке \c scene_pos.
    virtual void plotItemDoubleClick(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button);
    //! Обработка движения с зажатой кнопкой мыши \c button в области элемента \c item в точке \c scene_pos.
    virtual void plotItemMouseMove(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button);
    //! Обработка нажатия кнопки мыши \c button в области элемента \c item в точке \c scene_pos.
    virtual void plotItemMousePress(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button);
    //! Обработка отпускания кнопки мыши \c button в области элемента \c item в точке \c scene_pos.
    virtual void plotItemMouseRelease(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button);

    //! Обработка вызова контекстного меню элемента \c item в точке \c scene_pos.
    virtual void plotItemContextMenu(AbstractPlotItem *item, const QPointF &scene_pos);

    //! Отображние точки сцены \c scene_pos в значения шкал графика.
    virtual QPointF mapToScales(const QPointF &scene_pos) const = 0;
    //! Отображение значений шкал графика \c scale_values в координаты сцены.
    virtual QPointF mapFromScales(const QPointF &scale_values) const = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTPLOTSCENE_H
