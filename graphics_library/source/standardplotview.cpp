#include <QWheelEvent>
#include <QScrollBar>

#include "include/standardplotview.h"
#include "include/abstractplotscene.h"
#include "include/abstractscale.h"


namespace Graphics {

//! Реализация класса виджета для отображения графика.
class StandardPlotViewPrivate {
    Q_DECLARE_PUBLIC(StandardPlotView)

    //! Указатель на объявление.
    StandardPlotView *q_ptr;

    //! Графическая сцена.
    AbstractPlotScene *plot_scene;
    //! Флаг возможности масштабирования графика.
    bool is_zoom_enabled;
    //! Клавиша-модификатор для масштабирования.
    Qt::KeyboardModifier zoom_key_modifier;

    //! Кэш текущей отображаемой позиции на графике.
    QPointF update_cache_view_position;

    //! Конструктор.
    StandardPlotViewPrivate(StandardPlotView *q) :
        q_ptr(q),
        plot_scene(0),
        is_zoom_enabled(false),
        zoom_key_modifier(Qt::ControlModifier)
    {}

    //! Деструктор.
    ~StandardPlotViewPrivate() {}

    //! Метод начала обновления графической сцены.
    void beginSceneUpdate();
    //! Метод завершения обновления графической сцены.
    void endSceneUpdate();
};

void StandardPlotViewPrivate::beginSceneUpdate()
{
    Q_Q(StandardPlotView);

    if (plot_scene != 0)
        update_cache_view_position = plot_scene->mapToScales(q->mapToScene(q->viewport()->rect().center()));
}

void StandardPlotViewPrivate::endSceneUpdate()
{
    Q_Q(StandardPlotView);

    if (plot_scene != 0) {
        q->centerOn(plot_scene->mapFromScales(update_cache_view_position));
        plot_scene->visualize(q->mapToScene(q->viewport()->rect()).boundingRect());
    }
}


StandardPlotView::StandardPlotView(QWidget *parent) :
    AbstractPlotView(parent),
    d_ptr(new StandardPlotViewPrivate(this))
{
    setPlotSceneOrientation(Qt::Horizontal);
}

StandardPlotView::~StandardPlotView()
{
    delete d_ptr;
}

AbstractPlotScene *StandardPlotView::plotScene() const
{
    Q_D(const StandardPlotView);
    return d->plot_scene;
}

void StandardPlotView::setPlotScene(AbstractPlotScene *plot_scene)
{
    Q_D(StandardPlotView);
    if (d->plot_scene != plot_scene) {
        d->plot_scene = plot_scene;
        d->plot_scene->resetZoom();
        AbstractPlotView::setScene(d->plot_scene);

        if (d->plot_scene != 0)
            setPlotSceneOrientation(d->plot_scene->sceneOrientation());
    }
}

Qt::Orientation StandardPlotView::plotSceneOrientation() const
{
    Q_D(const StandardPlotView);
    return d->plot_scene->sceneOrientation();
}

void StandardPlotView::setPlotSceneOrientation(Qt::Orientation orientation)
{
    Q_D(StandardPlotView);

    if (d->plot_scene == 0)
        return;

    d->plot_scene->setSceneOrientation(orientation);

    d->plot_scene->resetZoom();

    setHorizontalScrollBarPolicy((orientation == Qt::Horizontal) ? Qt::ScrollBarAlwaysOff
                                                                 : Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy((orientation == Qt::Vertical) ? Qt::ScrollBarAlwaysOff
                                                             : Qt::ScrollBarAsNeeded);
}

bool StandardPlotView::isZoomEnabled() const
{
    Q_D(const StandardPlotView);
    return d->is_zoom_enabled;
}

void StandardPlotView::setZoomEnabled(bool on)
{
    Q_D(StandardPlotView);
    d->is_zoom_enabled = on;
}

Qt::KeyboardModifier StandardPlotView::zoomKeyboardModifier() const
{
    Q_D(const StandardPlotView);
    return d->zoom_key_modifier;
}

void StandardPlotView::setZoomKeyboardModifier(Qt::KeyboardModifier modifier)
{
    Q_D(StandardPlotView);
    d->zoom_key_modifier = modifier;
}

void StandardPlotView::scrollPlot(int steps_count)
{
    Q_D(StandardPlotView);

    if (d->plot_scene == 0)
        return;

    QScrollBar *active_scroll_bar = (d->plot_scene->sceneOrientation() == Qt::Horizontal)
                                    ? horizontalScrollBar()
                                    : verticalScrollBar();

    active_scroll_bar->setValue(active_scroll_bar->value() - steps_count * active_scroll_bar->singleStep());

    d->beginSceneUpdate();

    QRectF visible_scene_rect = mapToScene(viewport()->rect()).boundingRect();

    if (steps_count > 0)
        d->plot_scene->scrollBack(visible_scene_rect);
    else
        d->plot_scene->scrollForward(visible_scene_rect);

    d->endSceneUpdate();
}

void StandardPlotView::zoomIn()
{
    Q_D(StandardPlotView);
    if (d->plot_scene != 0) {
        QRectF view_rect = mapToScene(viewport()->rect()).boundingRect();
        QPointF cursor_pos = mapToScene(viewport()->mapFromGlobal(QCursor::pos()));
        QPointF cursor_value = d->plot_scene->mapToScales(cursor_pos);

        d->plot_scene->zoomIn();

        QPointF new_cursor_pos = d->plot_scene->mapFromScales(cursor_value);
        QPointF offset = cursor_pos - new_cursor_pos;
        QRectF new_view_rect = view_rect.translated(-offset);

        ensureVisible(new_view_rect, 0, 0);
    }
}

void StandardPlotView::zoomOut()
{
    Q_D(StandardPlotView);
    if (d->plot_scene != 0) {
        QRectF view_rect = mapToScene(viewport()->rect()).boundingRect();
        QPointF cursor_pos = mapToScene(viewport()->mapFromGlobal(QCursor::pos()));
        QPointF cursor_value = d->plot_scene->mapToScales(cursor_pos);

        d->plot_scene->zoomOut();

        QPointF new_cursor_pos = d->plot_scene->mapFromScales(cursor_value);
        QPointF offset = cursor_pos - new_cursor_pos;
        QRectF new_view_rect = view_rect.translated(-offset);

        ensureVisible(new_view_rect, 0, 0);
    }
}

void StandardPlotView::scrollTo(const QPointF &scale_values)
{
    Q_D(StandardPlotView);
    if (d->plot_scene != 0) {
        QRectF view_scene_geometry = mapToScene(viewport()->rect()).boundingRect();

        d->plot_scene->scrollTo(view_scene_geometry, scale_values);

        centerOn(d->plot_scene->mapFromScales(scale_values));

        QRectF new_view_scene_geometry = mapToScene(viewport()->rect()).boundingRect();
        d->plot_scene->visualize(new_view_scene_geometry);
    }
}

void StandardPlotView::showEvent(QShowEvent *event)
{
    AbstractPlotView::showEvent(event);
    if (!event->spontaneous())
        scrollPlot(0);
}

void StandardPlotView::wheelEvent(QWheelEvent *event)
{
    Q_D(StandardPlotView);

    if (d->plot_scene == 0)
        return;

    int degrees_count = event->delta() / 8;
    int steps_count = degrees_count / 15;

    if (event->modifiers().testFlag(Qt::NoModifier))
        scrollPlot(steps_count);

    if (event->modifiers().testFlag(d->zoom_key_modifier) && d->is_zoom_enabled) {
        if (event->delta() < 0) {
            zoomIn();
            d->plot_scene->refresh();
        }
        if (event->delta() > 0) {
            zoomOut();
            d->plot_scene->refresh();
        }
    }
}

} // namespace Graphics
