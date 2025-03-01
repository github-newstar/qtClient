#include "global.h"
#include<QString>
QString gate_url_prefix = "";
std::function<void(QWidget *)> repolish = [](QWidget *w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> xorString = [](QString str) {
    QString result = str;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        result[i] = QChar(static_cast<ushort>(str[i].unicode() ^ static_cast<ushort>(len)));
    }
    return result;
};
