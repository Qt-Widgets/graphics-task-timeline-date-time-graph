#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>

#include "include/interactiveplotitem.h"
#include "include/abstractplotscene.h"


namespace Graphics {

//! Реализация класса элемент графика, поддерживающего пользовательское взаимодействие.
class InteractivePlotItemPrivate {
    Q_DECLARE_PUBLIC(InteractivePlotItem)

    //! Указатель на объявление.
    InteractivePlotItem *q_ptr;

    //! Флаги поддерживаемых типов взаимодействия.
    PlotItemInteractionFlags interaction_flags;
    //! Флаги отключенных стандартных обработчиков событий.
    PlotItemInteractionFlags suppressed_default_events;

    //! Консруктор с указателем на объявление класса \c q.
    InteractivePlotItemPrivate(InteractivePlotItem *q) :
        q_ptr(q), interaction_flags(InteractionNo), suppressed_default_events(InteractionNo)
    {}

    //! Деструктор.
    ~InteractivePlotItemPrivate() {}

    //! Обновление флагов взаимодействия.
    void updateFlags();

    //! Установка флага перемещения элемента в значение \c on.
    void setMovable(bool on);
    //! Установка флага отслеживания перемещение курсора мыши в значение \c on.
    void setHoverable(bool on);
    //! Установка флага возможности нажатия кнопок мыши на элементе в значение \c on.
    void setClickable(bool on);
    //! Установка флага выделение элемента в значение \c on.
    void setSelectable(bool on);
};

void InteractivePlotItemPrivate::updateFlags()
{
    setMovable(interaction_flags.testFlag(InteractionMove));
    setHoverable(interaction_flags.testFlag(InteractionHover));
    setClickable(interaction_flags.testFlag(InteractionClick));
    setSelectable(interaction_flags.testFlag(InteractionSelect));
}

void InteractivePlotItemPrivate::setMovable(bool on)
{
    Q_Q(InteractivePlotItem);
    q->setFlag(QGraphicsItem::ItemIsMovable, on);
}

void InteractivePlotItemPrivate::setHoverable(bool on)
{
    Q_Q(InteractivePlotItem);
    q->setAcceptHoverEvents(on);
}

void InteractivePlotItemPrivate::setClickable(bool on)
{
    Q_Q(InteractivePlotItem);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    q->setAcceptedMouseButtons(on ? Qt::MouseButtons(Qt::AllButtons)
                                  : Qt::MouseButtons(Qt::NoButton));
#else
    q->setAcceptedMouseButtons(on ? Qt::MouseButtons(Qt::LeftButton | Qt::RightButton |
                                                     Qt::MiddleButton | Qt::XButton1 | Qt::XButton2)
                                  : Qt::MouseButtons(Qt::NoButton));
#endif
}

void InteractivePlotItemPrivate::setSelectable(bool on)
{
    Q_Q(InteractivePlotItem);
    q->setFlag(QGraphicsItem::ItemIsSelectable, on);
}



InteractivePlotItem::InteractivePlotItem(PlotItemInteractionFlags interaction_flags) :
    StandardPlotItem(),
    d_ptr(new InteractivePlotItemPrivate(this))
{
    setInteractionFlags(interaction_flags);
}

InteractivePlotItem::~InteractivePlotItem()
{
    delete d_ptr;
}

PlotItemInteractionFlags InteractivePlotItem::interactionFlags() const
{
    Q_D(const InteractivePlotItem);
    return d->interaction_flags;
}

void InteractivePlotItem::setInteractionFlag(PlotItemInteractionFlag interaction_flag, bool on)
{
    Q_D(InteractivePlotItem);
    if (on)
        d->interaction_flags |= interaction_flag;
    else
        d->interaction_flags &= ~interaction_flag;
    d->updateFlags();
}

void InteractivePlotItem::setInteractionFlags(PlotItemInteractionFlags interaction_flags)
{
    Q_D(InteractivePlotItem);
    d->interaction_flags = interaction_flags;
    d->updateFlags();
}

void InteractivePlotItem::setSuppressedDefaultEvents(PlotItemInteractionFlags interaction_flags)
{
    Q_D(InteractivePlotItem);
    d->suppressed_default_events = interaction_flags;
}

void InteractivePlotItem::onHoverEnter(const QPointF &item_pos)
{
    plotScene()->plotItemHoverEnter(this, mapToScene(item_pos));
}

void InteractivePlotItem::onHoverMove(const QPointF &item_pos)
{
    plotScene()->plotItemHoverMove(this, mapToScene(item_pos));
}

void InteractivePlotItem::onHoverLeave(const QPointF &item_pos)
{
    plotScene()->plotItemHoverLeave(this, mapToScene(item_pos));
}

void InteractivePlotItem::onMouseDoubleClick(const QPointF &item_pos, Qt::MouseButton button)
{
    plotScene()->plotItemDoubleClick(this, mapToScene(item_pos), button);
}

void InteractivePlotItem::onMouseMove(const QPointF &item_pos, Qt::MouseButton button)
{
    plotScene()->plotItemMouseMove(this, mapToScene(item_pos), button);
}

void InteractivePlotItem::onMousePress(const QPointF &item_pos, Qt::MouseButton button)
{
    plotScene()->plotItemMousePress(this, mapToScene(item_pos), button);
}

void InteractivePlotItem::onMouseRelease(const QPointF &item_pos, Qt::MouseButton button)
{
    plotScene()->plotItemMouseRelease(this, mapToScene(item_pos), button);
}

void InteractivePlotItem::onContextMenu(const QPointF &item_pos)
{
    plotScene()->plotItemContextMenu(this, mapToScene(item_pos));
}

void InteractivePlotItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionHover))
        StandardPlotItem::hoverEnterEvent(event);

    onHoverEnter(event->pos());
}

void InteractivePlotItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionHover))
        StandardPlotItem::hoverMoveEvent(event);

    onHoverMove(event->pos());

    // FIXME: receiving hover move event on mouse press, event if is not clickable
}

void InteractivePlotItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionHover))
        StandardPlotItem::hoverLeaveEvent(event);

    onHoverLeave(event->pos());
}

void InteractivePlotItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionClick))
        StandardPlotItem::mouseDoubleClickEvent(event);

    onMouseDoubleClick(event->pos(), event->button());
}

void InteractivePlotItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionMove))
        StandardPlotItem::mouseMoveEvent(event);

    onMouseMove(event->pos(), event->button());
}

void InteractivePlotItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionClick))
        StandardPlotItem::mousePressEvent(event);

    onMousePress(event->pos(), event->button());
}

void InteractivePlotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionClick))
        StandardPlotItem::mouseReleaseEvent(event);

    onMouseRelease(event->pos(), event->button());

    // FIXME: no release event if is not hoverable
}

void InteractivePlotItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_D(InteractivePlotItem);

    if (!d->suppressed_default_events.testFlag(InteractionContext))
        StandardPlotItem::contextMenuEvent(event);

    if (d->interaction_flags.testFlag(InteractionContext)) {
        event->accept();
        onContextMenu(event->pos());
    }

    // FIXME: receiving mouse click event after context menu hidden
}

} // namespace Graphics
