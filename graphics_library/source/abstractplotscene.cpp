#include "include/abstractplotscene.h"


namespace Graphics {

AbstractPlotScene::AbstractPlotScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

AbstractPlotScene::~AbstractPlotScene()
{
}

void AbstractPlotScene::visualize(const QRectF &visible_scene_rect)
{
    Q_UNUSED(visible_scene_rect);
}

void AbstractPlotScene::scrollBack(const QRectF &visible_scene_rect)
{
    Q_UNUSED(visible_scene_rect);
}

void AbstractPlotScene::scrollForward(const QRectF &visible_scene_rect)
{
    Q_UNUSED(visible_scene_rect);
}

void AbstractPlotScene::scrollTo(const QRectF &visible_scene_rect, const QPointF &scale_values)
{
    Q_UNUSED(visible_scene_rect);
    Q_UNUSED(scale_values);
}

void AbstractPlotScene::plotItemHoverEnter(AbstractPlotItem *item, const QPointF &scene_pos)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
}

void AbstractPlotScene::plotItemHoverMove(AbstractPlotItem *item, const QPointF &scene_pos)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
}

void AbstractPlotScene::plotItemHoverLeave(AbstractPlotItem *item, const QPointF &scene_pos)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
}

void AbstractPlotScene::plotItemDoubleClick(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
    Q_UNUSED(button);
}

void AbstractPlotScene::plotItemMouseMove(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
    Q_UNUSED(button);
}

void AbstractPlotScene::plotItemMousePress(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
    Q_UNUSED(button);
}

void AbstractPlotScene::plotItemMouseRelease(AbstractPlotItem *item, const QPointF &scene_pos, Qt::MouseButton button)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
    Q_UNUSED(button);
}

void AbstractPlotScene::plotItemContextMenu(AbstractPlotItem *item, const QPointF &scene_pos)
{
    Q_UNUSED(item);
    Q_UNUSED(scene_pos);
}

} // namespace Graphics
