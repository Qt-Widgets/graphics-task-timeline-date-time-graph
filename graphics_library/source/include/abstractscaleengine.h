#ifndef GRAPHICS_ABSTRACTSCALE_ENGINE_H
#define GRAPHICS_ABSTRACTSCALE_ENGINE_H

/*!
  * \file abstractscaleengine.h
  * \brief Объявление базового класса для движка рисования шкал.
  */

#include <Qt>
#include <QList>
#include "commonprerequisites.h"
#include "abstractscale.h"

class QString;
class QRectF;
class QFontMetrics;
class QPointF;

namespace Graphics {

//! Базовый класс для движка рисования шкалы.
class GRAPHICS_EXPORT AbstractScaleEngine {
protected:
    //! Конструктор.
    AbstractScaleEngine() {}
public:
    //! Деструткор.
    virtual ~AbstractScaleEngine() {}

    //! Используемая шкала.
    virtual AbstractScale *scale() const = 0;
    //! Смена используемой шкалы на \c scale.
    virtual void setScale(AbstractScale *scale) = 0;

    //! Положение засечек шкалы.
    virtual QList<double> tickPositions() const = 0;
    //! Положение крупных засечек шкалы.
    virtual QList<double> majorTickPositions() const = 0;

    //! Подписи к засечкам шкалы.
    virtual QList<QString> majorTickLabels() const = 0;
    //! Подписи к крупным засечкам шкалы.
    virtual QList<QRectF> majorTickLabelRectangles() const = 0;

    /*!
     * \brief Расчет положений и подписей засечек на основе информации об используемом
     * шрифте \c font_metrics, прямоугольнике шкалы \c scale_rect и
     * флага положения подписей \c revert.
     */
    virtual void update(const QFontMetrics &font_metrics, const QRectF &scale_rect, bool revert) = 0;
};

} // namespace Graphics

#endif // GRAPHICS_ABSTRACTSCALE_ENGINE_H
