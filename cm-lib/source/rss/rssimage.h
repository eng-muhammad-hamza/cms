#ifndef RSSIMAGE_H
#define RSSIMAGE_H

#include <QObject>
#include <QScopedPointer>
#include <QtXml/QDomNode>
#include <cm-lib_global.h>

namespace cm {
namespace rss {

class CMLIB_EXPORT RssImage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint16 ui_height READ height CONSTANT)
    Q_PROPERTY(quint16 ui_width READ width CONSTANT)
    Q_PROPERTY(QString ui_link READ link CONSTANT)
    Q_PROPERTY(QString ui_title READ title CONSTANT)
    Q_PROPERTY(QString ui_url READ url CONSTANT)
public:
    explicit RssImage(QObject *parent = nullptr, const QDomNode& domNode = QDomNode());
    ~RssImage();

    quint16 height() const;
    quint16 width() const;
    const QString& link() const;
    const QString& title() const;
    const QString& url() const;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

signals:
};

}
}

#endif // RSSIMAGE_H
