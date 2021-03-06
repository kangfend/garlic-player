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

#include "container.h"

TContainer::TContainer(QObject *parent) : TBaseTiming(parent)
{
}

QString TContainer::getIdOfActiveElement()
{
    return parseID(active_element);
}

TBaseTiming *TContainer::getChildElementFromList()
{
    TBaseTiming *ret = NULL;
    if (childs_iterator != activatable_childs.end())
    {
        ret = *childs_iterator;
        childs_iterator++;
    }
    else
    {
        childs_iterator = activatable_childs.begin();
        ret             = *childs_iterator;
    }
    return ret;
}

void TContainer::setPlayedElement(TBaseTiming *element)
{
    played_element = element;
    return;
}

TBaseTiming *TContainer::getPlayedElement()
{
    return played_element;
}


void TContainer::childStarted(TBaseTiming *element)
{
    activatable_childs.insert(element);
    childs_iterator = activatable_childs.begin();
}

void TContainer::childEnded(TBaseTiming *element)
{
    if (activatable_childs.find(element) != activatable_childs.end())
        activatable_childs.remove(element);
}

void TContainer::setChildActive(bool active)
{
    is_child_active = active;
}

bool TContainer::hasPlayingChilds()
{
    if (activatable_childs.size() > 0)
        return true;
    return false;
}

void TContainer::setBaseContainerAttributes()
{
    if (!root_element.hasAttribute("begin") && parent_container != NULL && parent_container->objectName() == "TExcl")
        begin.parse("indefinite");
}

QString TContainer::reactByTag()
{
    QString tag_name = active_element.tagName();
    QString type     = "";
    if(tag_name == "img" || tag_name == "video" || tag_name == "audio" || tag_name == "text" || tag_name == "prefetch" ||
            tag_name == "seq"|| tag_name == "par" || tag_name == "excl")
    {
        type = tag_name;
    }
    else if(tag_name == "ref" && active_element.hasAttribute("type"))
    {
        if(active_element.attribute("type").contains("image"))
           type = "img";
        else if (active_element.attribute("type").contains("video"))
           type = "video";
        else if (active_element.attribute("type").contains("audio"))
           type = "audio";
        else if (active_element.attribute("type").contains("text"))
           type = "text";
        else if (active_element.attribute("type").contains("application/widget"))
           type = "text";
    }
    if (type != "")
        emit foundElement(this, type, active_element);
    return type;
}

void TContainer::emitfinished() // called from finishedActiveDuration() TBase
{
    qDebug(Develop) << getID() << "finished Playlist";
    emit finishedContainer(parent_container, this);
}

