#include "rssimage.h"

namespace cm {
namespace rss {

class RssImage::Implementation {
public:
    QString url;    // Mandatory. Url of GIF , JPEG OR PNG That represent the channel
    QString title;  // Mandatory. Describes the Image
    QString link;   // Mandatory. Url of the Site
    quint16 width;  // Optional. Width in Pixels. Max 144 - Default 88
    quint16 height; // Optional. Height in Pixels. Max 400 - Default 31

    void update(const QDomNode& domNode) {
        QDomElement imageUrl = domNode.firstChildElement("url");
        if(!imageUrl.isNull()) { url = imageUrl.text(); }
        QDomElement imageTitle = domNode.firstChildElement("title");
        if(!imageTitle.isNull()) { title = imageTitle.text(); }
        QDomElement imageLink = domNode.firstChildElement("link");
        if(!imageLink.isNull()) { link = imageLink.text(); }
        QDomElement imageWidth = domNode.firstChildElement("width");
        if(!imageWidth.isNull()) {
            width = static_cast<quint16>(imageUrl.text().toShort());
        } else {
            width = 88;
        }
        QDomElement imageHeight = domNode.firstChildElement("height");
        if(!imageHeight.isNull()) {
            height = static_cast<quint16>(imageHeight.text().toShort());
        } else {
            height = 31;
        }
    }
};

RssImage::RssImage(QObject *parent, const QDomNode &domNode)
    : QObject(parent)
{
    implementation.reset(new Implementation());
    implementation->update(domNode);
}

RssImage::~RssImage() {}

quint16 RssImage::height() const { return implementation->height; }

quint16 RssImage::width() const { return implementation->width; }

const QString& RssImage::url() const { return implementation->url; }

const QString& RssImage::title() const { return implementation->title; }

const QString& RssImage::link() const { return implementation->link; }

}
}
