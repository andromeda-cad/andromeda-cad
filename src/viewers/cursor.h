#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsItem>
#include <QPen>

class ACursorItem : public QGraphicsItem
{
public:
    ACursorItem( void );

    QRectF boundingRect(void) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setSize( int size );
    int size( void) { return size_; }

protected:
    //! Cursor size (in pixels)
    int size_ = 15;

    //! Cursor bounding box
    QRectF bb_;

    //! Cursor pen
    QPen pen_;
};

#endif // CURSOR_H

