#include <QString>
#include <QRectF>
#include <QDateTime>
#include <QFontMetrics>

#include "include/datetimescaleengine.h"
#include "include/abstractscale.h"
#include "include/converter.h"


namespace Graphics {

//! Реализация класса движка рисования временной шкалы.
class DateTimeScaleEnginePrivate {
    friend class DateTimeScaleEngine;

    //! Интервал разбиения шкалы.
    enum SplitInterval {
        //! Не задан.
        IntervalNone,
        //! 1 секунда.
        IntervalSecond_1,
        //! 5 секунд.
        IntervalSecond_5,
        //! 10 секунд.
        IntervalSecond_10,
        //! 30 секунд.
        IntervalSecond_30,
        //! 1 минута.
        IntervalMinute_1,
        //! 5 минут.
        IntervalMinute_5,
        //! 10 минут.
        IntervalMinute_10,
        //! 30 минут.
        IntervalMinute_30,
        //! 1 час.
        IntervalHour_1,
        //! 2 часа.
        IntervalHour_2,
        //! 3 часа.
        IntervalHour_3,
        //! 4 часа.
        IntervalHour_4,
        //! 6 часов.
        IntervalHour_6,
        //! 12 часов.
        IntervalHour_12,
        //! 1 сутки.
        IntervalDay_1,
        //! 1 месяц.
        IntervalMonth_1,
        //! 3 месяца.
        IntervalMonth_3,
        //! 1 год.
        IntervalYear
    };

    //! Используемая шкала.
    AbstractScale *scale;

    //! Позиции засечек.
    QList<double> tick_positions;
    //! Позиции крупных засечек.
    QList<double> major_tick_positions;

    //! Подписи для крупных засечек.
    QList<QString> major_tick_labels;
    //! Положение подписей крупных засечек.
    QList<QRectF> major_tick_label_rectangles;

    //! Конструктор.
    DateTimeScaleEnginePrivate() : scale(0) {}
    //! Деструктор.
    ~DateTimeScaleEnginePrivate() {}

    //! Расстояние между датами \c from и \c to.
    double distance(const QDateTime &from, const QDateTime &to) const;

    //! Определение интервала разбиения шкалы на основе минимального расстояния между засечками \c minimum_tick_distance.
    SplitInterval interval(const double minimum_tick_distance = 5.0) const;

    //! Следующая за \c datetime дата, расчитанная на основе интевала разбиения \c interval и количества шагов между засечками \c tick_step.
    QDateTime nextDateTime(const QDateTime &datetime, SplitInterval interval, int tick_step = 1) const;

    //! Расстояние между засечками для интервала разбиения шкалы \c interval.
    double tickDistance(SplitInterval interval) const;

    //! Шаг крупных засечек для интервала разбиения \c interval.
    int majorTickStep(SplitInterval interval) const;

    //! Выравнивание даты \c datetime под интервал \c interval и шаг \c tick_step.
    QDateTime alignedToInterval(const QDateTime &datetime, SplitInterval interval, int tick_step) const;

    //! Формат подписи для крупных засечек при использовании интервала разбиения \c interval.
    QString majorTickLabelFormat(SplitInterval interval) const;
    //! Формат дополнительной подписи для крупных засечек при использовании интервала разбиения \c interval.
    QString majorTickSubLabelFormat(SplitInterval interval) const;

    /*!
     * \brief Флаг необходимости размещения дополнительной подписи для соседних засечек
     * \c prev_datetime и \c datetime при использовании интервала разбиения \c interval.
     */
    bool needsSubLabel(const QDateTime &prev_datetime, const QDateTime &datetime, SplitInterval interval) const;
};

double DateTimeScaleEnginePrivate::distance(const QDateTime &from, const QDateTime &to) const
{
    if (scale == 0)
        return 0.0;

    return scale->distance(Converter::toScale(from), Converter::toScale(to));
}

DateTimeScaleEnginePrivate::SplitInterval DateTimeScaleEnginePrivate::interval(const double minimum_tick_distance) const
{
    if (scale == 0)
        return IntervalNone;

    QDateTime scale_minimum = Converter::fromScale(scale->minimum());

    if (distance(scale_minimum, scale_minimum.addSecs(1)) > minimum_tick_distance)
        return IntervalSecond_1;

    if (distance(scale_minimum, scale_minimum.addSecs(5)) > minimum_tick_distance)
        return IntervalSecond_5;

    if (distance(scale_minimum, scale_minimum.addSecs(10)) > minimum_tick_distance)
        return IntervalSecond_10;

    if (distance(scale_minimum, scale_minimum.addSecs(30)) > minimum_tick_distance)
        return IntervalSecond_30;

    if (distance(scale_minimum, scale_minimum.addSecs(60)) > minimum_tick_distance)
        return IntervalMinute_1;

    if (distance(scale_minimum, scale_minimum.addSecs(300)) > minimum_tick_distance)
        return IntervalMinute_5;

    if (distance(scale_minimum, scale_minimum.addSecs(600)) > minimum_tick_distance)
        return IntervalMinute_10;

    if (distance(scale_minimum, scale_minimum.addSecs(1800)) > minimum_tick_distance)
        return IntervalMinute_30;

    if (distance(scale_minimum, scale_minimum.addSecs(3600)) > minimum_tick_distance)
        return IntervalHour_1;

    if (distance(scale_minimum, scale_minimum.addSecs(7200)) > minimum_tick_distance)
        return IntervalHour_2;

    if (distance(scale_minimum, scale_minimum.addSecs(10800)) > minimum_tick_distance)
        return IntervalHour_3;

    if (distance(scale_minimum, scale_minimum.addSecs(14400)) > minimum_tick_distance)
        return IntervalHour_4;

    if (distance(scale_minimum, scale_minimum.addSecs(21600)) > minimum_tick_distance)
        return IntervalHour_6;

    if (distance(scale_minimum, scale_minimum.addSecs(43200)) > minimum_tick_distance)
        return IntervalHour_12;

    if (distance(scale_minimum, scale_minimum.addDays(1)) > minimum_tick_distance)
        return IntervalDay_1;

    if (distance(scale_minimum, scale_minimum.addMonths(1)) > minimum_tick_distance)
        return IntervalMonth_1;

    if (distance(scale_minimum, scale_minimum.addMonths(3)) > minimum_tick_distance)
        return IntervalMonth_3;

    if (distance(scale_minimum, scale_minimum.addYears(1)) > minimum_tick_distance)
        return IntervalYear;

    return IntervalYear;
}

QDateTime DateTimeScaleEnginePrivate::nextDateTime(const QDateTime &datetime,
                                                   DateTimeScaleEnginePrivate::SplitInterval interval,
                                                   int tick_step) const
{
    QDateTime next_datetime = datetime;

    switch (interval) {
        case IntervalSecond_1:
            next_datetime = datetime.addSecs(1 * tick_step);
            break;
        case IntervalSecond_5:
            next_datetime = datetime.addSecs(5 * tick_step);
            break;
        case IntervalSecond_10:
            next_datetime = datetime.addSecs(10 * tick_step);
            break;
        case IntervalSecond_30:
            next_datetime = datetime.addSecs(30 * tick_step);
            break;
        case IntervalMinute_1:
            next_datetime = datetime.addSecs(60 * tick_step);
            break;
        case IntervalMinute_5:
            next_datetime = datetime.addSecs(300 * tick_step);
            break;
        case IntervalMinute_10:
            next_datetime = datetime.addSecs(600 * tick_step);
            break;
        case IntervalMinute_30:
            next_datetime = datetime.addSecs(1800 * tick_step);
            break;
        case IntervalHour_1:
            next_datetime = datetime.addSecs(3600 * tick_step);
            break;
        case IntervalHour_2:
            next_datetime = datetime.addSecs(7200 * tick_step);
            break;
        case IntervalHour_3:
            next_datetime = datetime.addSecs(10800 * tick_step);
            break;
        case IntervalHour_4:
            next_datetime = datetime.addSecs(14400 * tick_step);
            break;
        case IntervalHour_6:
            next_datetime = datetime.addSecs(21600 * tick_step);
            break;
        case IntervalHour_12:
            next_datetime = datetime.addSecs(43200 * tick_step);
            break;
        case IntervalDay_1:
            next_datetime = datetime.addDays(1 * tick_step);
            break;
        case IntervalMonth_1:
            next_datetime = datetime.addMonths(1 * tick_step);
            break;
        case IntervalMonth_3:
            next_datetime = datetime.addMonths(3 * tick_step);
            break;
        case IntervalYear:
            next_datetime = datetime.addYears(1 * tick_step);
            break;
        case IntervalNone:
        default:
            break;
    }

    return next_datetime;
}

double DateTimeScaleEnginePrivate::tickDistance(DateTimeScaleEnginePrivate::SplitInterval interval) const
{
    if (scale == 0)
        return 0.0;

    QDateTime scale_minimum = Converter::fromScale(scale->minimum());

    return scale->position(Converter::toScale(nextDateTime(scale_minimum, interval)));
}

int DateTimeScaleEnginePrivate::majorTickStep(DateTimeScaleEnginePrivate::SplitInterval interval) const
{
    int major_tick_step = 0;

    switch (interval) {
        case IntervalSecond_1:
            major_tick_step = 10;
            break;
        case IntervalSecond_5:
            major_tick_step = 12;
            break;
        case IntervalSecond_10:
            major_tick_step = 12;
            break;
        case IntervalSecond_30:
            major_tick_step = 10;
            break;
        case IntervalMinute_1:
            major_tick_step = 10;
            break;
        case IntervalMinute_5:
            major_tick_step = 12;
            break;
        case IntervalMinute_10:
            major_tick_step = 12;
            break;
        case IntervalMinute_30:
            major_tick_step = 12;
            break;
        case IntervalHour_1:
            major_tick_step = 12;
            break;
        case IntervalHour_2:
            major_tick_step = 12;
            break;
        case IntervalHour_3:
            major_tick_step = 12;
            break;
        case IntervalHour_4:
            major_tick_step = 9;
            break;
        case IntervalHour_6:
            major_tick_step = 10;
            break;
        case IntervalHour_12:
            major_tick_step = 10;
            break;
        case IntervalDay_1:
            major_tick_step = 10;
            break;
        case IntervalMonth_1:
            major_tick_step = 2;
            break;
        case IntervalMonth_3:
            major_tick_step = 12;
            break;
        case IntervalYear:
            major_tick_step = 10;
            break;
        case IntervalNone:
        default:
            break;
    }

    return major_tick_step;
}

QDateTime DateTimeScaleEnginePrivate::alignedToInterval(const QDateTime &datetime,
                                                        DateTimeScaleEnginePrivate::SplitInterval interval,
                                                        int tick_step) const
{
    if (scale == 0)
        return datetime;

    QDateTime aligned_datetime = datetime;

    if ((interval == IntervalSecond_1) ||
        (interval == IntervalSecond_5) ||
        (interval == IntervalSecond_10) ||
        (interval == IntervalSecond_30) ||
        (interval == IntervalMinute_1) ||
        (interval == IntervalMinute_5) ||
        (interval == IntervalMinute_10) ||
        (interval == IntervalMinute_30) ||
        (interval == IntervalHour_1) ||
        (interval == IntervalHour_2) ||
        (interval == IntervalHour_3) ||
        (interval == IntervalHour_4) ||
        (interval == IntervalHour_6) ||
        (interval == IntervalHour_12))
    {
        const QDateTime aligned_datetime_utc =
                QDateTime(aligned_datetime.date(), aligned_datetime.time(), Qt::UTC);

        const int utc_offset = aligned_datetime.secsTo(aligned_datetime_utc);

        const uint local_aligned_datetime_seconds = aligned_datetime.toTime_t() + utc_offset;

        const uint major_tick_seconds_step =
                aligned_datetime.secsTo(nextDateTime(aligned_datetime, interval, tick_step));

        const uint tmp = local_aligned_datetime_seconds / major_tick_seconds_step;

        if (local_aligned_datetime_seconds != tmp * major_tick_seconds_step) {
            aligned_datetime =
                    QDateTime::fromTime_t((tmp + 1) * major_tick_seconds_step - utc_offset);
        }
    }
    else if (interval == IntervalDay_1) {
        if (aligned_datetime.time() != QTime(0, 0, 0)) {
            aligned_datetime.setTime(QTime(0, 0, 0));
            aligned_datetime.setDate(aligned_datetime.addDays(1).date());
        }
    }
    else if (interval == IntervalMonth_1) {
        if ((aligned_datetime.date().day() != 1) || (aligned_datetime.time() != QTime(0, 0, 0))) {
            aligned_datetime.setTime(QTime(0, 0, 0));
            aligned_datetime.setDate(QDate(aligned_datetime.addMonths(1).date().year(),
                                           aligned_datetime.addMonths(1).date().month(),
                                           1));
        }
    }
    else if (interval == IntervalMonth_3) {
        if (((aligned_datetime.date().month() % 3) != 0) || (aligned_datetime.time() != QTime(0, 0, 0))) {
            int month = aligned_datetime.date().month();
            month = ((month % 3) == 0) ? month : ((month / 3 + 1) * 3);
            if ((aligned_datetime.date().month() != month) && (aligned_datetime.time() != QTime(0, 0, 0))) {
                aligned_datetime = aligned_datetime.addMonths(3);
            }
            else {
                aligned_datetime.setDate(QDate(aligned_datetime.date().year(),
                                               month,
                                               1));
            }
            aligned_datetime.setTime(QTime(0, 0, 0));
        }
    }
    else if (interval == IntervalYear) {
        if (aligned_datetime.secsTo(QDateTime(QDate(aligned_datetime.date().year(), 1, 1), QTime(0, 0, 0))) != 0) {
            aligned_datetime.setTime(QTime(0, 0, 0));
            aligned_datetime.setDate(QDate(aligned_datetime.date().year() + 1, 1, 1));
        }
    }

    return aligned_datetime;
}

QString DateTimeScaleEnginePrivate::majorTickLabelFormat(DateTimeScaleEnginePrivate::SplitInterval interval) const
{
    QString format = QString::null;

    switch (interval) {
        case IntervalSecond_1:
        case IntervalSecond_5:
        case IntervalSecond_10:
        case IntervalSecond_30:
            format = "hh:mm:ss";
            break;

        case IntervalMinute_1:
        case IntervalMinute_5:
        case IntervalMinute_10:
        case IntervalMinute_30:
            format = "hh:mm";
            break;

        case IntervalHour_1:
        case IntervalHour_2:
        case IntervalHour_3:
        case IntervalHour_4:
        case IntervalHour_6:
        case IntervalHour_12:
            format = "hh:mm";
            break;

        case IntervalDay_1:
            format = "d MMM";
            break;

        case IntervalMonth_1:
        case IntervalMonth_3:
            format = "MMM yyyy";
            break;

        case IntervalYear:
            format = "yyyy";
            break;

        case IntervalNone:
        default:
            break;
    }

    return format;
}

QString DateTimeScaleEnginePrivate::majorTickSubLabelFormat(DateTimeScaleEnginePrivate::SplitInterval interval) const
{
    QString format = QString::null;

    switch (interval) {
        case IntervalSecond_1:
        case IntervalSecond_5:
        case IntervalSecond_10:
        case IntervalSecond_30:
        case IntervalMinute_1:
        case IntervalMinute_5:
        case IntervalMinute_10:
        case IntervalMinute_30:
        case IntervalHour_1:
        case IntervalHour_2:
        case IntervalHour_3:
        case IntervalHour_4:
        case IntervalHour_6:
        case IntervalHour_12:
            format = "d MMM";
            break;

        case IntervalDay_1:
            format = "yyyy";
            break;

        case IntervalMonth_1:
        case IntervalMonth_3:
        case IntervalYear:
        case IntervalNone:
        default:
            break;
    }

    return format;
}

bool DateTimeScaleEnginePrivate::needsSubLabel(const QDateTime &prev_datetime, const QDateTime &datetime,
                                               DateTimeScaleEnginePrivate::SplitInterval interval) const
{
    bool needs_sublabel = false;

    switch (interval) {
        case IntervalSecond_1:
        case IntervalSecond_5:
        case IntervalSecond_10:
        case IntervalSecond_30:
        case IntervalMinute_1:
        case IntervalMinute_5:
        case IntervalMinute_10:
        case IntervalMinute_30:
        case IntervalHour_1:
        case IntervalHour_2:
        case IntervalHour_3:
        case IntervalHour_4:
        case IntervalHour_6:
        case IntervalHour_12:
            needs_sublabel = ((prev_datetime.date().day() != datetime.date().day()) || prev_datetime.isNull());
            break;

        case IntervalDay_1:
            needs_sublabel = ((prev_datetime.date().year() != datetime.date().year()) || prev_datetime.isNull());
            break;

        case IntervalMonth_1:
        case IntervalMonth_3:
        case IntervalYear:
        case IntervalNone:
        default:
            break;
    }

    return needs_sublabel;
}


DateTimeScaleEngine::DateTimeScaleEngine() :
    d_ptr(new DateTimeScaleEnginePrivate())
{
}

DateTimeScaleEngine::~DateTimeScaleEngine()
{
    delete d_ptr;
}

AbstractScale *DateTimeScaleEngine::scale() const
{
    Q_D(const DateTimeScaleEngine);
    return d->scale;
}

void DateTimeScaleEngine::setScale(AbstractScale *scale)
{
    Q_D(DateTimeScaleEngine);
    d->scale = scale;
}

QList<double> DateTimeScaleEngine::tickPositions() const
{
    Q_D(const DateTimeScaleEngine);
    return d->tick_positions;
}

QList<double> DateTimeScaleEngine::majorTickPositions() const
{
    Q_D(const DateTimeScaleEngine);
    return d->major_tick_positions;
}

QList<QString> DateTimeScaleEngine::majorTickLabels() const
{
    Q_D(const DateTimeScaleEngine);
    return d->major_tick_labels;
}

QList<QRectF> DateTimeScaleEngine::majorTickLabelRectangles() const
{
    Q_D(const DateTimeScaleEngine);
    return d->major_tick_label_rectangles;
}

void DateTimeScaleEngine::update(const QFontMetrics &font_metrics, const QRectF &scale_rect, bool revert)
{
    Q_D(DateTimeScaleEngine);

    d->tick_positions.clear();
    d->major_tick_positions.clear();

    d->major_tick_labels.clear();
    d->major_tick_label_rectangles.clear();

    if (d->scale == 0)
        return;

    const double minimum_tick_distance = 5.0;

    DateTimeScaleEnginePrivate::SplitInterval interval = d->interval(minimum_tick_distance);

    if (interval == DateTimeScaleEnginePrivate::IntervalNone)
        return;

    const int major_tick_step = d->majorTickStep(interval);

    const QDateTime tick_start_value = Converter::fromScale(d->scale->minimum());
    const QDateTime tick_end_value = Converter::fromScale(d->scale->maximum());

    const QDateTime major_tick_start_val = d->alignedToInterval(tick_start_value, interval, major_tick_step);

    const QString major_tick_format = d->majorTickLabelFormat(interval);
    const QString major_tick_subformat = d->majorTickSubLabelFormat(interval);

    const double tick_pos_offset = (d->scale->orientation() == Qt::Horizontal) ? scale_rect.x()
                                                                               : scale_rect.y();

    for (QDateTime tick_value = tick_start_value; tick_value < major_tick_start_val; /**/) {
        d->tick_positions.append(d->scale->position(Converter::toScale(tick_value)) + tick_pos_offset);
        tick_value = d->nextDateTime(tick_value, interval);
    }

    int tick_step = 0;
    for (QDateTime tick_value = major_tick_start_val; tick_value <= tick_end_value; ++ tick_step) {
        const double tick_pos = d->scale->position(Converter::toScale(tick_value)) + tick_pos_offset;
        if ((tick_step % major_tick_step) == 0)
            d->major_tick_positions.append(tick_pos);
        else
            d->tick_positions.append(tick_pos);
        tick_value = d->nextDateTime(tick_value, interval);
    }

    for (QDateTime tick_value = major_tick_start_val, prev_tick_value = major_tick_start_val;
         tick_value <= tick_end_value; /* empty */)
    {
        //	for (QDateTime tick_value = major_tick_start_val, prev_tick_value; tick_value <= tick_end_value; /* empty */) {
        QString tick_label = tick_value.toString(major_tick_format);

        if (d->needsSubLabel(prev_tick_value, tick_value, interval))
            tick_label += "\n" + tick_value.toString(major_tick_subformat);

        QRectF tick_label_rect =
                font_metrics.boundingRect(QRect(0, 0, 0, 0), Qt::AlignCenter, tick_label);

        if (d->scale->orientation() == Qt::Horizontal) {
            if (revert) {
                tick_label_rect.moveCenter(
                            QPointF(d->scale->position(Converter::toScale(tick_value)) + scale_rect.x(),
                                    scale_rect.bottom() - 10.0 - tick_label_rect.height() * 0.5));
            }
            else {
                tick_label_rect.moveCenter(
                            QPointF(d->scale->position(Converter::toScale(tick_value)) + scale_rect.x(),
                                    scale_rect.top() + 10.0 + tick_label_rect.height() * 0.5));
            }
        }
        else {
            if (revert) {
                tick_label_rect.moveCenter(
                            QPointF(scale_rect.right() - 13.0 - tick_label_rect.width() * 0.5,
                                    d->scale->position(Converter::toScale(tick_value)) + scale_rect.y()));
            }
            else {
                tick_label_rect.moveCenter(
                            QPointF(scale_rect.left() + 13.0 + tick_label_rect.width() * 0.5,
                                    d->scale->position(Converter::toScale(tick_value)) + scale_rect.y()));
            }
        }

        d->major_tick_labels.append(tick_label);
        d->major_tick_label_rectangles.append(tick_label_rect);

        prev_tick_value = tick_value;
        tick_value = d->nextDateTime(tick_value, interval, major_tick_step);
    }
}

} // namespace Graphics
