#pragma once
#include <QString>
class SearchInfo {
    public:
        SearchInfo(int uid, QString name, QString nick, QString desc, int sex) : 
            uid_(uid), name_(name), nick_(nick), desc_(desc), sex_(sex) {}
        int uid_;
        QString name_;
        QString nick_;
        QString desc_;
        int sex_;
};