#ifndef STYLESHEETCEATOR_H
#define STYLESHEETCEATOR_H

#include <QString>
#include <QHash>
#include <iterator>

class StyleSheetCeator
{
public:
    StyleSheetCeator();
    static QHash<QString,QString> setValue(QHash<QString,QString> style,QString key,QString value);
    static QHash<QString,QString> setBackgroundColor(QHash<QString,QString> style,QString color);
    static QHash<QString,QString> setPadding(QHash<QString,QString> style,int xl,int xr,int yt,int yb);
    static QHash<QString,QString> setTextFont(QHash<QString,QString> style,int size,QString textStyle = "plain");
    static QHash<QString,QString> setBorder(QHash<QString,QString> style,QString value);
    static QHash<QString,QString> setBorderColor(QHash<QString,QString> style,QString color);
    static QString getStyleSeetString(QHash<QString,QString> style);
};

#endif // STYLESHEETCEATOR_H
