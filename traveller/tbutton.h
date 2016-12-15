#ifndef TBUTTON_H
#define TBUTTON_H

#include <QPushButton>
#include "staticdata.h"
#include "stylesheetceator.h"

class TButton : public QPushButton
{
private:
    void setBasicStyleSheet();
public:
    TButton(QString str,int width);
    TButton(QString str);
    TButton(int h,int w);
    QHash<QString,QString> style;
};

#endif // TBUTTON_H
