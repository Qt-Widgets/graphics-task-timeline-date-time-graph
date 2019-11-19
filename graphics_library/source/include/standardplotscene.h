#ifndef GRAPHICS_STANDARDPLOTSCENE_H
#define GRAPHICS_STANDARDPLOTSCENE_H

/*!
  * \file standardplotscene.h
  * \brief Объявление класса сцены графика.
  *
  * \file standardplotscene.cpp
  * \brief Реализация класса сцены графика.
  */

#include "commonprerequisites.h"
#include "abstractplotscene.h"

namespace Graphics {

class StandardPlotScenePrivate;

//! Класс сцены графика.
class GRAPHICS_EXPORT StandardPlotScene : public AbstractPlotScene {
    Q_OBJECT
    Q_DECLARE_PRIVATE(StandardPlotScene)

    //! Указатель на реализацию.
    StandardPlotScenePrivate * const d_ptr;
public:
    //! Конструктор с установкой родительского объекта \c parent.
    explicit StandardPlotScene(QObject *parent);
    //! Деструктор.
    ~StandardPlotScene();

    AbstractScale *xScale() const;
    void setXScale(AbstractScale *scale);

    AbstractScale *yScale() const;
    void setYScale(AbstractScale *scale);

    AbstractPlotLayout *layout() const;
    void setLayout(AbstractPlotLayout *layout);

    Qt::Orientation sceneOrientation() const;
    void setSceneOrientation(Qt::Orientation orientation);

    double zoomExtent() const;
    void setZoomExtent(double extent);

    void addPlotItem(AbstractPlotItem *item);
    void removePlotItem(AbstractPlotItem *item);

    QList<AbstractPlotItem *> plotItems() const;
    QList<AbstractPlotItem *> plotItems(const QPointF &scale_values, bool exact = true) const;
    QList<AbstractPlotItem *> plotItems(const QRectF &value_rect, bool exact = true) const;

    void refresh();
    void refresh(AbstractPlotItem *item);

    void zoomIn();
    void zoomOut();
    void resetZoom();

    int zoomStep() const;
    void setZoomStep(int step);

    int minimumZoomStep() const;
    void setMinimumZoomStep(int step);

    int maximumZoomStep() const;
    void setMaximumZoomStep(int step);

    QPointF mapToScales(const QPointF &scene_pos) const;
    QPointF mapFromScales(const QPointF &scale_values) const;
};

} // namespace Graphics

#endif // GRAPHICS_STANDARDPLOTSCENE_H
