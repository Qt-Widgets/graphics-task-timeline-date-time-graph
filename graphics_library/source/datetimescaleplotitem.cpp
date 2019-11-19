#include <QVector>
#include <QStringList>
#include <QDateTime>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QLineF>
#include <QDebug>

#include "include/datetimescaleplotitem.h"
#include "include/datetimescale.h"
#include "include/converter.h"
#include "include/datetimescaleengine.h"


namespace Graphics {

//! Реализация класса графического элемента для рисования временной шкалы.
class DateTimeScalePlotItemPrivate {
    Q_DECLARE_PUBLIC(DateTimeScalePlotItem)

    //! Указатель на объевление класса.
    DateTimeScalePlotItem *q_ptr;

    //! Движок рисования шкалы.
    AbstractScaleEngine *engine;
    //! Отображаемая временная шкала.
    DateTimeScale *datetime_scale;

    //! Флаг размещения подписей над шкалой.
    bool is_reverted;

    //! Шрифт подписей.
    QFont label_font;
    //! Перо для рисования подписей.
    QPen item_pen;

    //! Кэшированное значение минимального значения шкалы.
    double cached_minimum;
    //! Кэшированное значение максимального значения шкалы.
    double cached_maximum;
    //! Кэшированное значение длины шкалы.
    double cached_length;
    //! Кэшированное значение ориентации шкалы.
    Qt::Orientation cached_orientation;
    //! Кэшированное значение флага положения подписей шкалы.
    bool cached_revert;

    //! Размер засечки.
    double tick_size;
    //! Размер крупной засечки.
    double major_tick_size;
    //! Формат подписей.
    QString tick_label_format;

    //! Линии шкалы.
    QVector<QLineF> scale_lines;

    //! Конструктор с указателем на объявление \c q.
    DateTimeScalePlotItemPrivate(DateTimeScalePlotItem *q) :
        q_ptr(q), datetime_scale(0), is_reverted(false),
        cached_minimum(0.0), cached_maximum(0.0), cached_length(0.0),
        cached_orientation(Qt::Horizontal), cached_revert(false)
    {}

    //! Деструктор.
    ~DateTimeScalePlotItemPrivate() {}

    //! Проверка на необходимость пересчета кэшированных значений перед рисованием.
    bool needsPaintingCacheInvalidation() const
    {
        if (datetime_scale == 0)
            return false;

        if ((cached_minimum != datetime_scale->minimum()) ||
            (cached_maximum != datetime_scale->maximum()) ||
            (cached_length != datetime_scale->length()) ||
            (cached_orientation != datetime_scale->orientation()) ||
            (cached_revert != is_reverted))
        {
            return true;
        }

        return false;
    }

    //! Пересчет кэшированных значений с использование опции стиля \c option.
    void invalidatePaintingChache(const QStyleOptionGraphicsItem *option)
    {
        Q_Q(DateTimeScalePlotItem);

        scale_lines.clear();

        QRectF item_rect = q->boundingRect();

        engine->update(option->fontMetrics, item_rect, is_reverted);

        tick_size = 5.0;
        major_tick_size = 10.0;

        scale_lines.clear();

        if (datetime_scale->orientation() == Qt::Horizontal) {
            scale_lines.append(is_reverted ? QLineF(item_rect.bottomLeft(), item_rect.bottomRight())
                                           : QLineF(item_rect.topLeft(), item_rect.topRight()));

            const double y_origin = is_reverted ? item_rect.bottom() : item_rect.top();

            const double y_offset = is_reverted ? (y_origin - tick_size)
                                                : (y_origin + tick_size);

            const double y_major_offset = is_reverted ? (y_origin - major_tick_size)
                                                      : (y_origin + major_tick_size);

            foreach (const double tick_position, engine->tickPositions())
                scale_lines.append(QLineF(tick_position, y_origin, tick_position, y_offset));

            foreach (const double tick_position, engine->majorTickPositions())
                scale_lines.append(QLineF(tick_position, y_origin,tick_position, y_major_offset));
        }
        else {
            scale_lines.append(is_reverted ? QLineF(item_rect.topRight(), item_rect.bottomRight())
                                           : QLineF(item_rect.topLeft(), item_rect.bottomLeft()));

            const double x_origin = is_reverted ? item_rect.right() : item_rect.left();

            const double x_offset = is_reverted ? (x_origin - tick_size)
                                                : (x_origin + tick_size);

            const double x_major_offset = is_reverted ? (x_origin - major_tick_size)
                                                      : (x_origin + major_tick_size);

            foreach (const double tick_position, engine->tickPositions())
                scale_lines.append(QLineF(x_origin, tick_position, x_offset, tick_position));

            foreach (const double tick_position, engine->majorTickPositions())
                scale_lines.append(QLineF(x_origin, tick_position, x_major_offset, tick_position));
        }

        cached_minimum = datetime_scale->minimum();
        cached_maximum = datetime_scale->maximum();
        cached_length = datetime_scale->length();
        cached_orientation = datetime_scale->orientation();
        cached_revert = is_reverted;
    }

    void paintScaleLines(QPainter *painter, const QStyleOptionGraphicsItem *option)
    {
        Q_UNUSED(option);

        painter->drawLines(scale_lines.constData(), scale_lines.size());
    }

    void paintTickLabels(QPainter *painter, const QStyleOptionGraphicsItem *option)
    {
        Q_UNUSED(option);

        const QList<QString> major_tick_labels = engine->majorTickLabels();
        const QList<QRectF> major_tick_rects = engine->majorTickLabelRectangles();

        for (int i = 0; i < major_tick_labels.size(); ++ i) {
            painter->drawText(major_tick_rects.at(i),
                              Qt::AlignCenter,
                              major_tick_labels.at(i));
        }
    }
};



DateTimeScalePlotItem::DateTimeScalePlotItem(DateTimeScale *datetime_scale) :
    StandardPlotItem(),
    d_ptr(new DateTimeScalePlotItemPrivate(this))
{
    Q_D(DateTimeScalePlotItem);
    d->datetime_scale = datetime_scale;

    d->engine = new DateTimeScaleEngine();
    d->engine->setScale(datetime_scale);

    d->label_font.setPixelSize(11);
    d->item_pen = QPen(Qt::darkGray);
}

DateTimeScalePlotItem::~DateTimeScalePlotItem()
{
    Q_D(DateTimeScalePlotItem);
    delete d->engine;
    delete d_ptr;
}

double DateTimeScalePlotItem::beginCoordinateX() const
{
    Q_D(const DateTimeScalePlotItem);
    if (d->datetime_scale == 0)
        return StandardPlotItem::beginCoordinateX();
    return (d->datetime_scale->orientation() == Qt::Horizontal) ? d->datetime_scale->minimum()
                                                                : StandardPlotItem::beginCoordinateX();
}

double DateTimeScalePlotItem::beginCoordinateY() const
{
    Q_D(const DateTimeScalePlotItem);
    if (d->datetime_scale == 0)
        return StandardPlotItem::beginCoordinateY();
    return (d->datetime_scale->orientation() == Qt::Vertical) ? d->datetime_scale->minimum()
                                                              : StandardPlotItem::beginCoordinateY();
}

double DateTimeScalePlotItem::endCoordinateX() const
{
    Q_D(const DateTimeScalePlotItem);
    if (d->datetime_scale == 0)
        return StandardPlotItem::endCoordinateX();
    return (d->datetime_scale->orientation() == Qt::Horizontal) ? d->datetime_scale->maximum()
                                                                : StandardPlotItem::endCoordinateX();
}

double DateTimeScalePlotItem::endCoordinateY() const
{
    Q_D(const DateTimeScalePlotItem);
    if (d->datetime_scale == 0)
        return StandardPlotItem::endCoordinateY();
    return (d->datetime_scale->orientation() == Qt::Vertical) ? d->datetime_scale->maximum()
                                                              : StandardPlotItem::endCoordinateY();
}

bool DateTimeScalePlotItem::isReverted() const
{
    Q_D(const DateTimeScalePlotItem);
    return d->is_reverted;
}

void DateTimeScalePlotItem::setReverted(bool on)
{
    Q_D(DateTimeScalePlotItem);
    d->is_reverted = on;
}

DateTimeScale *DateTimeScalePlotItem::dateTimeScale() const
{
    Q_D(const DateTimeScalePlotItem);
    return d->datetime_scale;
}

void DateTimeScalePlotItem::setDateTimeScale(DateTimeScale *datetime_scale)
{
    Q_D(DateTimeScalePlotItem);
    if (d->datetime_scale != datetime_scale) {
        d->datetime_scale = datetime_scale;
        d->engine->setScale(datetime_scale);
        update();
    }
}

void DateTimeScalePlotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    Q_D(DateTimeScalePlotItem);

    if (d->datetime_scale == 0)
        return;

    if (d->needsPaintingCacheInvalidation())
        d->invalidatePaintingChache(option);

    painter->save();

    painter->setPen(d->item_pen);
    painter->setFont(d->label_font);

    d->paintScaleLines(painter, option);
    d->paintTickLabels(painter, option);

    painter->restore();
}

} // namespace Graphics
