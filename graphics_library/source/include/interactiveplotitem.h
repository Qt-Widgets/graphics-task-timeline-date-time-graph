#ifndef GRAPHICS_INTERACTIVEPLOTITEM_H
#define GRAPHICS_INTERACTIVEPLOTITEM_H

/*!
  * \file interactiveplotitem.h
  * \brief Объявление класса интерактивного элемента графика.
  *
  * \file interactiveplotitem.cpp
  * \brief Реализация класса интерактивного элемента графика.
  */

#include "commonprerequisites.h"
#include "standardplotitem.h"

namespace Graphics {

//! Флаги типов пользовательского взаимодействия с элементом графика.
enum PlotItemInteractionFlag {
    //! Взаимодействие не поддерживается.
    InteractionNo = 0x00,
    //! Элемент можно перемещать.
    InteractionMove = 0x01,
    //! Элемент отслеживает положение курсора мыши в своей области.
    InteractionHover = 0x02,
    //! Элемент определяет нажатие кнопок мыши.
    InteractionClick = 0x04,
    //! Элемент определяет запрос контекстного меню.
    InteractionContext = 0x08,
    //! Элемент поддерживает выделение.
    InteractionSelect = 0x10,
    //! Элемент поддерживает все типы взаимодействия.
    InteractionAll = 0x1f
};

Q_DECLARE_FLAGS(PlotItemInteractionFlags, PlotItemInteractionFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(PlotItemInteractionFlags)

class InteractivePlotItemPrivate;

//! Элемент графика, поддерживающий пользовательское взаимодействие.
class GRAPHICS_EXPORT InteractivePlotItem : public StandardPlotItem {
    Q_DECLARE_PRIVATE(InteractivePlotItem)

    //! Указатель на реализацию.
    InteractivePlotItemPrivate * const d_ptr;
public:
    //! Конструктор с флагами типов поддерживаемых взаимодействий.
    InteractivePlotItem(PlotItemInteractionFlags interaction_flags = InteractionAll);
    //! Деструктор.
    ~InteractivePlotItem();

    //! Флаги поддерживаемых типов взаимодействия.
    PlotItemInteractionFlags interactionFlags() const;
    //! Установка флага типа взаимодействия \c interaction_flag в значение \c on.
    void setInteractionFlag(PlotItemInteractionFlag interaction_flag, bool on = true);
    //! Установка флагов поддерживаемых типов взаимодействия в \c interaction_flags.
    void setInteractionFlags(PlotItemInteractionFlags interaction_flags);

    //! Отключение стандартных обработчиков событий взаимодействия \с interaction_flags.
    void setSuppressedDefaultEvents(PlotItemInteractionFlags interaction_flags);
protected:
    //! Обработка события вхождения курсора мыши в область элемента в точке \c item_pos.
    virtual void onHoverEnter(const QPointF &item_pos);
    //! Обработка события движения курсора мыши в области элемента в точке \c item_pos.
    virtual void onHoverMove(const QPointF &item_pos);
    //! Обработка события выхода курсора мыши из области элемента в точке \c item_pos.
    virtual void onHoverLeave(const QPointF &item_pos);

    //! Обработка события двойного нажатия кнопки мыши \c button в точке \c item_pos.
    virtual void onMouseDoubleClick(const QPointF &item_pos, Qt::MouseButton button);
    //! Обработка события движение курсора с зажатой кнопкой мыши \c button в точке \c item_pos.
    virtual void onMouseMove(const QPointF &item_pos, Qt::MouseButton button);
    //! Обработка события нажатия кнопки мыши \c button в точке \c item_pos.
    virtual void onMousePress(const QPointF &item_pos, Qt::MouseButton button);
    //! Обработка события отпускания кнопки мыши \c button в точке \c item_pos.
    virtual void onMouseRelease(const QPointF &item_pos, Qt::MouseButton button);

    //! Обработка события вызова контекстного меню в точке \c item_pos.
    virtual void onContextMenu(const QPointF &item_pos);
private:
    //! Стандартный обработчик события \c event вхождения курсора мыши в область элемента.
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //! Стандартный обработчик события \c event движения курсора мыши в области элемента.
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    //! Стандартный обработчик события \c event выхода курсора мыши из области элемента.
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    //! Стандартный обработчик события \c event двойного нажатия кнопки мыши.
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //! Стандартный обработчик события \c event движение курсора с зажатой кнопкой мыши.
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //! Стандартный обработчик события \c event нажатия кнопки мыши.
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //! Стандартный обработчик события \c event отпускания кнопки мыши.
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //! Стандартный обработчик события \c event вызова контекстного меню.
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

} // namespace Graphics

#endif // GRAPHICS_INTERACTIVEPLOTITEM_H
