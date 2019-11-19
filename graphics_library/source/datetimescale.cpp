#include <QDateTime>

#include "include/datetimescale.h"
#include "include/converter.h"


namespace Graphics {

//! Релизация класса временной шкалы.
class DateTimeScalePrivate {
    friend class DateTimeScale;

    //! Формат подписей.
    QString format;

    //! Конструктор.
    DateTimeScalePrivate() : format("d MM yyyy hh:mm:ss") {}
    //! Деструктор.
    ~DateTimeScalePrivate() {}
};


DateTimeScale::DateTimeScale() :
    NumericScale(),
    d_ptr(new DateTimeScalePrivate())
{
}

DateTimeScale::~DateTimeScale()
{
    delete d_ptr;
}

QString DateTimeScale::format() const
{
    Q_D(const DateTimeScale);
    return d->format;
}

void DateTimeScale::setFormat(const QString &format)
{
    Q_D(DateTimeScale);
    d->format = format;
}

QString DateTimeScale::label(double position) const
{
    Q_D(const DateTimeScale);
    return Converter::fromScale(value(position)).toString(d->format);
}

} // namespace Graphics
