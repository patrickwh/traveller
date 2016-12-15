#include "staticdata.h"

const QString StaticData::EDIT_ICON_PATH = "../icons/edit.png";
const QString StaticData::DELETE_ICON_PATH = "../icons/delete.png";
const QString StaticData::NULL_RESULT = "No Result Avialable";
const QString StaticData::DATE_STORATION_FORMAT = "yyyyMMdd";
const QString StaticData::DATE_DISPLAY_FORMAT = "dd MMM yyyy";
const QString StaticData::LIGHT_BLUE = "66b2ff";
const QString StaticData::BLACK = "202020";
const QString StaticData::LIGHT_ORANGE = "ffb266";
const QString StaticData::LIGHT_PURPLE = "b266ff";
const QString StaticData::LIGHT_RED = "ff6666";
const QString StaticData::GOLD = "ffd700";
const QString StaticData::WHITE = "ffffff";
const QString StaticData::DARK_CYAN = "00cccc";
const QString StaticData::LIGHT_FORESTGREEN = "00994c";
const QString StaticData::LIGHT_GRAY = "c0c0c0";
const QString StaticData::LIGHT_MAGENTA = "ff66ff";
const QString StaticData::LINGHT_PINK = "ff99cc";
const QString StaticData::DEEP_SKY_BLUE = "00bfff";
const double StaticData::MAIN_WINDOW_HEIGHT_RATIO = 0.7;
const double StaticData::MAIN_WINDOW_WIDTH_RATIO = 0.7;
const double StaticData::ADD_TRIP_WIDONW_HEIGHT_RATIO = 0.5;
const double StaticData::ADD_TRIP_WIDONW_WIDTH_RATIO = 0.5;
const double StaticData::ADD_EVENT_WIDONW_HEIGHT_RATIO = 0.3;
const double StaticData::ADD_EVENT_WIDONW_WIDTH_RATIO = 0.5;
QString StaticData::COLOR_SET[] = {"light_blue","light_orange","light_purple","gold",\
                                  "dark_cyan","light_forestgreen","light_gray","light_magenta",\
                                  "light_pink","light_red","deep_sky_blue","black"};

StaticData::StaticData()
{

}

QString StaticData::getColorByName(QString name){
    if(name=="black")
        return StaticData::BLACK;
    else if(name=="light_blue")
        return StaticData::LIGHT_BLUE;
    else if(name=="light_orange")
        return StaticData::StaticData::LIGHT_ORANGE;
    else if(name=="light_purple")
        return StaticData::StaticData::LIGHT_PURPLE;
    else if(name=="gold")
        return StaticData::StaticData::GOLD;
    else if(name=="dark_cyan")
        return StaticData::StaticData::DARK_CYAN;
    else if(name=="light_forestgreen")
        return StaticData::StaticData::LIGHT_FORESTGREEN;
    else if(name=="light_gray")
        return StaticData::StaticData::LIGHT_GRAY;
    else if(name=="light_magenta")
        return StaticData::StaticData::LIGHT_MAGENTA;
    else if(name=="light_pink")
        return StaticData::StaticData::LINGHT_PINK;
    else if(name=="light_red")
        return StaticData::StaticData::LIGHT_RED;
    else if(name=="deep_sky_blue")
        return StaticData::DEEP_SKY_BLUE;
    else
        return StaticData::NULL_RESULT;
}
