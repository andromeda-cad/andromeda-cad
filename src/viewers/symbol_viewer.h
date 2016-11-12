#ifndef SYMBOL_VIEWER_H
#define SYMBOL_VIEWER_H

#include "src/symbol/schematic_symbol.h"

#include "andromeda_view.h"

/**
 * @brief The ASymbolViewer class defines a viewer for a single
 * ASchematicSymbol object.
 * The symbol viewer does not provide editing capabilities,
 * it should be thought of as a "preview" of the symbol,
 * e.g. when selecting a symbol from a list or menu.
 */

class ASymbolViewer : public AView
{
    Q_OBJECT

public:
    ASymbolViewer(QWidget *parent = 0);

public slots:
    ASchematicSymbol *symbol( void ) { return &symbol_; }

protected:
    // The symbol object to be displayed
    ASchematicSymbol symbol_;

};

#endif // SYMBOL_VIEWER_H

