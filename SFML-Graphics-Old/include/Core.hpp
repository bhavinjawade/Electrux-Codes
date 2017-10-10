#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include "PixelMap.hpp"

const static double PI = 3.14159;

class GraphicsEngine
{
	sf::RenderWindow window;
	sf::Event event;
	PixelMap pixmap;

	
	float getangle( int x1, int y1, int x2, int y2 )
	{
		return ( float )std::atan2(y2 - y1, x2 - x1);
	}

	int round( float num )
	{
		return ( num - ( int )num >= 0.5 ) ? num + 1 : num;
	}

	void pollevent()
	{
		while( window.pollEvent( event ) )
	       	{
		       	if( event.type == sf::Event::Closed )
			       	window.close();

       			if( event.type == sf::Event::KeyPressed &&
			    event.key.code == sf::Keyboard::Escape )
	       			window.close();
		}
	}
	
public:

	void initgraph( int width = 1280, int height = 720, std::string title = "SFML Default" )
	{
		window.create( sf::VideoMode( width, height ), title );
		pixmap.init( width, height );
	}

	void putpixel( int pos_x, int pos_y ) { pixmap.putpixel( pos_x, pos_y ); }

	void line( int x1, int y1, int x2, int y2 )
	{
		float angle = this->getangle( x1, y1, x2, y2 );

		float x_start = ( float ) x1;
		float y_start = ( float ) y1;

		float x_inc = std::cos( angle );
		float y_inc = std::sin( angle );

		while ( this->round( x_start ) != x2 || this->round( y_start ) != y2 ) {

			this->putpixel( ( int )x_start, ( int )y_start );

			x_start += x_inc;
			y_start += y_inc;

		}

		this->putpixel( x2, y2 );
	}

	void displaycirclepoints( int x_start,
				  int y_start,
				  int x,
				  int y,
				  int semicircle = -1 )
	{
		if ( semicircle == 1 || semicircle == -1 ) {
			this->putpixel( x_start + x, y_start + y );
			this->putpixel( x_start + x, y_start - y );
			this->putpixel( x_start + y, y_start + x );
			this->putpixel( x_start + y, y_start - x );
		}
		
		if ( semicircle == 0 || semicircle == -1 ) {
			this->putpixel( x_start - x, y_start + y );
			this->putpixel( x_start - x, y_start - y );
			this->putpixel( x_start - y, y_start + x );
			this->putpixel( x_start - y, y_start - x );
		}
	}

	void circle( int r,
		     int x_start,
		     int y_start,
		     int semicircle = -1 )
	{
		int x = r, y = 0,
			dx = 1, dy = 1,
			error = dx - r * 2;

		while ( x >= y ) {
			this->displaycirclepoints( x_start, y_start, x, y, semicircle );

			if ( error <= 0 ) {
				y++;
				error += dy;
				dy += 2;
			}

			if ( error > 0 ) {
				x--;
				dx += 2;
				error += dx - r * 2;
			}
		}
	}
	
	void setpixelcolor( sf::Color color )
	{
		pixmap.setcolor( color );
	}

	void closegraph()
	{
		pixmap.updateimage();
		
		while( window.isOpen() ) {
			this->pollevent();
			this->show();
		}
	}

	bool isopen()
	{
		return window.isOpen();
	}

	void show()
	{
		window.clear();
		window.draw( pixmap );
		window.display();
	}
};

#endif // CORE_HPP
