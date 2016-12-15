#ifndef TPALETTE_H
#define TPALETTE_H

#include <QPalette>
#include "commoncolor.h"
#include "staticdata.h"

class TPalette : public QPalette
{
public:
    TPalette(int target = StaticData::TEXT_COLOR,QColor* color = CommonColor::WHITE);
};

#endif // TPALETTE_H
