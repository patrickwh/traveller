#include "commonpaletteandfont.h"
QPalette* CommonPaletteAndFont::BLACK_BG_WHTITE_TEXT = new QPalette();
QFont* CommonPaletteAndFont::TEXT_LABEL_FONT = new QFont();
void b = CommonPaletteAndFont::BLACK_BG_WHTITE_TEXT->setColor(QPalette::Background,Qt::black);
bool b1 = CommonPaletteAndFont::BLACK_BG_WHTITE_TEXT->setColor(QPalette::WindowText,Qt::white);
bool b2 =  CommonPaletteAndFont::TEXT_LABEL_FONT->setPointSize(StaticData::TEXT_SIZE);

CommonPaletteAndFont::CommonPaletteAndFont()
{

}
