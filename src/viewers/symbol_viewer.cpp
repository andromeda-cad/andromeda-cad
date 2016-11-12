#include "symbol_viewer.h"

ASymbolViewer::ASymbolViewer(QWidget *parent) : AView(parent)
{
    setCacheMode(QGraphicsView::CacheBackground);

    // Add the symbol to the scene
    scene_->addItem(&symbol_);
}
