#ifndef GRAPHICS_DATETIMESCALEENGINE_H
#define GRAPHICS_DATETIMESCALEENGINE_H

/*!
  * \file datetimescaleengine.h
  * \brief Объявление класса движка для рисования временной шкалы.
  *
  * \file datetimescaleengine.cpp
  * \brief Реализация класса движка рисования для временной шкалы.
  */

#include "commonprerequisites.h"
#include "abstractscaleengine.h"

namespace Graphics {

class DateTimeScaleEnginePrivate;

//! Движок рисования временной шкалы.
class GRAPHICS_EXPORT DateTimeScaleEngine : public AbstractScaleEngine {
    Q_DECLARE_PRIVATE(DateTimeScaleEngine)
    Q_DISABLE_COPY(DateTimeScaleEngine)

    //! Указатель на реализацию.
    DateTimeScaleEnginePrivate * const d_ptr;
public:
    //! Конструктор.
    DateTimeScaleEngine();
    //! Деструктор.
    ~DateTimeScaleEngine();

    AbstractScale *scale() const;
    void setScale(AbstractScale *scale);

    QList<double> tickPositions() const;
    QList<double> majorTickPositions() const;

    QList<QString> majorTickLabels() const;
    QList<QRectF> majorTickLabelRectangles() const;

    void update(const QFontMetrics &font_metrics, const QRectF &scale_rect, bool revert);
};

} // namespace Graphics

#endif // GRAPHICS_DATETIMESCALEENGINE_H
