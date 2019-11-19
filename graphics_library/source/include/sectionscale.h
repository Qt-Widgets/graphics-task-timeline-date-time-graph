#ifndef GRAPHICS_SECTIONSCALE_H
#define GRAPHICS_SECTIONSCALE_H

/*!
  * \file sectionscale.h
  * \brief Объявление класса дискретной шкалы.
  *
  * \file sectionscale.cpp
  * \brief Реализация класса дискретной шкалы.
  */

#include "commonprerequisites.h"
#include "numericscale.h"

namespace Graphics {

class SectionScalePrivate;

//! Класс дискретной шкалы.
class GRAPHICS_EXPORT SectionScale : public NumericScale {
    Q_DISABLE_COPY(SectionScale)
    Q_DECLARE_PRIVATE(SectionScale)
public:
    //! Флаги выравнивания элементов внутри секций значений.
    enum SectionAlignment {
        //! В начале секции.
        SectionAlignStart,
        //! В середине секции.
        SectionAlignMiddle,
        //! В конце секции.
        SectionAlignEnd
    };
private:
    //! Указатель на реализацию.
    SectionScalePrivate * const d_ptr;
public:
    //! Конструктор.
    SectionScale();
    //! Деструктор.
    ~SectionScale();

    void setLength(double length);

    //! Количество секций.
    uint sectionsCount() const;
    //! Смена количества секций на \c count.
    void setSectionsCount(uint count);

    //! Подпись для секции \c section.
    QString sectionLabel(uint section) const;
    //! Смена подписи секции \c section на \c label.
    void setSectionLabel(uint section, const QString &label);

    //! Выравнивание элементов в секции \c section.
    SectionAlignment sectionAlignment(uint section) const;
    //! Смена выравнивания элементов внутри секции \c section на \c alignment.
    void setSectionAlignment(uint section, SectionAlignment alignment);

    //! Установка фиксированного размера \c size для секции \c section.
    void setSectionSizeFixed(uint section, double size);
    //! Установка расчитываемого размера для секции \c section.
    void setSectionSizeAdjusted(uint section);

    double position(double value) const;
    double value(double position) const;

    double position(const AbstractPlotItem *item) const;

    double distance(double value_from, double value_to) const;

    QString label(double position) const;
};

} // namespace Graphics

#endif // GRAPHICS_SECTIONSCALE_H
