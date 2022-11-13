#include <QPainter>
#include <QDebug>
#include <QFontMetrics>
#include "ui/MediaItemDelegate.h"
#include "ui/MediaItem.h"

MediaItemDelegate::MediaItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void MediaItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole);
        MediaItem itemData = var.value<MediaItem>();

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QRectF imageRect = QRect(rect.left(), rect.top(), rect.width(), rect.height() - 30);
        QRectF textRect = QRect(imageRect.left(), imageRect.bottom() + 5, rect.width(), 20);

        painter->drawImage(imageRect, QImage(itemData.thumbnail));

        painter->setPen(QPen(Qt::black));
        auto font = QFont("Microsoft Yahei", 15);
        painter->setFont(font);
        QString strDes = itemData.name;
        QFontMetrics fontMetrics(font);
        if(fontMetrics.width(itemData.name) > textRect.width()) {
            strDes = fontMetrics.elidedText(itemData.name, Qt::ElideMiddle, textRect.width());
        }
        painter->drawText(textRect, strDes);

        painter->restore();
    }
}

QSize MediaItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, 150);
}
