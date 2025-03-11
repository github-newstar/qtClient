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
    ID_REG_USER = 1002,
    //重置密码
    ID_RESET_PWD = 1003,
    //用户登录
    ID_LOGIN_USER = 1004,
    //登录聊天服务器
    ID_CHAT_LOGIN = 1005,
    //登录聊天服务器回包
    ID_CHAST_LOGIN_RSP = 1006,
};

enum Modules {
    REGISTERMOD = 0,
    
    RESETMOD = 1,
    
    LOGINMOD = 2,
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1,   // prase json error
    ERR_NETWORK,    //net work error
};

enum TipErr {
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_VARIFY_ERR = 4,
    TIP_USER_ERR = 5,
};

enum ClickLbState {
    NORMAL = 0,
    SELECTED = 1
};

enum ChatUIMode {
    ChatMode = 0,
    ContactMode = 1,
    SearchMode = 2,
};
enum ListItemType{
    CHAT_USER_ITEM, //聊天用户
    COTACT_USER_ITEM,//联系人
    SEARCH_USER_ITEM,//搜索到的用户
    ADD_USER_TIP_ITEM,//提示添加用户
    INVALID_ITEM,   //不可点击条目
    GROUP_TIP_ITEM  //分组提示条目
};

struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};

enum class ChatRole {
    Self,
    Other
};

struct MsgInfo{
    QString msgFlag;
    QString content;    //表示文件和图像的url,文本消息
    QPixmap pixmap;     //文件盒图像的缩略图
};


extern QString gate_url_prefix;
#endif //GLOBAL_H
