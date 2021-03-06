#ifdef SUPPORT_QTMM
#include "qtmm_decoder.h"

QtMMDecoder::QtMMDecoder(QObject *parent) : QObject(parent)
{
    MediaDecoder.reset(new QMediaPlayer(this));
    connect(MediaDecoder.data(), SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
//    connect(MediaDecoder.data(), SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
}

void QtMMDecoder::setVideoOutput(MediaWidgetWrapper *renderer)
{
    MediaDecoder.data()->setVideoOutput(renderer->getVideoRenderer());
}

void QtMMDecoder::removeVideoOutput(MediaWidgetWrapper *renderer)
{
    Q_UNUSED(renderer);
}

bool QtMMDecoder::load(QString file_path)
{
    current_media_path = file_path;
    MediaDecoder.data()->setMedia(QMediaContent(QUrl::fromLocalFile(current_media_path)));
    return (MediaDecoder.data()->mediaStatus() != QMediaPlayer::NoMedia && MediaDecoder.data()->mediaStatus() != QMediaPlayer::InvalidMedia);
}

void QtMMDecoder::setVolume(QString percent)
{
    int vol = 0;
    if (percent.endsWith('%'))
        vol = percent.mid(0, percent.length()-1).toInt();
    MediaDecoder.data()->setVolume(vol);
}

void QtMMDecoder::unload()
{
    MediaDecoder.data()->setMedia(QMediaContent());
}

void QtMMDecoder::play()
{
    MediaDecoder.data()->play();
}

void QtMMDecoder::stop()
{
    MediaDecoder.data()->stop();
}

void QtMMDecoder::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status)
    {
        case QMediaPlayer::UnknownMediaStatus:
            qWarning(Develop) << "Unknown media status! Media:" << current_media_path;
            break;
        case QMediaPlayer::NoMedia:
            qWarning(Develop) << "No Media " << current_media_path;
            break;
        case QMediaPlayer::LoadedMedia:
            qInfo(Develop) << "Loaded media " << current_media_path;
            break;
        case QMediaPlayer::BufferedMedia:
            qInfo(Develop) << "Buffered media " << current_media_path;
            break;
        case QMediaPlayer::BufferingMedia:
            qInfo(Develop) << "Buffering media " << current_media_path;
            break;
        case QMediaPlayer::LoadingMedia:
            qInfo(Develop) << "Loading media " << current_media_path;
            break;
        case QMediaPlayer::StalledMedia:
            qWarning(Develop) << "Stalled media " << current_media_path;
            break;
        case QMediaPlayer::EndOfMedia:
            qInfo(Develop) << "End of media " << current_media_path;
            emit finished();
            break;
        case QMediaPlayer::InvalidMedia:
            qWarning(Develop) << "invalid Media " << current_media_path;
            break;
    }
}

void QtMMDecoder::displayErrorMessage()
{
    qWarning(Develop) << MediaDecoder->errorString();
}


#endif
