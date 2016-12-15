#ifndef STATICDATA_H
#define STATICDATA_H

#include <QString>
#include <QHash>

class StaticData
{
public:
    StaticData();
    const static int NORMAL_TEXT_HEIGHT = 75;
    const static int SMALL_TEXT_HEIGHT = 50;
    const static int SMALL_TEXT_SIZE = 10;
    const static int NORMAL_TEXT_SIZE = 15;
    const static int BACKGOUND_COLOR = 0;
    const static int TEXT_COLOR = 1;
    const static int DAY_ITEM_FRAME_WIDTH = 800;
    const static int EVENT_FRAME_WIDTH = DAY_ITEM_FRAME_WIDTH - 180;
    const static int TRIP_FRAME_HEIGHT = 250;
    const static int ADD_NEW_DAY_BUTTON_WIDTH = 200;
    const static int DELETE_BUTTON_HEIGHT = 40;
    const static int NORMAL_BUTTON_HIGHT = NORMAL_TEXT_HEIGHT;
    const static int SMALL_BUTTON_HEIGHT = SMALL_TEXT_HEIGHT;
    static const double MAIN_WINDOW_WIDTH_RATIO;
    static const double MAIN_WINDOW_HEIGHT_RATIO;
    static const double ADD_TRIP_WIDONW_WIDTH_RATIO;
    static const double ADD_TRIP_WIDONW_HEIGHT_RATIO;
    static const double ADD_EVENT_WIDONW_WIDTH_RATIO;
    static const double ADD_EVENT_WIDONW_HEIGHT_RATIO;
    const static int SAVE_AND_CLOSE = 0;
    const static int CANCEL_AND_CLOSE = 1;
    const static int NORMAL_TEXT_COMBOBOX = 0;
    const static int COLOR_SELECT_COMBOBOX = 1;
    const static int COLOR_SET_SIZE = 12;
    const static int ADD_NEW_WINDOW = 0;
    const static int UPDATE_INFO_WINDOW = 1;

    static const QString DATE_STORATION_FORMAT;
    static const QString DATE_DISPLAY_FORMAT;
    static const QString NULL_RESULT;
    static const QString EDIT_ICON_PATH;
    static const QString DELETE_ICON_PATH;
    static const QString LIGHT_BLUE;
    static const QString WHITE;
    static const QString BLACK;
    static const QString LINGHT_PINK;
    static const QString LIGHT_RED;
    static const QString LIGHT_ORANGE;
    static const QString LIGHT_PURPLE;
    static const QString GOLD;
    static const QString LIGHT_GRAY;
    static const QString LIGHT_GREEN;
    static const QString LIGHT_MAGENTA;
    static const QString DARK_CYAN;
    static const QString LIGHT_FORESTGREEN;
    static const QString DEEP_SKY_BLUE;

    static QString COLOR_SET[];

    static QString getColorByName(QString name);
};

#endif // STATICDATA_H
