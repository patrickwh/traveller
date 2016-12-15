#ifndef COMMONPALETTEANDFONT_H
#define COMMONPALETTEANDFONT_H

#include <QPalette>
#include <QFont>
#include "commoncolor.h"
#include "staticdata.h"

class CommonPaletteAndFont
{
public:
    CommonPaletteAndFont();
    static QPalette* BLACK_BG_WHTITE_TEXT;
    static QFont* TEXT_LABEL_FONT;
};

#endif // COMMONPALETTEANDFONT_H
