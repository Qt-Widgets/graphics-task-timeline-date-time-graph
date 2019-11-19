#include <cmath>
#include <QMap>

#include "include/sectionscale.h"
#include "include/abstractplotitem.h"


namespace Graphics {

//! Реализация класса дискретной шкалы.
class SectionScalePrivate {
    Q_DECLARE_PUBLIC(SectionScale)

    //! Укзатель на объявление.
    SectionScale *q_ptr;

    //! Количество секций.
    uint sections_count;
    //! Подписи секций.
    QMap<uint, QString> section_label;
    //! Выравнивание элементов внутри секций.
    QMap<uint, SectionScale::SectionAlignment> section_alignment;
    //! Фиксированные размеры секций.
    QMap<uint, double> section_fixed_size;
    //! Кэш размеров секций.
    QMap<uint, double> section_size_cache;
    //! Кэш положения секций.
    QMap<uint, double> section_position_cache;

    //! Конструктор с указателем на объявление класса \c q.
    SectionScalePrivate(SectionScale *q) : q_ptr(q), sections_count(0) {}
    //! Деструктор.
    ~SectionScalePrivate() {}

    //! Расчитываемая ширина секции.
    double sectionWidth() const
    {
        Q_Q(const SectionScale);
        return (sections_count == 0) ? 0.0 : (q->length() / double(sections_count));
    }

    //! Пересчет кэшей размеров и положения секций.
    void updateSectionsGeometry()
    {
        Q_Q(SectionScale);

        section_size_cache.clear();
        section_position_cache.clear();

        double fixed_section_size = 0;
        foreach (double fixed_size, section_fixed_size.values())
            fixed_section_size += fixed_size;

        double rest_size = qMax(0.0, q->length() - fixed_section_size);

        uint adjusted_section_count = qMax(uint(0), sections_count - section_fixed_size.size());

        double adjusted_section_size = (adjusted_section_count != 0) ? rest_size / double(adjusted_section_count)
                                                                     : 0.0;

        double position_offset = 0.0;

        for (uint i = 0; i < sections_count; ++ i) {
            double section_size = section_fixed_size.value(i, adjusted_section_size);

            section_size_cache.insert(i, section_size);
            section_position_cache.insert(i, position_offset);

            position_offset += section_size;
        }
    }
};



SectionScale::SectionScale() :
    NumericScale(),
    d_ptr(new SectionScalePrivate(this))
{
}

SectionScale::~SectionScale()
{
    delete d_ptr;
}

void SectionScale::setLength(double length)
{
    Q_D(SectionScale);
    NumericScale::setLength(length);
    d->updateSectionsGeometry();
}

uint SectionScale::sectionsCount() const
{
    Q_D(const SectionScale);
    return d->sections_count;
}

void SectionScale::setSectionsCount(uint count)
{
    Q_D(SectionScale);
    d->sections_count = count;
    setRange(0.0, double(d->sections_count));
    d->updateSectionsGeometry();
}

QString SectionScale::sectionLabel(uint section) const
{
    Q_D(const SectionScale);
    return d->section_label.value(section, QString::null);
}

void SectionScale::setSectionLabel(uint section, const QString &label)
{
    Q_D(SectionScale);
    d->section_label.insert(section, label);
}

SectionScale::SectionAlignment SectionScale::sectionAlignment(uint section) const
{
    Q_D(const SectionScale);
    return d->section_alignment.value(section, SectionAlignMiddle);
}

void SectionScale::setSectionAlignment(uint section, SectionScale::SectionAlignment alignment)
{
    Q_D(SectionScale);
    d->section_alignment.insert(section, alignment);
}

void SectionScale::setSectionSizeFixed(uint section, double size)
{
    Q_D(SectionScale);
    d->section_fixed_size.insert(section, size);
    d->updateSectionsGeometry();
}

void SectionScale::setSectionSizeAdjusted(uint section)
{
    Q_D(SectionScale);
    if (d->section_fixed_size.contains(section)) {
        d->section_fixed_size.remove(section);
        d->updateSectionsGeometry();
    }
}

double SectionScale::position(double value) const
{
    Q_D(const SectionScale);

    return d->section_position_cache.value(uint(floor(value)));
}

double SectionScale::value(double position) const
{
    Q_D(const SectionScale);
    const double section_width = d->sectionWidth();
    return (section_width == 0) ? 0.0 : floor(position / section_width);
}

double SectionScale::position(const AbstractPlotItem *item) const
{
    const double section = (orientation() == Qt::Horizontal) ? item->beginCoordinateX()
                                                             : item->beginCoordinateY();

    const double alignment_offset = (orientation() == Qt::Horizontal) ? item->width() * 0.5
                                                                      : item->height() * 0.5;

    const double section_width = (orientation() == Qt::Horizontal)
                                 ? distance(item->beginCoordinateX(), item->endCoordinateX())
                                 : distance(item->beginCoordinateY(), item->endCoordinateY());

    double item_position = position(section);

    switch (sectionAlignment(section)) {
        case SectionAlignStart:
            item_position = item_position + alignment_offset;
            break;
        case SectionAlignMiddle:
            item_position = item_position + section_width * 0.5;
            break;
        case SectionAlignEnd:
            item_position = item_position + section_width - alignment_offset;
            break;
    }

    return item_position;
}

double SectionScale::distance(double value_from, double value_to) const
{
    Q_D(const SectionScale);

    double dist = 0.0;

    for (uint section = uint(floor(value_from)); section <= value_to; ++ section)
        dist += d->section_size_cache.value(section);

    return dist;
}

QString SectionScale::label(double position) const
{
    return sectionLabel(value(position));
}

} // namespace Graphics
