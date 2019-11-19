#ifndef GRAPHICS_COMMON_H
#define GRAPHICS_COMMON_H

/*!
  * \file commonprerequisites.h
  * \brief Глобальные объявления для библиотеки graphics.
  */

//! Пространство имен с классами библиотеки graphics.
namespace Graphics {

class AbstractScale;
class NumericScale;
class DateTimeScale;
class SectionScale;

class AbstractScaleEngine;
class DateTimeScaleEngine;

class AbstractPlotItem;
class StandardPlotItem;
class InteractivePlotItem;

class DateTimeScalePlotItem;

class AbstractPlotLayout;
class StandardPlotLayout;

class AbstractPlotScene;
class StandardPlotScene;

class AbstractPlotView;
class StandardPlotView;

} // namespace Graphics

#if _WIN32
#	if defined( __MINGW32__ )
#      define GRAPHICS_EXPORT
#   else
#      ifdef GRAPHICS_LIB
#         define GRAPHICS_EXPORT __declspec (dllexport)
#      else
#         define GRAPHICS_EXPORT __declspec (dllimport)
#      endif
#   endif
#else
#   define GRAPHICS_EXPORT
#endif

/*!
  * \mainpage Библиотека Graphics
  *
  * \section Назначение
  * Библиотека graphics предоставлет набор инструментов для построения и отображения
  * двумерных графиков в приложениях.
  *
  * \section Компоненты
  * Библиотека graphics предоставляет следующие компоненты:
  * <ul>
  * <li>Graphics::AbstractPlotItem - класс для создания элементов графика</li>
  * <li>Graphics::AbstractScale - класс для создания шкал</li>
  * <li>Graphics::AbstractPlotLayout - класс для описания логики позиционирования элементов на графике</li>
  * <li>Graphics::AbstractPlotScene - класс сцены, служащей моделью графика</li>
  * <li>Graphics::AbstractPlotView - класс виджета для отображения графика</li>
  * </ul>
  */

#endif // GRAPHICS_COMMON_H
