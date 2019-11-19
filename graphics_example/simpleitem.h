#ifndef SIMPLEITEM_H
#define SIMPLEITEM_H

#include <QPainter>
#include <standardplotitem.h>

class SimpleItem : public Graphics::StandardPlotItem {
public:
    SimpleItem() : Graphics::StandardPlotItem() {}
    ~SimpleItem() {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->fillRect(boundingRect().adjusted(0.5, 0.5, -0.5, -0.5), Qt::gray);
    }
};

#endif // SIMPLEITEM_H
