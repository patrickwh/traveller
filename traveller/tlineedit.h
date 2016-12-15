#ifndef TLINEEDIT_H
#define TLINEEDIT_H

#include<QLineEdit>
#include "commonpaletteandfont.h"

class TLineEdit : public QLineEdit
{
public:
    TLineEdit(QString hint,int width = 0);
};

#endif // TLINEEDIT_H
