#include "base_media.h"

BaseMedia::BaseMedia(QQmlComponent *mc, QString r_id, QObject *parent) : QObject(parent)
{
    Q_UNUSED(mc);
    setRegionId(r_id);
}

QString BaseMedia::getRegionId() const
{
    return region_id;
}

void BaseMedia::setRegionId(const QString &value)
{
    region_id = value;
}

bool BaseMedia::load(QQuickItem *item)
{
    QString source = MyMedia->getLoadablePath();
    bool ret = false;
    if (isFileExists(source))
    {
        ret = true;
        item->setProperty("source", "file:"+source);
    }
    else
        qInfo(MediaPlayer) << "MEDIA_NOT_AVAILABLE" << "recourceURI" << MyMedia->getSrc();

    return ret;
}

QQuickItem *BaseMedia::createMediaItem(QQmlComponent *mc, QString str)
{
    mc->setData(str.toUtf8(), QUrl());
    if (mc->isError())
    {
        qCritical(MediaControl) << mc->errorString();
        return Q_NULLPTR;
    }

    return qobject_cast<QQuickItem *>(mc->create());
}


bool BaseMedia::isFileExists(QString path)
{
    return QFileInfo::exists(path);
}
