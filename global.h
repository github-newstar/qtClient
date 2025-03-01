#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"
#include <memory>
#include <iostream>
#include <mutex>
#include <QString>
/**
 * repolish qss 用来刷新qss
 */
extern std::function<void(QWidget*)> repolish;
extern std::function<QString(QString)> xorString;
enum ReqId {
    //get verify code
    ID_GET_VARIFY_CODE = 1001,
    //regiter user
    ID_REQ_USER = 1002,
    ID_REG_USER = 1003,
};

enum Modules {
    REGISTERMOD = 0,
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1,   // prase json error
    ERR_NETWORK,    //net work error
};

extern QString gate_url_prefix;
#endif //GLOBAL_H
