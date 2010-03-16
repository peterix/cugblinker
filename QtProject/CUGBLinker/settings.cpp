#include "settings.h"

Settings::Settings()
{
}

void Settings::addAccount(Account& account)
{
    accounts.append(account);
}

void Settings::delAccount(QString username)
{
    for(int i=0; i<accounts.size(); i++)
    {
        if(accounts[i].username==username)
        {
            accounts.removeAt(i);
            break;
        }
    }
}
