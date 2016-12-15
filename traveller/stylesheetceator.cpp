#include "stylesheetceator.h"

StyleSheetCeator::StyleSheetCeator()
{

}

QHash<QString,QString> StyleSheetCeator::setValue(QHash<QString, QString> style, QString key, QString value){
    if(style.contains(key)) style[key] = value;
    else style.insert(key,value);
    return style;
}

QHash<QString,QString> StyleSheetCeator::setBackgroundColor(QHash<QString,QString> style,QString color){
    return StyleSheetCeator::setValue(style,"background-color","#"+color);
}

QHash<QString,QString> StyleSheetCeator::setPadding(QHash<QString,QString> style,int xl,int xr,int yt,int yb){
    QString value = QString::number(yt)+"px "+QString::number(xr)+"px "+QString::number(yb)+"px "+QString::number(xl)+"px";
    return StyleSheetCeator::setValue(style,"padding",value);
}

QHash<QString,QString> StyleSheetCeator::setTextFont(QHash<QString,QString> style,int size,QString textStyle){
    QString value = QString::number(size)+"pt "+textStyle;
    return StyleSheetCeator::setValue(style,"font",value);
}

QHash<QString,QString> StyleSheetCeator::setBorder(QHash<QString, QString> style, QString value){
    return StyleSheetCeator::setValue(style,"border",value);
}

QHash<QString,QString> StyleSheetCeator::setBorderColor(QHash<QString, QString> style, QString color){
    return StyleSheetCeator::setValue(style,"border-color",color);
}

QString StyleSheetCeator::getStyleSeetString(QHash<QString, QString> style){
    QHash<QString,QString>::iterator itr;
    QString r ="";
    for(itr=style.begin();itr!=style.end();++itr){
        r += itr.key()+":"+itr.value()+";";
    }
    return r;
}
