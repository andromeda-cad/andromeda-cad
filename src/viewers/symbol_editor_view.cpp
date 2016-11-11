#include <QApplication>
#include <QDebug>
#include <QLineF>

#include <QGraphicsTextItem>

#include "src/geometry/geometry.h"
#include "src/shapes/ellipse.h"
#include "src/shapes/text_item.h"
#include "src/symbol/symbol_pin.h"

#include "symbol_editor_view.h"

SymbolEditorView::SymbolEditorView(QWidget *parent) : AView(parent)
{
    addTool(&poly_tool_);
    addTool(&rect_tool_);
    addTool(&ellipse_tool_);
    addTool(&pin_tool_);

    scene_->addItem(&symbol_);

    setCacheMode(QGraphicsView::CacheBackground);

    addItems();
}

void SymbolEditorView::addItems()
{

#define TEST_TEXT
#define TEST_ELLIPSE
#define TEST_RECT

    AEllipse *ellipse;
    //ATextItem *text;
    APolyline *rect;

    QGraphicsTextItem *text;

    QElapsedTimer t;

    t.start();

    for (int i=-200; i<200; i+=5)
    {
        for (int j=-100; j<100; j+= 5)
        {
#ifdef TEST_TEXT
            //text = new ATextItem();
            text = new QGraphicsTextItem();
            text->setPlainText("ABCDE");
            text->setFlags(QGraphicsItem::ItemIsSelectable);
            //text->setText("ABCDE");
            text->setPos(i*15,j*15);
            text->setZValue(3);
            scene_->addItem(text);
#endif
#ifdef TEST_ELLIPSE
            ellipse = new AEllipse();
            ellipse->setRadius(5,5);
            ellipse->setLineWidth(5);
            ellipse->setPos(i*10,j*10);
            ellipse->setZValue(1);
            scene_->addItem(ellipse);
#endif

#ifdef TEST_RECT
            rect = new APolyline();

            rect->setLineWidth(2.5);

            rect->addPoint(QPointF(-5,-10));
            rect->addPoint(QPointF( 5,-10));
            rect->addPoint(QPointF( 5, 10));
            rect->addPoint(QPointF(-5, 10));
            rect->addPoint(QPointF(-5,-10));

            rect->setPos(i*12, j*12);
            rect->setZValue(2);
            scene_->addItem(rect);
#endif
        }
    }

    qDebug() << "Adding items took" << t.elapsed() << "ms";
}

void SymbolEditorView::keyPressEvent(QKeyEvent *event)
{
    if (nullptr == event) return;

    bool accepted = true;

    ATextItem *text;

    QElapsedTimer t;

    t.start();

    if (isToolActive())
    {
        sendKeyEventToTool(event);
    }
    else
    {
        // Tool activation keys
        switch (event->key())
        {
        case Qt::Key_Q:
            scene_->clear();

            qDebug() << "Clear scene took" << t.elapsed() << "ms";
            break;
        case Qt::Key_N:
            addItems();
            break;
        case Qt::Key_X: // Delete
            deleteSelectedItems();
            break;
        case Qt::Key_D:
            duplicateItems();
            break;
        case Qt::Key_L:
            startTool(&poly_tool_);
            break;
        case Qt::Key_E:
            startTool(&ellipse_tool_);
            break;
        case Qt::Key_R:
            startTool(&rect_tool_);
            break;
        case Qt::Key_P:
            startTool(&pin_tool_);
            break;
        case Qt::Key_T:
            text = new ATextItem();
            text->setText("Hello World");
            text->setPos(cursorPos());
            scene_->addItem(text);
            break;
        default:
            accepted = false;
            break;
        }
    }

    // If not used, pass upstream
    if (!accepted)
    {
        // Pass the event down the chain
        AView::keyPressEvent(event);
    }

    update();
}


void SymbolEditorView::onToolFinished(AToolBase *toolPtr)
{
    if (nullptr == toolPtr)
        return;

    void *pointer = (void *) toolPtr;

    //TODO - better pointer management, using qobjectcast or similar

    // Pointer comparison fun
    if (pointer == &poly_tool_)
    {
        APolyline *line = new APolyline();

        poly_tool_.getPolyline(*line);

        scene_->addItem(line);

        poly_tool_.reset();
    }
    else if (pointer == &ellipse_tool_)
    {
        AEllipse *ell = new AEllipse();

        ellipse_tool_.getEllipse(*ell);

        if (ell->rx() > 0 && ell->ry() > 0)
            scene_->addItem(ell);

        ellipse_tool_.reset();
    }
    else if (pointer == &rect_tool_)
    {
        APolyline *line = new APolyline();

        rect_tool_.getPolyline(*line);

        scene_->addItem(line);

        rect_tool_.reset();
    }
    else if (pointer == &pin_tool_)
    {
        symbol_.addPin(pin_tool_.getPin());
    }

    //qDebug() << symbol_.encodedString();
}
