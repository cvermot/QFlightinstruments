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
#ifndef QFI_ILS_H
#define QFI_ILS_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QGraphicsSvgItem>

#include <qfi/qfi_defs.h>
#include <qfi/qfi_enums.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Horizontal Indicator widget class.
 */
class QFIAPI qfi_ILS : public QGraphicsView
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit qfi_ILS( QWidget *parent = Q_NULLPTR );

    /** Destructor. */
    virtual ~qfi_ILS();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();

    /** @param course [deg] */
    void setCourse( double course );

    /**
     * @param normalized horizontal deviation dot position (range from -1.0 to 1.0)
     * @param normalized vertical deviation dot position (range from -1.0 to 1.0)
     * @param deviation horizontal dot visibility
     * @param deviation vertical dot visibility */
    void setDots( double dotH, double dotV, bool visibleH, bool visibleV );

protected:

    /** */
    void resizeEvent( QResizeEvent *event );

private:

    QGraphicsScene *_scene;

    QGraphicsSvgItem *_itemFaceFixed;
    QGraphicsSvgItem *_itemFace;
    QGraphicsSvgItem *_itemTo;
    QGraphicsSvgItem *_itemFrom;
    QGraphicsSvgItem *_itemFlagNav;
    QGraphicsSvgItem *_itemFlagGs;
    QGraphicsSvgItem *_itemHandNav;
    QGraphicsSvgItem *_itemHandGs;
    QGraphicsSvgItem *_itemCase;

    double _course;
    double _dotH;
    double _dotV;
    bool _visibleH;
    bool _visibleV;

    double _dotVPos;
    double _dotVPos_old;
    double _dotHPos;
    double _dotHPos_old;

    double _scaleX;
    double _scaleY;

    const int _originalHeight;
    const int _originalWidth;

    QPointF _originalVorCtr;
    QPointF _originalHandCtr;

    const int _faceFixedZ;
    const int _handNavZ;
    const int _handGsZ;
    const int _faceZ;
    const int _flagNavZ;
    const int _flagGsZ;
    const int _caseZ;

    void init();

    void reset();

    void updateView();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_ILS_H
