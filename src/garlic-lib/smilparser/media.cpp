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

#include "media.h"

TMedia::TMedia(QObject *parent) : TBaseTiming(parent)
{
}

bool TMedia::parse(QDomElement element)
{
    root_element   = element;
    setAttributes();     // special for every media type
    setBaseParameters(); // in this class
    return true;
}

QString TMedia::parseSrc(QDomElement element)
{
    QString ret = "";
    if (element.hasAttribute("src"))
        ret = element.attribute("src");
    return ret;
}

bool TMedia::isDownloaded()
{
    // FIXME MediaModel::_no_exist as static member constant do not work =>look at https://stackoverflow.com/questions/5391973/undefined-reference-to-static-const-int
    return (MyMediaManager->checkCacheStatus(src) == MEDIA_AVAILABLE || MyMediaManager->checkCacheStatus(src) == MEDIA_UNCACHABLE);
}

QString TMedia::getLoadablePath()
{
    return MyMediaManager->requestLoadablePath(src);
}


void TMedia::registerFile(MediaManager *mm)
{
    MyMediaManager = mm;
    MyMediaManager->registerFile(src);
    qDebug(Develop) << src << " registered media";
}

void TMedia::setBaseMediaAttributes()
{
    region = title = src = exec = "";
    if (!root_element.hasAttribute("begin") && parent_container->objectName() == "TExcl")
        begin.parse("indefinite");
    if (root_element.hasAttribute("region"))
        region = root_element.attribute("region");
    if (root_element.hasAttribute("fit"))
        fit = root_element.attribute("fit");
    if (root_element.hasAttribute("type"))
        type = root_element.attribute("type");

    src = parseSrc(root_element);
    if (root_element.hasAttribute("exec"))
        exec = root_element.attribute("exec");
    setTimingAttributes();
}

void TMedia::emitfinished() // called from finishedActiveDuration() in TBaseTiming
{
   emit finishedMedia(parent_container, this);
}

void TMedia::setBaseParameters()
{
    cache_control = filename = log_content_id = "";
    if (root_element.hasChildNodes())
    {
        QDomNodeList childs = root_element.childNodes();
        QDomElement param;
        for (int i = 0; i < childs.length(); i++)
        {
            param = childs.item(i).toElement();
            if (param.tagName() == "param" && param.hasAttribute("name") && param.hasAttribute("value"))
            {
                if (param.attribute("name") == "cacheControl")
                    cache_control = param.attribute("value");
                else if (param.attribute("name") == "filename")
                    filename = param.attribute("value");
                else if (param.attribute("name") == "logContentId")
                    log_content_id = param.attribute("value");
            }
        }

    }
}
