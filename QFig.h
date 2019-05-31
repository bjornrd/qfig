/****************************************************************************
 * Written by: bjornrd
 * 27/5/2019
 * me_brd@hotmail.com
 ****************************************************************************/
#ifndef QFIG_H
#define QFIG_H

#include <QMainWindow>
#include <QGraphicsView>

#if defined(QTFIG_LIBRARY)
#  define QTFIGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTFIGSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace qf{

enum QTFIGSHARED_EXPORT FigureResizeOption{
    FitOnResize,
    NoFitOnResize
};

enum QTFIGSHARED_EXPORT AspectRatioMode {
    KeepAspectRatio   = Qt::AspectRatioMode::KeepAspectRatio,
    IgnoreAspectRatio = Qt::AspectRatioMode::IgnoreAspectRatio
};

struct QTFIGSHARED_EXPORT ImageOptions {
        FigureResizeOption  figureResizeOption  = FitOnResize;
        AspectRatioMode     aspectRatioMode     = KeepAspectRatio;
};

class QTFIGSHARED_EXPORT QFig : public QMainWindow
{
        Q_OBJECT
    public:
         QFig(QWidget* parent = nullptr);
        ~QFig() override;

         void close();

         FigureResizeOption resizeOption();
         void setResizeOption(qf::FigureResizeOption opt);

         AspectRatioMode aspectRatioMode() const;
         void setAspectRatioMode(const AspectRatioMode &aspectRatioMode);

         void setImage(QPixmap pixmap);
         QPixmap pixmap();
         void setImage(QImage image);
         QImage image();

    protected:
         void resizeEvent(QResizeEvent* event) override;
         bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        QGraphicsView*       _view;
        QGraphicsScene*      _scene;
        QGraphicsPixmapItem* _imItem;
        FigureResizeOption   _resizeOpt;
        AspectRatioMode      _aspectRatioMode;
};

const static ImageOptions defaultImageOptions = ImageOptions();

QTFIGSHARED_EXPORT QFig* imshow(QPixmap pixmap,                 ImageOptions opt = ImageOptions(), QWidget* parent = nullptr);
QTFIGSHARED_EXPORT QFig* imshow(QPixmap pixmap, QString title,  ImageOptions opt = ImageOptions(), QWidget* parent = nullptr);
QTFIGSHARED_EXPORT QFig* imshow(QImage image,                   ImageOptions opt = ImageOptions(), QWidget* parent = nullptr);
QTFIGSHARED_EXPORT QFig* imshow(QImage image,   QString title,  ImageOptions opt = ImageOptions(), QWidget* parent = nullptr);


}
#endif // QFIG_H
