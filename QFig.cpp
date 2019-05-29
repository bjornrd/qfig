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
#include <QWheelEvent>

namespace qf{

QFig::QFig(QWidget* parent) :
    QMainWindow(parent),
    _view(new QGraphicsView()),
    _scene(new QGraphicsScene(_view)),
    _imItem(new QGraphicsPixmapItem()),
    _resizeOpt(FitOnResize),
    _aspectRatioMode(KeepAspectRatio),
    _currentGain(1.0),
    _gainIncrement(0.01)
{
    // Make the figure windows close when the main app windows close
    this->setAttribute(Qt::WA_QuitOnClose, false);    

    _view->setScene(_scene);
    _scene->addItem(_imItem);
    _view->viewport()->installEventFilter(this);
    _view->setDragMode(QGraphicsView::ScrollHandDrag);

    this->setCentralWidget(_view);
}

QFig::~QFig()
{
    if(_view != nullptr)
        delete _view;
}

void QFig::close()
{
    QFig::~QFig();
}

QGraphicsView* QFig::view()
{
    return _view;
}

void QFig::setView(QGraphicsView *newView)
{
    _view = newView;
    this->setCentralWidget(_view);
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
        _view->fitInView(_view->items().at(0)->boundingRect(), static_cast<Qt::AspectRatioMode>(_aspectRatioMode));
}

bool QFig::eventFilter(QObject *watched, QEvent *event)
{
    // Comparison image zoom
    if(watched  == _view->viewport())
    {
        if(event->type() == QEvent::Wheel)
        {
            QWheelEvent* ev = static_cast<QWheelEvent*>(event);

            double scaleFactor = 1.025;
            _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

            if(ev->delta() > 0) {
                // Zoom in
                _view->scale(scaleFactor, scaleFactor);

            } else {
                // Zooming out
                 _view->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }

            return true;
        }

        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            _view->scene()->setSceneRect(_view->scene()->sceneRect());
            _view->fitInView(_view->items().at(0)->boundingRect(), Qt::KeepAspectRatio);

            return true;

        } else {
            return QMainWindow::eventFilter(watched, event);
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

AspectRatioMode QFig::aspectRatioMode() const
{
    return _aspectRatioMode;
}

void QFig::setAspectRatioMode(const AspectRatioMode &aspectRatioMode)
{
    _aspectRatioMode = aspectRatioMode;
}

void QFig::setImage(QPixmap pixmap)
{
    _imItem->setPixmap(pixmap);
    _scene->setSceneRect(_imItem->boundingRect());
    _view->fitInView(_imItem, static_cast<Qt::AspectRatioMode>(_aspectRatioMode));
}

void QFig::setImage(QImage image)
{
    _imItem->setPixmap(QPixmap::fromImage(image));
    _scene->setSceneRect(_imItem->boundingRect());
    _view->fitInView(_imItem, static_cast<Qt::AspectRatioMode>(_aspectRatioMode));
}

QFig* imshow(QPixmap pixmap, QString title, ImageOptions opt, QWidget* parent)
{
    QFig* figure = new QFig(parent);

    figure->setResizeOption(opt.figureResizeOption);
    figure->setWindowTitle(title);
    figure->setImage(pixmap);
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

} // namespace qf
