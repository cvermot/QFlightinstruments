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

#include <qfi/qfi_VOR.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_VOR::qfi_VOR( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemFaceFixed ( Q_NULLPTR ),
    _itemFace ( Q_NULLPTR ),
    _itemTo ( Q_NULLPTR ),
    _itemFrom ( Q_NULLPTR ),
    _itemFlag ( Q_NULLPTR ),
    _itemHand ( Q_NULLPTR ),
    _itemCase ( Q_NULLPTR ),

    _course ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalHsiCtr ( 120.0 , 120.0 ),

    _faceFixedZ ( -50 ),
    _faceZ ( -40 ),
    _toZ ( -30 ),
    _fromZ ( -20 ),
    _flagZ ( -10 ),
    _handZ ( 0 ),
    _caseZ (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_VOR::~qfi_VOR()
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

void qfi_VOR::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::setCourse( double course )
{
    _course = course;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::setDeviation( double deviation, CDI cdi )
{
    _deviation = deviation;
    _cdi = cdi;

    if ( _deviation < -1.0 ) _deviation = -1.0;
    if ( _deviation >  1.0 ) _deviation =  1.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemFaceFixed = new QGraphicsSvgItem( ":/qfi/images/vor/vor_face_fixed.svg" );
    _itemFaceFixed->setCacheMode( QGraphicsItem::NoCache );
    _itemFaceFixed->setZValue( _faceFixedZ );
    _itemFaceFixed->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFaceFixed->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemFaceFixed );

    _itemFace = new QGraphicsSvgItem( ":/qfi/images/vor/vor_face.svg" );
    _itemFace->setCacheMode( QGraphicsItem::NoCache );
    _itemFace->setZValue( _faceZ );
    _itemFace->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemFace );

    _itemTo = new QGraphicsSvgItem( ":/qfi/images/vor/vor_to.svg" );
    _itemTo->setCacheMode( QGraphicsItem::NoCache );
    _itemTo->setZValue( _toZ );
    _itemTo->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemTo->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemTo );

    _itemFrom = new QGraphicsSvgItem( ":/qfi/images/vor/vor_from.svg" );
    _itemFrom->setCacheMode( QGraphicsItem::NoCache );
    _itemFrom->setZValue( _fromZ );
    _itemFrom->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFrom->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemFrom );

    _itemFlag = new QGraphicsSvgItem( ":/qfi/images/vor/vor_flag.svg" );
    _itemFlag->setCacheMode( QGraphicsItem::NoCache );
    _itemFlag->setZValue( _flagZ );
    _itemFlag->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFlag->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemFlag );

    _itemHand = new QGraphicsSvgItem( ":/qfi/images/vor/vor_hand.svg" );
    _itemHand->setCacheMode( QGraphicsItem::NoCache );
    _itemHand->setZValue( _handZ );
    _itemHand->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHand->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemHand );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/vor/vor_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::reset()
{
    _itemFace = Q_NULLPTR;
    _itemCase = Q_NULLPTR;

    _course = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_VOR::updateView()
{
    _itemFace->setRotation( - _course );

    _itemHand->setTransformOriginPoint(QPoint(120,68));
    if ( _cdi != CDI::Off )
    {
        _itemFlag->setVisible(false);
        if(_cdi == CDI::TO)
        {
            _itemTo->setVisible(true);
            _itemFrom->setVisible(false);
        }
        else
        {
            _itemTo->setVisible(false);
            _itemFrom->setVisible(true);
        }
        _itemHand->setRotation(_deviation*40);
    }
    else
    {
        _itemFlag->setVisible(true);
        _itemTo->setVisible(false);
        _itemFrom->setVisible(false);

        _itemHand->setRotation(0.0);
    }

    _scene->update();
}
