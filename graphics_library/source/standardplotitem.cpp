#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "include/standardplotitem.h"


namespace Graphics {

//! Реализация класса элемента графика.
class StandardPlotItemPrivate {
    friend class StandardPlotItem;

    //! Графическая сцена.
    AbstractPlotScene *plot_scene;

    //! X-координата начала элемента.
    double begin_coodrinate_x;
    //! Y-координата начала элемента.
    double begin_coodrinate_y;
    //! X-координата конца элемента.
    double end_coordinate_x;
    //! Y-координата конца элемента.
    double end_coordinate_y;

    //! Флаг необходимости расчета ширины элемента на основе его координат.
    bool is_width_calculated;
    //! Флаг необходимости расчета высоты элемента на основе его координат.
    bool is_height_calculated;

    //! Размер элемента.
    QSizeF size;

    //! Конструктор.
    StandardPlotItemPrivate() :
        plot_scene(0),
        begin_coodrinate_x(0.0), begin_coodrinate_y(0.0),
        end_coordinate_x(0.0), end_coordinate_y(0.0),
        is_width_calculated(true), is_height_calculated(true),
        size()
    {}

    //! Деструктор.
    ~StandardPlotItemPrivate() {}
};



StandardPlotItem::StandardPlotItem() :
    AbstractPlotItem(),
    d_ptr(new StandardPlotItemPrivate())
{
}

StandardPlotItem::~StandardPlotItem()
{
    delete d_ptr;
}

QPointF StandardPlotItem::beginCoordinates() const
{
    return QPointF(beginCoordinateX(), beginCoordinateY());
}

void StandardPlotItem::setBeginCoordinates(double x, double y)
{
    setBeginCoordinateX(x);
    setBeginCoordinateY(y);
}

void StandardPlotItem::setBeginCoordinates(const QPointF &coordinates)
{
    setBeginCoordinateX(coordinates.x());
    setBeginCoordinateY(coordinates.y());
}

double StandardPlotItem::beginCoordinateX() const
{
    Q_D(const StandardPlotItem);
    return d->begin_coodrinate_x;
}

void StandardPlotItem::setBeginCoordinateX(double x)
{
    Q_D(StandardPlotItem);
    d->begin_coodrinate_x = x;
}

double StandardPlotItem::beginCoordinateY() const
{
    Q_D(const StandardPlotItem);
    return d->begin_coodrinate_y;
}

void StandardPlotItem::setBeginCoordinateY(double y)
{
    Q_D(StandardPlotItem);
    d->begin_coodrinate_y = y;
}

QPointF StandardPlotItem::endCoordinates() const
{
    return QPointF(endCoordinateX(), endCoordinateY());
}

void StandardPlotItem::setEndCoordinates(double x, double y)
{
    setEndCoordinateX(x);
    setEndCoordinateY(y);
}

void StandardPlotItem::setEndCoordinates(const QPointF &coordinates)
{
    setEndCoordinateX(coordinates.x());
    setEndCoordinateY(coordinates.y());
}

double StandardPlotItem::endCoordinateX() const
{
    Q_D(const StandardPlotItem);
    return d->end_coordinate_x;
}

void StandardPlotItem::setEndCoordinateX(double x)
{
    Q_D(StandardPlotItem);
    d->end_coordinate_x = x;
}

double StandardPlotItem::endCoordinateY() const
{
    Q_D(const StandardPlotItem);
    return d->end_coordinate_y;
}

void StandardPlotItem::setEndCoordinateY(double y)
{
    Q_D(StandardPlotItem);
    d->end_coordinate_y = y;
}

bool StandardPlotItem::isWidthCalculated() const
{
    Q_D(const StandardPlotItem);
    return d->is_width_calculated;
}

void StandardPlotItem::setWidthCalculated(bool on)
{
    Q_D(StandardPlotItem);
    d->is_width_calculated = on;
}

bool StandardPlotItem::isHeightCalculated() const
{
    Q_D(const StandardPlotItem);
    return d->is_height_calculated;
}

void StandardPlotItem::setHeightCalculated(bool on)
{
    Q_D(StandardPlotItem);
    d->is_height_calculated = on;
}

QSizeF StandardPlotItem::size() const
{
    Q_D(const StandardPlotItem);
    return d->size;
}

void StandardPlotItem::setSize(double width, double height)
{
    setSize(QSizeF(width, height));
}

void StandardPlotItem::setSize(const QSizeF &size)
{
    Q_D(StandardPlotItem);
    if (d->size != size) {
        prepareGeometryChange();
        d->size = size;
    }
}

double StandardPlotItem::width() const
{
    return size().width();
}

void StandardPlotItem::setWidth(double width)
{
    setSize(width, height());
}

double StandardPlotItem::height() const
{
    return size().height();
}

void StandardPlotItem::setHeight(double height)
{
    setSize(width(), height);
}

AbstractPlotScene *StandardPlotItem::plotScene() const
{
    Q_D(const StandardPlotItem);
    return d->plot_scene;
}

void StandardPlotItem::setPlotScene(AbstractPlotScene *plot_scene)
{
    Q_D(StandardPlotItem);
    d->plot_scene = plot_scene;
}

QRectF StandardPlotItem::boundingRect() const
{
    Q_D(const StandardPlotItem);
    return QRectF(QPointF(- d->size.width() * 0.5, - d->size.height() * 0.5), d->size);
}

} // namespace Graphics
