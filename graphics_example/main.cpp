#include <QDateTime>
#include <QApplication>

#include <numericscale.h>
#include <sectionscale.h>
#include <datetimescale.h>
#include <standardplotlayout.h>
#include <standardplotscene.h>
#include <infiniteplotscene.h>
#include <converter.h>
#include <datetimescaleplotitem.h>
#include <standardplotview.h>

#include "simpleitem.h"

using namespace Graphics;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StandardPlotView *view = new StandardPlotView();
    view->setAttribute(Qt::WA_DeleteOnClose);
    view->setWindowTitle("Graphics Plot Test");


    DateTimeScale *x_scale = new DateTimeScale();
    x_scale->setOrientation(Qt::Horizontal);
    x_scale->setLength(4000);
    x_scale->setRange(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(0, 0, 0))),
                      Converter::toScale(QDateTime(QDate(2014, 10, 2), QTime(0, 0, 0))));

    SectionScale *y_scale = new SectionScale();
    y_scale->setOrientation(Qt::Vertical);
    y_scale->setLength(500);
    y_scale->setSectionsCount(5);

    StandardPlotLayout *layout = new StandardPlotLayout();

    InfinitePlotScene *scene = new InfinitePlotScene(view);
    scene->setXScale(x_scale);
    scene->setYScale(y_scale);
    scene->setLayout(layout);
    scene->setZoomExtent(3600 * 2);
    scene->setMinimumZoomStep(-100);
    scene->setMaximumZoomStep(100);

    DateTimeScalePlotItem *scale_item = new DateTimeScalePlotItem(x_scale);
    scale_item->setBeginCoordinates(x_scale->minimum(), 0);
    scale_item->setEndCoordinates(x_scale->maximum(), 0);
    scale_item->setWidthCalculated(true);
    scale_item->setHeightCalculated(true);

    scene->addPlotItem(scale_item);

    SimpleItem *plot_item_1 = new SimpleItem();
    plot_item_1->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(1, 0, 0))), 1);
    plot_item_1->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(5, 0, 0))), 1);
    plot_item_1->setWidthCalculated(true);
    plot_item_1->setHeightCalculated(true);

    scene->addPlotItem(plot_item_1);

    SimpleItem *plot_item_2 = new SimpleItem();
    plot_item_2->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(3, 43, 20))), 1);
    plot_item_2->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(13, 13, 13))), 1);
    plot_item_2->setWidthCalculated(true);
    plot_item_2->setHeightCalculated(true);

    scene->addPlotItem(plot_item_2);

    SimpleItem *plot_item_3 = new SimpleItem();
    plot_item_3->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(1, 10, 0))), 2);
    plot_item_3->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(9, 0, 0))), 2);
    plot_item_3->setWidthCalculated(true);
    plot_item_3->setHeightCalculated(false);
    plot_item_3->setHeight(20);

    scene->addPlotItem(plot_item_3);

    SimpleItem *plot_item_4 = new SimpleItem();
    plot_item_4->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(15, 0, 0))), 2);
    plot_item_4->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(19, 0, 0))), 2);
    plot_item_4->setWidthCalculated(true);
    plot_item_4->setHeightCalculated(true);

    scene->addPlotItem(plot_item_4);

    SimpleItem *plot_item_5 = new SimpleItem();
    plot_item_5->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(1, 10, 0))), 3);
    plot_item_5->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 10, 1), QTime(2, 0, 0))), 3);
    plot_item_5->setWidthCalculated(true);
    plot_item_5->setHeightCalculated(false);
    plot_item_5->setHeight(20);

    scene->addPlotItem(plot_item_5);

    SimpleItem *plot_item_6 = new SimpleItem();
    plot_item_6->setBeginCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(1, 10, 0))), 4);
    plot_item_6->setEndCoordinates(Converter::toScale(QDateTime(QDate(2014, 9, 30), QTime(9, 0, 0))), 4);
    plot_item_6->setWidthCalculated(true);
    plot_item_6->setHeightCalculated(false);
    plot_item_6->setHeight(20);

    scene->addPlotItem(plot_item_6);

    scene->refresh();

    view->setPlotScene(scene);
    view->setZoomEnabled(true);

    view->resize(1300, 600);
    view->show();
    view->scrollPlot(20);

    return app.exec();
}
