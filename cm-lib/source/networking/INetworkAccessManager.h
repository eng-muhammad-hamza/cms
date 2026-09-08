#ifndef INETWORKACCESSMANAGER_H
#define INETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace cm {
namespace networking {

class INetworkAccessManager {
public:
    INetworkAccessManager() {}
    virtual ~INetworkAccessManager() {}

    virtual QNetworkReply* get(const QNetworkRequest& request) = 0;
};

}
}

#endif // INETWORKACCESSMANAGER_H
