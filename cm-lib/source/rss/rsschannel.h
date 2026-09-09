#ifndef RSSCHANNEL_H
#define RSSCHANNEL_H

#include <QDateTime>
#include <QObject>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QList>
#include <QtQml/QQmlListProperty>
#include <QString>

#include <cm-lib_global.h>
#include <rss/rssimage.h>
#include <rss/rssitem.h>

namespace cm {
namespace rss {

class CMLIB_EXPORT RssChannel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ui_description READ description CONSTANT)
    Q_PROPERTY(QString ui_link READ link CONSTANT)
    Q_PROPERTY(QString ui_title READ title CONSTANT)
    Q_PROPERTY(cm::rss::RssImage* ui_image READ image CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::rss::RssItem> ui_items READ ui_items CONSTANT)

public:
    explicit RssChannel(QObject *parent = nullptr, const QDomNode& domNode = QDomNode());
    ~RssChannel();

    void addItem(RssItem* item);
    const QString& description() const;
    const QString& link() const;
    const QString& title() const;
    RssImage* image() const;
    const QList<RssItem*>& items() const;
    void setImage(RssImage* image);
    QQmlListProperty<RssItem> ui_items();

    static RssChannel* fromXml(const QByteArray& xmlData,QObject* parent = nullptr);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

signals:
};

}
}

#endif // RSSCHANNEL_H
