#include <QtWidgets>
#include <cmath>

#include "ui/MediaItem.h"

MediaItem::MediaItem()
    : mediaType(MediaType_Unknown)
    , materialType(MaterialType_Unknown)
    , timeLen(DEFAULT_TIME_LEN)
    , local(true){

}

MediaItem::MediaItem(QString uri, QString name, uint32_t timeLen, MediaType mediaType, MaterialType materialType, bool local, QString thumbnail)
    : uri(uri)
    , name(name)
    , timeLen(timeLen)
    , mediaType(mediaType)
    , materialType(materialType)
    , local(local)
    , thumbnail(thumbnail) {

}
