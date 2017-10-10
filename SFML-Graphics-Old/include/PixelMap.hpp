#ifndef PIXELMAP_HPP
#define PIXELMAP_HPP

#include <SFML/Graphics.hpp>

class PixelMap : public sf::Drawable
{
	sf::Uint8 *pixelmap;
	sf::Color color;

	int width, height;

	sf::Image pixmapimg;
	sf::Texture texture;
	sf::Sprite sprite;

	virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const
	{
		target.draw( sprite, states );
	}

	void generatedefaultpixelmap()
	{
		for( int x = 0; x < width; ++x )
		{
			for( int y = 0; y < height; ++y )
			{
				// RGBA format
				pixelmap[ ( y * width + x ) * 4 + 0 ] = 0;
				pixelmap[ ( y * width + x ) * 4 + 1 ] = 0;
				pixelmap[ ( y * width + x ) * 4 + 2 ] = 0;
				pixelmap[ ( y * width + x ) * 4 + 3 ] = 255;
			}
		}
	}

	void create( int width, int height )
	{
		if( pixelmap != nullptr	)
			delete[] pixelmap;
		
		pixelmap = new sf::Uint8[ width * height * 4 ];

		this->width = width;
		this->height = height;

		color = sf::Color::White;

		this->generatedefaultpixelmap();

		pixmapimg.create( width, height, pixelmap );
		texture.loadFromImage( pixmapimg, sf::IntRect( 0, 0, width, height ) );
		sprite.setTexture( texture );
	}

public:

	PixelMap()
	{
		pixelmap = nullptr;
	}

	PixelMap( int width, int height )
	{
		pixelmap = nullptr;
		this->create( width, height );
	}

	~PixelMap()
	{
		delete[] pixelmap;
	}

	void init( int width, int height )
	{
		this->create( width, height );
	}

	void setcolor( sf::Color color )
	{
		this->color = color;
	}

	void putpixel( int pos_x, int pos_y )
	{
		if( pos_x >= width || pos_y >= height )
			return;

		pixelmap[ ( pos_y * width + pos_x ) * 4 + 0 ] = color.r;
		pixelmap[ ( pos_y * width + pos_x ) * 4 + 1 ] = color.g;
		pixelmap[ ( pos_y * width + pos_x ) * 4 + 2 ] = color.b;
		pixelmap[ ( pos_y * width + pos_x ) * 4 + 3 ] = color.a;

	}

	void updateimage()
	{
		pixmapimg.create( width, height, pixelmap );
		texture.loadFromImage( pixmapimg, sf::IntRect( 0, 0, width, height ) );
		sprite.setTexture( texture );
	}
};

#endif //PIXELMAP_HPP
