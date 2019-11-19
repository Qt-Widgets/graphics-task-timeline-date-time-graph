#include <QDateTime>

#include "include/converter.h"


namespace Graphics {

double Converter::toScale(const QDateTime &val)
{
    return double(val.toTime_t());
}

QDateTime Converter::fromScale(double val)
{
    return QDateTime::fromTime_t(val);
}

} // namespace Graphics
