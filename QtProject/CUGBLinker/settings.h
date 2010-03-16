#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
public:
    Settings();

public:
    typedef struct {
        QString	username;		//用户名
        QString password;		//密码
        int	range;                  //默认访问范围
        bool	savePwd;		//是否保存密码
        double	curTraffic;             //当前流量
        int	maxTraffic;             //流量控制阈值
        bool	showTip;		//超流量时是否提示
        bool	autoDis;		//超流量时是否自动断网
    } Account;

    QList<Account> accounts;

public:
    void addAccount(Account& account);
    void delAccount(QString username);
};

#endif // SETTINGS_H
