#include "include/standardplotscene.h"
#include "include/abstractscale.h"
#include "include/abstractplotlayout.h"
#include "include/abstractplotitem.h"


namespace Graphics {

//! Реализация класса сцены графика.
class StandardPlotScenePrivate {
    friend class StandardPlotScene;

    //! Шкала X.
    AbstractScale *x_scale;
    //! Шкала Y.
    AbstractScale *y_scale;

    //! Объект позиционирования элементов на графике.
    AbstractPlotLayout *layout;

    //! Ориентация сцены.
    Qt::Orientation orientation;

    //! Приращение масштабирования.
    double zoom_extent;

    //! Текущий шаг масштабирования.
    int zoom_step;
    //! Минимальный шаг мастшабирования.
    int minimum_zoom_step;
    //! Максимальный шаг масштабирования.
    int maximum_zoom_step;

    //! Графические элементы.
    QList<AbstractPlotItem *> plot_items;

    //! Конструктор.
    StandardPlotScenePrivate() :
        x_scale(0), y_scale(0),
        layout(0),
        orientation(Qt::Horizontal),
        zoom_extent(100.0),
        zoom_step(0),
        minimum_zoom_step(-20),
        maximum_zoom_step(20)
    {}

    //! Деструктор.
    ~StandardPlotScenePrivate() {}
};



StandardPlotScene::StandardPlotScene(QObject *parent) :
    AbstractPlotScene(parent),
    d_ptr(new StandardPlotScenePrivate())
{
}

StandardPlotScene::~StandardPlotScene()
{
    Q_D(StandardPlotScene);

    if (d->x_scale != 0)
        delete d->x_scale;

    if (d->y_scale != 0)
        delete d->y_scale;

    if (d->layout != 0)
        delete d->layout;

    delete d_ptr;
}

AbstractScale *StandardPlotScene::xScale() const
{
    Q_D(const StandardPlotScene);
    return d->x_scale;
}

void StandardPlotScene::setXScale(AbstractScale *scale)
{
    Q_D(StandardPlotScene);
    d->x_scale = scale;
}

AbstractScale *StandardPlotScene::yScale() const
{
    Q_D(const StandardPlotScene);
    return d->y_scale;
}

void StandardPlotScene::setYScale(AbstractScale *scale)
{
    Q_D(StandardPlotScene);
    d->y_scale = scale;
}

AbstractPlotLayout *StandardPlotScene::layout() const
{
    Q_D(const StandardPlotScene);
    return d->layout;
}

void StandardPlotScene::setLayout(AbstractPlotLayout *layout)
{
    Q_D(StandardPlotScene);

    if (d->layout != 0)
        d->layout->setPlotScene(0);

    d->layout = layout;

    if (d->layout != 0)
        d->layout->setPlotScene(this);
}

Qt::Orientation StandardPlotScene::sceneOrientation() const
{
    Q_D(const StandardPlotScene);
    return d->orientation;
}

void StandardPlotScene::setSceneOrientation(Qt::Orientation orientation)
{
    Q_D(StandardPlotScene);
    d->orientation = orientation;
}

double StandardPlotScene::zoomExtent() const
{
    Q_D(const StandardPlotScene);
    return d->zoom_extent;
}

void StandardPlotScene::setZoomExtent(double extent)
{
    Q_D(StandardPlotScene);
    d->zoom_extent = extent;
}

void StandardPlotScene::addPlotItem(AbstractPlotItem *item)
{
    Q_D(StandardPlotScene);

    if (item == 0)
        return;

    if (d->layout == 0)
        return;

    if (d->plot_items.contains(item))
        return;

    d->plot_items.append(item);
    AbstractPlotScene::addItem(item);
    item->setPlotScene(this);
}

void StandardPlotScene::removePlotItem(AbstractPlotItem *item)
{
    Q_D(StandardPlotScene);

    int item_index = d->plot_items.indexOf(item);
    if (item_index != -1) {
        d->plot_items.removeAt(item_index);
        AbstractPlotScene::removeItem(item);
        item->setPlotScene(0);
    }
}

QList<AbstractPlotItem *> StandardPlotScene::plotItems() const
{
    Q_D(const StandardPlotScene);
    return d->plot_items;
}

QList<AbstractPlotItem *> StandardPlotScene::plotItems(const QPointF &scale_values, bool exact) const
{
    QPointF lookup_point = mapFromScales(scale_values);

    QList<QGraphicsItem *> graphics_items = items(lookup_point,
                                                  exact ? Qt::ContainsItemShape
                                                        : Qt::IntersectsItemShape,
                                                  Qt::AscendingOrder);
    QList<AbstractPlotItem *> result;

    foreach (QGraphicsItem *graphics_item, graphics_items) {
        AbstractPlotItem *plot_item = dynamic_cast<AbstractPlotItem *>(graphics_item);
        if (plot_item != 0)
            result.append(plot_item);
    }

    return result;
}

QList<AbstractPlotItem *> StandardPlotScene::plotItems(const QRectF &value_rect, bool exact) const
{
    QRectF lookup_rect(QPointF(xScale()->position(value_rect.left()), yScale()->position(value_rect.top())),
                       QPointF(xScale()->position(value_rect.right()), yScale()->position(value_rect.bottom())));

    QList<QGraphicsItem *> graphics_items = items(lookup_rect, exact ? Qt::ContainsItemShape
                                                                     : Qt::IntersectsItemShape);
    QList<AbstractPlotItem *> result;

    foreach (QGraphicsItem *graphics_item, graphics_items) {
        AbstractPlotItem *plot_item = dynamic_cast<AbstractPlotItem *>(graphics_item);
        if (plot_item != 0)
            result.append(plot_item);
    }

    return result;
}

void StandardPlotScene::refresh()
{
    Q_D(StandardPlotScene);

    if (d->layout != 0)
        d->layout->refresh();

    AbstractPlotScene::update();
}

void StandardPlotScene::refresh(AbstractPlotItem *item)
{
    Q_D(StandardPlotScene);

    if (d->layout != 0)
        d->layout->refresh(item);

    AbstractPlotScene::update();
}

void StandardPlotScene::zoomIn()
{
    Q_D(StandardPlotScene);

    if (d->zoom_step >= d->maximum_zoom_step)
        return;

    AbstractScale *active_scale = (d->orientation == Qt::Horizontal) ? d->x_scale : d->y_scale;
    if (active_scale == 0)
        return;

    active_scale->setLength(active_scale->length() + d->zoom_extent);

    setZoomStep(d->zoom_step + 1);
}

void StandardPlotScene::zoomOut()
{
    Q_D(StandardPlotScene);

    if (d->zoom_step <= d->minimum_zoom_step)
        return;

    AbstractScale *active_scale = (d->orientation == Qt::Horizontal) ? d->x_scale : d->y_scale;
    if (active_scale == 0)
        return;

    if ((active_scale->length() - d->zoom_extent) <= 0)
        return;

    active_scale->setLength(active_scale->length() - d->zoom_extent);

    setZoomStep(d->zoom_step - 1);
}

void StandardPlotScene::resetZoom()
{
    Q_D(StandardPlotScene);

    while (d->zoom_step < 0)
        zoomIn();
    while (d->zoom_step > 0)
        zoomOut();
}

int StandardPlotScene::zoomStep() const
{
    Q_D(const StandardPlotScene);
    return d->zoom_step;
}

void StandardPlotScene::setZoomStep(int step)
{
    Q_D(StandardPlotScene);
    d->zoom_step = step;
}

int StandardPlotScene::minimumZoomStep() const
{
    Q_D(const StandardPlotScene);
    return d->minimum_zoom_step;
}

void StandardPlotScene::setMinimumZoomStep(int step)
{
    Q_D(StandardPlotScene);
    d->minimum_zoom_step = step;
}

int StandardPlotScene::maximumZoomStep() const
{
    Q_D(const StandardPlotScene);
    return d->maximum_zoom_step;
}

void StandardPlotScene::setMaximumZoomStep(int step)
{
    Q_D(StandardPlotScene);
    d->maximum_zoom_step = step;
}

QPointF StandardPlotScene::mapToScales(const QPointF &scene_pos) const
{
    Q_D(const StandardPlotScene);

    QPointF res;

    if (d->x_scale != 0)
        res.setX(d->x_scale->value(scene_pos.x()));
    if (d->y_scale != 0)
        res.setY(d->y_scale->value(scene_pos.y()));

    return res;
}

QPointF StandardPlotScene::mapFromScales(const QPointF &scale_values) const
{
    Q_D(const StandardPlotScene);

    QPointF res;

    if (d->x_scale != 0)
        res.setX(d->x_scale->position(scale_values.x()));
    if (d->y_scale != 0)
        res.setY(d->y_scale->position(scale_values.y()));

    return res;
}

} // namespace Graphics
