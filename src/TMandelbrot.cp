/***** * TMandelbrot.cp * *		The window methods to draw a Mandelbrot set * *****/#include <Packages.h>			// for NumToString prototype#include "TFractalViewerWindow.h"#include "TMandelbrot.h"#include <stdlib.h>/**** *	TFractalViewerWindow constructor * *		Create a bullseye window. This constructor relies *		on the TWindow constructor to place the window in *		in attractive place. Then it appends a number to the *		window title. * ****/TMandelbrot::TMandelbrot(void){		//	Set the width, and show the window.	PrepareStyles();	SetStyle(1);	SetDrawMode(2);		// Set the default plane	DefaultPlane();		Show();}/**** * Hit * *		Handle a mouse down in the window. *		Bullseye window just force a refresh. * ****/void TMandelbrot::DefaultPlane(){	pWidth = 3.0;	pHeigth = 3.0;	pCX = -0.6;	pCY = 0.0;}void TMandelbrot::Hit(Point where){	Point 	mouse;	double	sCX, sCY, tX, tY, hX, hY;	Rect	drawingRect;	// Recalculate center	GlobalToLocal(&where);	hX = where.h; // - sLeft;	hY = where.v; // - sTop;		sCX = sWidth / 2.0;	sCY = sHeigth / 2.0;	tX = sCX - hX;	tY = hY - sCY;	pCX = pCX - pWidth * tX / (double)sWidth;		pCY = pCY - pHeigth * tY / (double)sHeigth;	RefreshWindow(false);		// preserve the scroll bars}/**** * DrawShape methods * *		These are the DrawShape methods for *			TBullWindow:	does nothing *			TCircleBull:	Circles *			TSquareBull:	Squares *			TPlasma:	"Triangles" * *		All the DrawShape methods take a drawingRect *		as a parameter. The pen width *		is already set to the appropriate width. * ****/int TMandelbrot::Mandelbrot(double real, double imag, short maxiterations) {	double zReal = real;	double zImag = imag;		for (int i = 0; i < maxiterations; ++i) {		double r2 = zReal * zReal;		double i2 = zImag * zImag;		if (r2 + i2 > 8.0)			return i;		zImag = 2.0 * zReal * zImag + imag;		zReal = r2 - i2 + real;	}	return maxiterations;}void TMandelbrot::DrawShape(Rect *drawingRect){	RGBColor colPix;	short maxiterations;		switch (drawMode) {	case 1:		maxiterations = 20;		break;	case 2:		maxiterations = 100;		break;	case 3:		maxiterations = 200;		break;	}		short st = GetStyle() - 1;	sWidth = drawingRect->right - drawingRect->left + 1;	sHeigth = drawingRect->bottom - drawingRect->top + 1;		pHeigth = (double)sHeigth * pWidth / (double)sWidth;	double x_start = pCX - pWidth / 2.0;	double x_fin = x_start + pWidth;	double y_start = pCY - pHeigth / 2.0;	double y_fin = y_start + pHeigth;		double dx = (x_fin - x_start)/(sWidth - 1);	double dy = (y_fin - y_start)/(sHeigth - 1);	for (int i = 0; i < sHeigth; i++) {		for (int j = 0; j < sWidth; j++) {			double x = x_start + j*dx; // current real value			double y = y_fin - i*dy; // current imaginary value						int value = Mandelbrot(x, y, maxiterations);			if (value == maxiterations) {				colPix.red = 0;				colPix.green = 0;				colPix.blue = 0;			}			else {				value = 255 * value / maxiterations;				colPix = spec[st][value % 255];			}			SetCPixel(j, i, &colPix);		}	}}//// PREPARE STYLES METHODS//void TMandelbrot::PrepareStyles(){	short ci;	// Style 1	for(ci=0; ci < 256; ci++) {		spec[0][ci].red = 65536 - ci * 256;		spec[0][ci].green = 65536 - ci * 256;		spec[0][ci].blue = 65536 - ci * 256;	}	// Style 2	for(ci=0; ci < 256; ci++) {		spec[1][ci].red = ci * 256;		spec[1][ci].green = ci * 256;		spec[1][ci].blue = ci * 256;	}	// Style 2	for(ci=0; ci < 256; ci++) {		spec[2][ci].red = 65535 - ci * 256;		spec[2][ci].green = 32768 + ci * 128;		spec[2][ci].blue = ci * 256;	}	// Style 2	for(ci=0; ci < 256; ci++) {		spec[3][ci].red = ci * 256;		spec[3][ci].green = 32768 + ci * 128;		spec[3][ci].blue = 65535 - ci * 256;	}	// Style 2	for(ci=0; ci < 256; ci++) {		spec[4][ci].red = 32768 - ci * 128;		spec[4][ci].green = ci * 256;		spec[4][ci].blue = 65535 - ci * 256;	}}//// ZOOM CONTENT//void TMandelbrot::ZoomContent(short z){			switch (z) {		case -1:			pWidth = pWidth * 1.333;			pHeigth = pHeigth * 1.333;			break;		case 1:			pWidth = pWidth * 0.666;			pHeigth = pHeigth * 0.666;			break;			break;		default:			DefaultPlane();			break;	}	RefreshWindow(false);		// preserve the scroll bars}