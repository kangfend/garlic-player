/*************************************************************************************
    garlic-player: SMIL Player for Digital Signage
    Copyright (C) 2016 Nikolaos Saghiadinos <ns@smil-control.com>
    This file is part of the garlic-player source code

    This program is free software: you can redistribute it and/or  modify
    it under the terms of the GNU Affero General Public License, version 3,
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*************************************************************************************/

#ifndef MAGE_H
#define IMAGE_H

#include "media.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

struct showImg
{
    QString media_type;
    QString region;
    QString fit;
    QPixmap pixmap;
    QGraphicsPixmapItem *image_item;
};

class TImage : public TMedia
{
    Q_OBJECT
public:
    TImage(TContainer *parent = 0);
    ~TImage();
    showImg  getMediaForShow();
    QString  getFit();
    bool     load(QString index_path);
    void     pause();
    void     stop();
    void     play();
public slots:
    void     setDurationTimerBeforePlay();
protected:
    showImg show_img;
    void    setAttributes();
};

#endif // IMAGE_H
