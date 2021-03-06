#ifndef QTAV_WIDGET_H
#define QTAV_WIDGET_H

#ifdef SUPPORT_QTAV
#include <QtAV>
#include <QtAVWidgets>

class QtAVWidget : public QWidget
{
    Q_OBJECT
public:
    QtAVWidget(QWidget *parent = Q_NULLPTR);
    QWidget              *getVideoWidget();
    QtAV::VideoRenderer  *getVideoRenderer();
    void                  setAspectRatioFill();
    void                  setAspectRatioMeet();
    void                  setAspectRatioMeetBest();
signals:
protected:
    QScopedPointer<QtAV::VideoOutput> VideoWidget;  // a deleteLater leads to a crash on playlistchange!
};
#endif
#endif // QTAV_WIDGET_H
