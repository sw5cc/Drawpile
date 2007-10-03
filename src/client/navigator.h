/*
   Copyright (C) 2007 M.K.A.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef Navigator_H
#define Navigator_H

#include "../config.h"

#include <QDockWidget> // inherited by Navigator
#include <QGraphicsView> // inherited by NavigatorView
#include <QRectF>

//! Navigator graphics view
class NavigatorView
	: public QGraphicsView
{
	Q_OBJECT
public:
	//! ctor
	NavigatorView(QGraphicsScene *scene, QWidget *parent);
	
signals:
	//! Signal rectangle movement
	void focusMoved(int x, int y);
	
public slots:
	//! Set rectangle to point
	void moveFocus(const QPoint& pt);
	//! Set rectangle
	void setFocus(const QRectF& rect);
	
protected:
	//! Draw rectangle
	void drawForeground(QPainter *painter, const QRectF& rect);
	
	//! Drag rectangle if button is pressed
	void mouseMoveEvent(QMouseEvent *event);
	//! Move rectangle and enable dragging
	void mousePressEvent(QMouseEvent *event);
	//! Disable dragging
	void mouseReleaseEvent(QMouseEvent *event);
	
	QRectF rect_;
	
	//! Is dragging?
	bool dragging_;
};

//! Minimal layout for Navigator dock
class NavigatorLayout
	: public QWidget
{
	Q_OBJECT
public:
	NavigatorLayout(QWidget *parent, NavigatorView *view);
};

//! Navigator dock widget
class Navigator
	: public QDockWidget
{
	Q_OBJECT
protected:
	//! Viewport
	NavigatorView *view_;
	QGraphicsScene *scene_;
public:
	//! Ctor
	Navigator(QWidget *parent, QGraphicsScene *scene);
	//! Dtor
	~Navigator();
signals:
	//! Signaled when user moves the rectangle to some other spot
	//void focusMoved(const QRect& focus);
	
	//! Signal for editorview
	void focusMoved(int x, int y);
	
	//! Proxy signal for NavigatorLayout.zoomIn()
	void zoomIn();
	//! Proxy signal for NavigatorLayout.zoomOut()
	void zoomOut();
	
public slots:
	//! Enable/disable delayed update
	void delayedUpdate(bool enable);
	//! Update 
	void update();
	//! Set associated graphics scene
	void setScene(QGraphicsScene *scene);
	//! Set view rectangle to different spot
	void setFocus(const QRectF& focus);
	//! Re-scale the viewport
	void rescale();
	//! Should be called when scene is resized
	void sceneResized();
	
	//! Set Navigator render hints
	/**
	 * @see http://doc.trolltech.com/4.3/qpainter.html#RenderHint-enum
	 */
	void setRenderHint(QPainter::RenderHint hints);
	
	//! Proxy for NavigatorView
	void catchFocusMove(int x, int y);
	//! 
	void catchZoomIn();
	//! 
	void catchZoomOut();
	
protected:
	//! React to widget resizing
	void resizeEvent(QResizeEvent *event);
	
	NavigatorLayout *layout_;
	
	bool delayed_;
};

#endif // Navigator_H
