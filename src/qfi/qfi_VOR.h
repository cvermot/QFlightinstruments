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
#ifndef QFI_VOR_H
#define QFI_VOR_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QGraphicsSvgItem>

#include <qfi/qfi_defs.h>
#include <qfi/qfi_enums.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Horizontal Indicator widget class.
 */
class QFIAPI qfi_VOR : public QGraphicsView
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit qfi_VOR( QWidget *parent = Q_NULLPTR );

    /** Destructor. */
    virtual ~qfi_VOR();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();

    /** @param course [deg] */
    void setCourse( double course );

    /** @param deviation [-] */
    void setDeviation( double deviation, CDI cdi = CDI::Off );

protected:

    /** */
    void resizeEvent( QResizeEvent *event );

private:

    QGraphicsScene *_scene;

    QGraphicsSvgItem *_itemFaceFixed;
    QGraphicsSvgItem *_itemFace;
    QGraphicsSvgItem *_itemTo;
    QGraphicsSvgItem *_itemFrom;
    QGraphicsSvgItem *_itemFlag;
    QGraphicsSvgItem *_itemHand;
    QGraphicsSvgItem *_itemCase;

    double _course;
    double _deviation;                  ///<
    CDI _cdi;                           ///<

    double _scaleX;
    double _scaleY;

    const int _originalHeight;
    const int _originalWidth;

    QPointF _originalHsiCtr;

    const int _faceFixedZ;
    const int _faceZ;
    const int _toZ;
    const int _fromZ;
    const int _flagZ;
    const int _handZ;
    const int _caseZ;

    void init();

    void reset();

    void updateView();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_VOR_H
