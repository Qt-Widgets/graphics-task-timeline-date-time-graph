#include <QList>

#include "include/standardplotlayout.h"
#include "include/abstractplotscene.h"
#include "include/abstractscale.h"
#include "include/abstractplotitem.h"


namespace Graphics {

//! реализация класса для позиционирования объектов на графике.
class StandardPlotLayoutPrivate {
    friend class StandardPlotLayout;

    //! Графическая сцена.
    AbstractPlotScene *plot_scene;

    //! Конструктор.
    StandardPlotLayoutPrivate() : plot_scene(0) {}
    //! Деструктор.
    ~StandardPlotLayoutPrivate() {}
};



StandardPlotLayout::StandardPlotLayout() :
    AbstractPlotLayout(),
    d_ptr(new StandardPlotLayoutPrivate())
{
}

StandardPlotLayout::~StandardPlotLayout()
{
    delete d_ptr;
}

AbstractPlotScene *StandardPlotLayout::plotScene() const
{
    Q_D(const StandardPlotLayout);
    return d->plot_scene;
}

void StandardPlotLayout::setPlotScene(AbstractPlotScene *plot_scene)
{
    Q_D(StandardPlotLayout);
    d->plot_scene = plot_scene;
}

void StandardPlotLayout::refresh()
{
    Q_D(StandardPlotLayout);

    if (d->plot_scene == 0)
        return;

    if ((d->plot_scene->xScale() == 0) || (d->plot_scene->yScale() == 0))
        return;

    d->plot_scene->setSceneRect(0.0, 0.0, d->plot_scene->xScale()->length(), d->plot_scene->yScale()->length());

    foreach (AbstractPlotItem *item, d->plot_scene->plotItems())
        refresh(item);
}

void StandardPlotLayout::refresh(AbstractPlotItem *item)
{
    Q_D(StandardPlotLayout);

    if ((d->plot_scene == 0) || (item == 0))
        return;

    if ((d->plot_scene->xScale() == 0) || (d->plot_scene->yScale() == 0))
        return;

    if (item->isWidthCalculated()) {
        const double item_width = d->plot_scene->xScale()->distance(item->beginCoordinateX(),
                                                                    item->endCoordinateX());
        item->setWidth(item_width);
    }

    if (item->isHeightCalculated()) {
        const double item_height = d->plot_scene->yScale()->distance(item->beginCoordinateY(),
                                                                     item->endCoordinateY());
        item->setHeight(item_height);
    }

    const double item_pos_x = d->plot_scene->xScale()->position(item);
    const double item_pos_y = d->plot_scene->yScale()->position(item);

    item->setPos(item_pos_x, item_pos_y);

    item->update();
}

} // namespace Graphics
