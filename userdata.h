#pragma once
#include <QString>
class SearchInfo {
    public:
        SearchInfo(int uid, QString name, QString nick, QString desc, int sex);
        int uid_;
        QString name_;
        QString nick_;
        QString desc_;
        int sex_;
};