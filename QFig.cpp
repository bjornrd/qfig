/****************************************************************************
 * Written by: bjornrd
 * 27/5/2019
 * me_brd@hotmail.com
 ****************************************************************************/
#include "QFig.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QApplication>

namespace qf{

QGraphicsView* setUpNewGraphicsView(QPixmap pixmap);



QFig::QFig(QWidget* parent) :
    QMainWindow(parent),
    _figureView(nullptr),
    _resizeOpt(FitOnResize),
    _aspectRatioMode(KeepAspectRatio)
{
    // Make the figure windows close when the main app windows close
    this->setAttribute(Qt::WA_QuitOnClose, false);
}

QFig::~QFig()
{
    if(_figureView != nullptr)
        delete _figureView;
}

void QFig::close()
{
    QFig::~QFig();
}

QGraphicsView* QFig::view()
{
    return _figureView;
}

void QFig::setView(QGraphicsView *newView)
{
    _figureView = newView;
    this->setCentralWidget(_figureView);
}

FigureResizeOption QFig::resizeOption()
{
    return _resizeOpt;
}

void QFig::setResizeOption(FigureResizeOption opt)
{
    _resizeOpt = opt;
}

void QFig::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if(_resizeOpt == FitOnResize)
        _figureView->fitInView(_figureView->items().at(0)->boundingRect(), static_cast<Qt::AspectRatioMode>(_aspectRatioMode));
}

AspectRatioMode QFig::aspectRatioMode() const
{
    return _aspectRatioMode;
}

void QFig::setAspectRatioMode(const AspectRatioMode &aspectRatioMode)
{
    _aspectRatioMode = aspectRatioMode;
}

QFig* imshow(QPixmap pixmap, QString title, ImageOptions opt, QWidget* parent)
{
    auto view = setUpNewGraphicsView(pixmap);

    QFig* figure = new QFig(parent);

    figure->setResizeOption(opt.figureResizeOption());
    figure->setWindowTitle(title);
    figure->setView(view);
    figure->show();

    return figure;
}

QFig* imshow(QPixmap pixmap, ImageOptions opt, QWidget* parent)
{
    return imshow(pixmap, "", opt, parent);
}

QFig* imshow(QImage image, ImageOptions opt, QWidget* parent)
{
    return imshow(QPixmap::fromImage(image), "", opt, parent);
}

QFig* imshow(QImage image, QString title, ImageOptions opt, QWidget* parent)
{
    return imshow(QPixmap::fromImage(image), title, opt, parent);
}

QGraphicsView* setUpNewGraphicsView(QPixmap pixmap)
{
    QGraphicsView*       view   = new QGraphicsView();
    QGraphicsScene*      scene  = new QGraphicsScene(view);
    QGraphicsPixmapItem* item   = new QGraphicsPixmapItem();

    view->setScene(scene);
    scene->addItem(item);
    item->setPixmap(pixmap);
    scene->setSceneRect(item->boundingRect());

    view->fitInView(item, Qt::KeepAspectRatio);

    return view;
}

} // namespace qf
