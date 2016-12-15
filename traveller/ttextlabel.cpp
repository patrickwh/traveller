#include "ttextlabel.h"

TTextLabel::TTextLabel(QString str,int textSize,int height,bool fixedHeight) : QLabel(str)
{
    QPalette* whiteText = new QPalette();
    whiteText->setColor(QPalette::WindowText,*CommonColor::WHITE);
    QFont* flabel = new QFont();
    flabel->setPointSize(textSize);

    this->setPalette(*whiteText);
    this->setFont(*flabel);
    if(fixedHeight) this->setFixedHeight(height);

    this->setWordWrap(true);

    setContentsMargins(0,0,0,0);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    style = StyleSheetCeator::setBorder(style,"none");
    style = StyleSheetCeator::setPadding(style,0,0,0,0);
    style = StyleSheetCeator::setValue(style,"font-style","bold");
    this->setStyleSheet(StyleSheetCeator::getStyleSeetString(style));
}
