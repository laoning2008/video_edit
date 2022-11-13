#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H

#include <QMetaType>
#include <QPointF>
#include <QVector>
#include <QImage>

class MediaItem
{
public:
    static const uint32_t DEFAULT_TIME_LEN = 5;

    enum MediaType {
        MediaType_Unknown,
        MediaType_Video,
        MediaType_Image,
        MediaType_Audio,
    };

    enum MaterialType {
        MaterialType_Unknown,
        MaterialType_Media,
        MaterialType_Audio,
        MaterialType_Text,
        MaterialType_Sticker,
        MaterialType_EffectE,
        MaterialType_Transition,
        MaterialType_Filter,
    };

    MediaItem();
    MediaItem(QString uri, QString name, uint32_t timeLen, MediaType mediaType, MaterialType materialType, bool local, QString thumbnail);

    QString                         uri;
    QString                         name;
    uint32_t                        timeLen;
    MediaType                       mediaType;
    MaterialType                    materialType;
    bool                            local;
    QString                         thumbnail;
};

Q_DECLARE_METATYPE(MediaItem)

#endif
