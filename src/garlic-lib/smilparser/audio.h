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

#ifndef TAUDIO_H
#define TAUDIO_H

#include "media.h"

class TAudio : public TMedia
{
    Q_OBJECT
public:
    explicit TAudio(TContainer *pc, QObject *parent = Q_NULLPTR);
    ~TAudio();
    QString                 getSoundLevel(){return soundLevel;}
    void                    pause();
    void                    stop();
    void                    play();
protected:
    QString                 soundLevel = "100%";
    void                    setAttributes();
    bool                    loadMedia();
protected slots:
    void                    setDurationTimerBeforePlay();
};

#endif // TAUDIO_H
