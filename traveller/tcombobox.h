#ifndef TCOMBOBOX_H
#define TCOMBOBOX_H

#include <QComboBox>
#include <QIcon>
#include "tfont.h"
#include "staticdata.h"

class TComboBox : public QComboBox
{
public:
    TComboBox(int type = StaticData::NORMAL_TEXT_COMBOBOX);
    void setList(QStringList str);
};

#endif // TCOMBOBOX_H
