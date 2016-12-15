#include "tpalette.h"

TPalette::TPalette(int target, QColor* color)
{
    switch (target)
    {
    case StaticData::TEXT_COLOR:{
        this->setColor(QPalette::Background,*CommonColor::LIGHT_BLACK_64);
        this->setColor(QPalette::WindowText,*color);
        break;
    }
    case StaticData::BACKGOUND_COLOR:{
        this->setColor(this->Background,*color);
        break;
    }

    }
}
