#ifndef TTEXTLABEL_H
#define TTEXTLABEL_H

#include <QLabel>
#include "commoncolor.h"
#include "staticdata.h"
#include "stylesheetceator.h"

class TTextLabel : public QLabel
{
public:
    TTextLabel(QString str,int textSize=StaticData::NORMAL_TEXT_SIZE,int height = StaticData::NORMAL_TEXT_HEIGHT,\
            bool fixedHeight = true);
    QHash<QString,QString> style;
};

#endif // TTEXTLABEL_H
