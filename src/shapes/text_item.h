#ifndef TEXT_ITEM
#define TEXT_ITEM

#include <QFont>
#include <QStaticText>

#include "src/drawable/drawable_primitive.h"

class ATextItem : public ADrawablePrimitive
{
    Q_OBJECT

    Q_PROPERTY( QString text READ text WRITE setText )
    Q_PROPERTY( double width READ width )
    Q_PROPERTY( double height READ height )
    Q_PROPERTY( int alignment READ alignment WRITE setAlignment )

public:
    ATextItem(QObject *parent = 0);
    virtual ATextItem *clone(void) override { return makeClone<ATextItem>(); }

    enum Alignment
    {
        LEFT  = 0,
        RIGHT = 0x01,
        CENTER = 0x02,
    };

    // Painter functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Property getters
    QString text(void) const { return text_; }
    double width(void) const { return width_; }
    double height(void) const { return height_; }
    int alignment(void) const { return alignment_; }

    // Encode / decode
    virtual void encode(AJsonObject &data, bool hideDefaults) const override;
    virtual void decode(AJsonObject &data, bool undoable = false) override;

public slots:
    void setText(QString text);
    void setAlignment( int alignment );
    virtual void updateBoundingBox(void) override;

protected:
    QString text_;

    QStaticText static_text_;

    QFont font_;

    int alignment_ = Alignment::LEFT;

    double width_  = 0;
    double height_ = 0;

    bool allow_multiline_ = false;

    void updateFont(void);
};

#endif // TEXT_ITEM

