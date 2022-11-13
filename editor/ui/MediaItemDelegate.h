#ifndef MEDIAITEMDELEGATE_H
#define MEDIAITEMDELEGATE_H

#include <QStyledItemDelegate>

class MediaItemDelegate : public QStyledItemDelegate
{
public:
    MediaItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // MEDIAITEMDELEGATE_H
