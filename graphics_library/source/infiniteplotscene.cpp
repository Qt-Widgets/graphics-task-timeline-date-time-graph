#include <QDateTime>

#include "include/converter.h"
#include "include/infiniteplotscene.h"
#include "include/abstractscale.h"


namespace Graphics {

//! Реализация сцены для графика с бесконечной прокруткой по одной из осей.
class InfinitePlotScenePrivate {
    friend class InfinitePlotScene;

    //! Конструктор.
    InfinitePlotScenePrivate() {}
    //! Деструктор.
    ~InfinitePlotScenePrivate() {}
};



InfinitePlotScene::InfinitePlotScene(QObject *parent) :
    StandardPlotScene(parent),
    d_ptr(new InfinitePlotScenePrivate())
{
}

InfinitePlotScene::~InfinitePlotScene()
{
    delete d_ptr;
}

void InfinitePlotScene::zoomIn()
{
    if (zoomStep() >= maximumZoomStep())
        return;

    setZoomStep(zoomStep() + 1);

    AbstractScale *active_scale = (sceneOrientation() == Qt::Horizontal) ? xScale() : yScale();
    if (active_scale == 0)
        return;

    const double old_scale_minimum = active_scale->minimum();
    const double old_scale_maximum = active_scale->maximum();

    const double value_zoom_extent = (zoomStep() == 0) ? zoomExtent()
                                                       : (zoomExtent() / double(qAbs(zoomStep())));

    // checking new scale range
    if ((active_scale->minimum() + value_zoom_extent) >= (active_scale->maximum() - value_zoom_extent))
        return;

    active_scale->setRange(active_scale->minimum() + value_zoom_extent,
                           active_scale->maximum() - value_zoom_extent);

    cleanup(old_scale_minimum, active_scale->minimum());
    cleanup(active_scale->maximum(), old_scale_maximum);
}

void InfinitePlotScene::zoomOut()
{
    if (zoomStep() <= minimumZoomStep())
        return;

    AbstractScale *active_scale = (sceneOrientation() == Qt::Horizontal) ? xScale() : yScale();
    if (active_scale == 0)
        return;

    const double old_scale_minimum = active_scale->minimum();
    const double old_scale_maximum = active_scale->maximum();

    const double value_zoom_extent = (zoomStep() == 0) ? zoomExtent()
                                                       : (zoomExtent() / double(qAbs(zoomStep())));

    active_scale->setRange(active_scale->minimum() - value_zoom_extent,
                           active_scale->maximum() + value_zoom_extent);

    populate(active_scale->minimum(), old_scale_minimum);
    populate(old_scale_maximum, active_scale->maximum());

    setZoomStep(zoomStep() - 1);
}

void InfinitePlotScene::scrollBack(const QRectF &visible_scene_rect)
{
    const QRectF scene_rect = sceneRect();

    double scene_visible_limit = 0.0;
    double scene_visible_pos = 0.0;
    AbstractScale *scroll_scale = 0;

    if (sceneOrientation() == Qt::Horizontal) {
        scene_visible_limit = scene_rect.left();
        scene_visible_pos = visible_scene_rect.left();
        scroll_scale = xScale();
    }
    else {
        scene_visible_limit = scene_rect.top();
        scene_visible_pos = visible_scene_rect.top();
        scroll_scale = yScale();
    }

    if (scroll_scale == 0)
        return;

    if (scene_visible_limit >= scene_visible_pos) {
        double old_minimum_value = scroll_scale->minimum();
        double old_maximum_value = scroll_scale->maximum();

        double extension_value = (old_maximum_value - old_minimum_value) * 0.5;

        double new_minimum_value = old_minimum_value - extension_value;
        double new_maximum_value = old_maximum_value - extension_value;

        cleanup(new_maximum_value, old_maximum_value);

        scroll_scale->setRange(new_minimum_value, new_maximum_value);

        populate(new_minimum_value, old_minimum_value);

        refresh();
    }
}

void InfinitePlotScene::scrollForward(const QRectF &visible_scene_rect)
{
    const QRectF scene_rect = sceneRect();

    double scene_visible_limit = 0.0;
    double scene_visible_pos = 0.0;
    AbstractScale *scroll_scale = 0;

    if (sceneOrientation() == Qt::Horizontal) {
        scene_visible_limit = scene_rect.right();
        scene_visible_pos = visible_scene_rect.right();
        scroll_scale = xScale();
    }
    else {
        scene_visible_limit = scene_rect.bottom();
        scene_visible_pos = visible_scene_rect.bottom();
        scroll_scale = yScale();
    }

    if (scroll_scale == 0)
        return;

    if (scene_visible_limit <= scene_visible_pos) {
        double old_minimum_value = scroll_scale->minimum();
        double old_maximum_value = scroll_scale->maximum();

        double extension_value = (old_maximum_value - old_minimum_value) * 0.5;

        double new_minimum_value = old_minimum_value + extension_value;
        double new_maximum_value = old_maximum_value + extension_value;

        cleanup(old_minimum_value, new_minimum_value);

        scroll_scale->setRange(new_minimum_value, new_maximum_value);

        populate(old_maximum_value, new_maximum_value);

        refresh();
    }
}

void InfinitePlotScene::scrollTo(const QRectF &visible_scene_rect, const QPointF &scale_values)
{
    const QRectF scene_rect = sceneRect();

    if (sceneOrientation() == Qt::Horizontal) {
        double scale_value = scale_values.x();

        double mid_value = xScale()->minimum() + (xScale()->maximum() - xScale()->minimum()) * 0.5;

        QRectF new_visible_rect = visible_scene_rect;
        new_visible_rect.moveCenter(QPointF(xScale()->position(scale_value),
                                            new_visible_rect.y()));

        double old_minimum_value = xScale()->minimum();
        double old_maximum_value = xScale()->maximum();

        double extension_value = (old_maximum_value - old_minimum_value) * 0.5;

        if (scale_value < mid_value) {
            if (scene_rect.left() == new_visible_rect.left()) {
                scrollBack(new_visible_rect);
            }
            else if (scene_rect.left() > new_visible_rect.left()) {
                double new_minimum_value = scale_value - extension_value;
                double new_maximum_value = scale_value + extension_value;

                cleanup(qMax(old_minimum_value, new_maximum_value), old_maximum_value);

                xScale()->setRange(new_minimum_value, new_maximum_value);

                populate(new_minimum_value, qMin(new_maximum_value, old_minimum_value));
            }
        }
        else {
            if (scene_rect.right() == new_visible_rect.right()) {
                scrollForward(new_visible_rect);
            }
            else if (scene_rect.right() < new_visible_rect.right()) {
                double new_minimum_value = scale_value - extension_value;
                double new_maximum_value = scale_value + extension_value;

                cleanup(old_minimum_value, qMin(new_minimum_value, old_maximum_value));

                xScale()->setRange(new_minimum_value, new_maximum_value);

                populate(qMax(new_minimum_value, old_maximum_value), new_maximum_value);
            }
        }
    }
    else {
        double scale_value = scale_values.y();

        double mid_value = yScale()->minimum() + (yScale()->maximum() - yScale()->minimum()) * 0.5;

        QRectF new_visible_rect = visible_scene_rect;
        new_visible_rect.moveCenter(QPointF(new_visible_rect.x(),
                                            yScale()->position(scale_value)));

        double old_minimum_value = yScale()->minimum();
        double old_maximum_value = yScale()->maximum();

        double extension_value = (old_maximum_value - old_minimum_value) * 0.5;

        if (scale_value < mid_value) {
            if (scene_rect.top() == new_visible_rect.top()) {
                scrollBack(new_visible_rect);
            }
            else if (scene_rect.top() > new_visible_rect.top()) {
                double new_minimum_value = scale_value - extension_value;
                double new_maximum_value = scale_value + extension_value;

                cleanup(qMax(old_minimum_value, new_maximum_value), old_maximum_value);

                yScale()->setRange(new_minimum_value, new_maximum_value);

                populate(new_minimum_value, qMin(new_maximum_value, old_minimum_value));
            }
        }
        else {
            if (scene_rect.bottom() == new_visible_rect.bottom()) {
                scrollForward(new_visible_rect);
            }
            else if (scene_rect.bottom() < new_visible_rect.bottom()) {
                double new_minimum_value = scale_value - extension_value;
                double new_maximum_value = scale_value + extension_value;

                cleanup(old_minimum_value, qMin(new_minimum_value, old_maximum_value));

                yScale()->setRange(new_minimum_value, new_maximum_value);

                populate(qMax(new_minimum_value, old_maximum_value), new_maximum_value);
            }
        }
    }
}

void InfinitePlotScene::cleanup(double begin_value, double end_value)
{
    Q_UNUSED(begin_value);
    Q_UNUSED(end_value);
}

void InfinitePlotScene::populate(double begin_value, double end_value)
{
    Q_UNUSED(begin_value);
    Q_UNUSED(end_value);
}

} // namespace Graphics
