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

#include <qfi/qfi_ILS.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_ILS::qfi_ILS( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemFaceFixed ( Q_NULLPTR ),
    _itemFace ( Q_NULLPTR ),
    _itemFlagNav ( Q_NULLPTR ),
    _itemFlagGs ( Q_NULLPTR ),
    _itemHandNav ( Q_NULLPTR ),
    _itemHandGs ( Q_NULLPTR ),
    _itemCase ( Q_NULLPTR ),

    _course ( 0.0 ),
    _dotH ( 0.0 ),
    _dotV ( 0.0 ),
    _visibleH (false),
    _visibleV (false),

    _dotVPos( 0.0 ),
    _dotVPos_old ( 0.0 ),
    _dotHPos ( 0.0 ),
    _dotHPos_old ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalVorCtr ( 120.0 , 120.0 ),
    _originalHandCtr( 120, 68 ),

    _faceFixedZ ( -50 ),
    _handNavZ ( -40 ),
    _handGsZ ( -30 ),
    _faceZ ( -20 ),
    _flagNavZ ( -60 ),
    _flagGsZ ( -50 ),
    _caseZ (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_ILS::~qfi_ILS()
{
    if ( _scene != Q_NULLPTR )
    {
        _scene->clear();
        delete _scene;
        _scene = Q_NULLPTR;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::setCourse( double course )
{
    _course = course;
}

////////////////////////////////////////////////////////////////////////////////

void  qfi_ILS::setDots( double dotH, double dotV, bool visibleH, bool visibleV )
{
    _dotH = dotH;
    _dotV = dotV;
    _visibleH = visibleH;
    _visibleV = visibleH;

    if ( _dotH < -1.0 ) _dotH = -1.0;
    if ( _dotH >  1.0 ) _dotH =  1.0;
    if ( _dotV < -1.0 ) _dotV = -1.0;
    if ( _dotV >  1.0 ) _dotV =  1.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemFaceFixed = new QGraphicsSvgItem( ":/qfi/images/ils/ils_case_fixed.svg" );
    _itemFaceFixed->setCacheMode( QGraphicsItem::NoCache );
    _itemFaceFixed->setZValue( _faceFixedZ );
    _itemFaceFixed->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFaceFixed->setTransformOriginPoint( _originalVorCtr );
    _scene->addItem( _itemFaceFixed );

    _itemFace = new QGraphicsSvgItem( ":/qfi/images/ils/ils_face.svg" );
    _itemFace->setCacheMode( QGraphicsItem::NoCache );
    _itemFace->setZValue( _faceZ );
    _itemFace->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace->setTransformOriginPoint( _originalVorCtr );
    _scene->addItem( _itemFace );

    _itemFlagNav = new QGraphicsSvgItem( ":/qfi/images/ils/ils_flag_nav.svg" );
    _itemFlagNav->setCacheMode( QGraphicsItem::NoCache );
    _itemFlagNav->setZValue( _flagGsZ );
    _itemFlagNav->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFlagNav->setTransformOriginPoint( _originalVorCtr );
    _scene->addItem( _itemFlagNav );

    _itemFlagGs = new QGraphicsSvgItem( ":/qfi/images/ils/ils_flag_gs.svg" );
    _itemFlagGs->setCacheMode( QGraphicsItem::NoCache );
    _itemFlagGs->setZValue( _flagGsZ );
    _itemFlagGs->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFlagGs->setTransformOriginPoint( _originalVorCtr );
    _scene->addItem( _itemFlagGs );

    _itemHandNav = new QGraphicsSvgItem( ":/qfi/images/ils/ils_hand_nav.svg" );
    _itemHandNav->setCacheMode( QGraphicsItem::NoCache );
    _itemHandNav->setZValue( _handNavZ );
    _itemHandNav->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHandNav->setTransformOriginPoint( _originalHandCtr );
    _scene->addItem( _itemHandNav );

    _itemHandGs = new QGraphicsSvgItem( ":/qfi/images/ils/ils_hand_gs.svg" );
    _itemHandGs->setCacheMode( QGraphicsItem::NoCache );
    _itemHandGs->setZValue( _handGsZ );
    _itemHandGs->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHandGs->setTransformOriginPoint( _originalHandCtr );
    _scene->addItem( _itemHandGs );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/ils/ils_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::reset()
{
    _itemFace = Q_NULLPTR;
    _itemCase = Q_NULLPTR;

    _course = 0.0;
    _dotVPos_old = 0.0;
    _dotVPos = 0.0;
    _dotHPos_old = 0.0;
    _dotHPos = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ILS::updateView()
{
    _itemFace->setRotation( - _course );

    _dotVPos_old = _dotVPos;
    _dotHPos_old = _dotHPos;

    _dotVPos = -_dotV*38.0;
    _dotHPos = _dotH*38.0;

    _itemHandNav->moveBy(_dotHPos - _dotHPos_old, 0.0);
    _itemHandGs->moveBy(0.0, _dotVPos - _dotVPos_old);

    _scene->update();
}
