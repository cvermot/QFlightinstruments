/****************************************************************************//*
 * Copyright (C) 2024 Clement Vermot-Desroches
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef WIDGETVOR_H
#define WIDGETVOR_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi/qfi_VOR.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
class WidgetVOR;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetVOR : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetVOR( QWidget *parent = Q_NULLPTR );

    ~WidgetVOR();

    inline void redraw() { _vor->redraw(); }

    inline void setCourse( double course )
    {
        _vor->setCourse( course );
    }

    inline void setDeviation( double deviation, CDI cdi )
    {
        _vor->setDeviation( deviation, cdi );
    }

private:

    Ui::WidgetVOR  *_ui;
    qfi_VOR        *_vor;
    LayoutSquare  *_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETVOR_H
