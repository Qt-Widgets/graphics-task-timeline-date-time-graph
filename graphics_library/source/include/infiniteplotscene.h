#ifndef GRAPHICS_INFINITEPLOTSCENE_H
#define GRAPHICS_INFINITEPLOTSCENE_H

/*!
  * \file infiniteplotscene.h
  * \brief Объявление класса сцены для графика с бесконечной прокруткой по одной из осей.
  *
  * \file infiniteplotscene.cpp
  * \brief Реализация класса сцены для графика с бесконечной прокруткой по одной из осей.
  */

#include "commonprerequisites.h"
#include "standardplotscene.h"

namespace Graphics {

class InfinitePlotScenePrivate;

//! Сцена для графика с бесконечной прокруткой по одной из осей.
class GRAPHICS_EXPORT InfinitePlotScene : public StandardPlotScene {
    Q_OBJECT
    Q_DECLARE_PRIVATE(InfinitePlotScene)

    //! Указатель на реализацию.
    InfinitePlotScenePrivate * const d_ptr;
public:
    //! Конструктор с установкой родительского объекта \c parent.
    explicit InfinitePlotScene(QObject *parent = 0);
    //! Деструктор.
    ~InfinitePlotScene();

    void zoomIn();
    void zoomOut();

    void scrollBack(const QRectF &visible_scene_rect);
    void scrollForward(const QRectF &visible_scene_rect);

    void scrollTo(const QRectF &visible_scene_rect, const QPointF &scale_values);

    //! Виртуальный метод очистки области графика от \c begin_value до \c end_value.
    virtual void cleanup(double begin_value, double end_value);
    //! Виртуальный метод подгрузки данных графика в область от \c begin_value до \c end_value.
    virtual void populate(double begin_value, double end_value);
};

} // namespace Graphics

#endif // GRAPHICS_INFINITEPLOTSCENE_H
