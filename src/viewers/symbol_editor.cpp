#include <QApplication>
#include <QDebug>
#include <QLineF>

#include <QGraphicsTextItem>

#include "src/dialogs/symbol_editor/graphic_item_editor_dialog.h"
#include "src/dialogs/symbol_editor/pin_editor_dialog.h"

#include "src/geometry/geometry.h"

#include "src/shapes/ellipse.h"
#include "src/shapes/text_item.h"

#include "src/symbol/symbol_pin.h"

#include "symbol_editor.h"

ASymbolEditor::ASymbolEditor(QWidget *parent) : ASymbolViewer(parent)
{
    addTool( &poly_tool_ );
    addTool( &rect_tool_ );
    addTool( &ellipse_tool_ );
    addTool( &pin_tool_ );
    addTool( &text_tool_ );

    // Test function to add thousands of items to the scene
    // (to test rendering performance)
    //addItems();

    // Enable selection
    selection_enabled_ = true;

    connect( &symbol_, SIGNAL( edited() ), this, SLOT( symbolEdited() ) );
}

void ASymbolEditor::addItems()
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

/**
 * @brief ASymbolEditor::editItems
 * Edit the selected items
 * Action to be performed depends on the selected items,
 * or whether a tool is currently active
 */
void ASymbolEditor::editItems()
{
    if ( isToolActive() )
    {
        // Instruct the active tool to open an edit dialog
        current_tool_->openEditor();
        return;
    }

    QList<QGraphicsItem*> items = scene_->selectedItems();

    if ( items.count() == 0)
    {
        return;
    }
    // Single item is selected
    else if ( items.count() == 1 )
    {
        editSingleItem( static_cast<ADrawableBase*>( items.first() ) );
    }
    else
    {
        //TODO
        qDebug() << "Multiple edit:" << items.count();
    }
}

void ASymbolEditor::editSingleItem(ADrawableBase *item)
{
    if ( nullptr == item ) return;

    qDebug() << "Edit item:" << item->objectName();

    AEllipse *itemEllipse;
    APolyline *itemPolyline;
    ASymbolPin *itemPin;
    ATextItem *itemText;

    GraphicItemEditorDialog dlgGraphic;
    PinEditorDialog dlgPin;


    // Determine the type of item, pass it to the correct editing window
    //TODO is there a better way to do this?

    itemEllipse = static_cast<AEllipse*>( item );
    itemPolyline = static_cast<APolyline*>( item );
    itemPin = static_cast<ASymbolPin*>( item );
    itemText = static_cast<ATextItem*>( item );

    //TODO casting to AEllipse NEVER fails, no matter the object passed.

    //TODO investigate this

#warning "static cast is not working as expected?"

    if ( nullptr != itemEllipse )
    {
        qDebug() << "ell";
        dlgGraphic.setWindowTitle( tr( "Ellipse Properties" ) );

        dlgGraphic.editObject( itemEllipse );
    }
    else if ( nullptr != itemPolyline )
    {
        dlgGraphic.setWindowTitle( tr( "Polyline Properties" ) );
        dlgGraphic.editObject( itemPolyline );
    }
    else if ( nullptr != itemPin )
    {
        dlgPin.editObject( itemPin );
    }
    else if ( nullptr != itemText )
    {
        //TODO
        qDebug() << "edit text item";
    }
}

void ASymbolEditor::keyPressEvent(QKeyEvent *event)
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
            startTool( &poly_tool_ );
            break;
        case Qt::Key_E:
            startTool( &ellipse_tool_ );
            break;
        case Qt::Key_R:
            startTool( &rect_tool_ );
            break;
        case Qt::Key_P:
            startTool( &pin_tool_ );
            break;
        case Qt::Key_T:
            startTool( &text_tool_ );
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


void ASymbolEditor::onToolFinished(AToolBase *toolPtr)
{
    if (nullptr == toolPtr)
        return;

    void *pointer = (void *) toolPtr;

    //TODO - better pointer management, using qobjectcast or similar

    // Pointer comparison fun
    if ( pointer == &poly_tool_ )
    {
        APolyline *line = new APolyline();

        poly_tool_.getPolyline( *line );

        scene_->addItem( line );

        poly_tool_.reset();
    }
    else if ( pointer == &ellipse_tool_ )
    {
        AEllipse *ell = new AEllipse();

        ellipse_tool_.getEllipse( *ell );

        if ( ell->rx() > 0 && ell->ry() > 0 )
            scene_->addItem( ell );

        ellipse_tool_.reset();
    }
    else if ( pointer == &rect_tool_ )
    {
        APolyline *line = new APolyline();

        rect_tool_.getPolyline( *line );

        scene_->addItem( line );

        rect_tool_.reset();
    }
    else if ( pointer == &pin_tool_ )
    {
        symbol_.addPin(pin_tool_.getPin());
    }
    else if ( pointer == &text_tool_ )
    {
        ATextItem *txt = text_tool_.getText();

        scene_->addItem( txt );
    }

    //qDebug() << symbol_.encodedString();
}

void ASymbolEditor::symbolEdited()
{
    qDebug() << "symbol was edited";
}
