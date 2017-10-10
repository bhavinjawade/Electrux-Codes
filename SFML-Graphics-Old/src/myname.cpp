#include "../include/Core.hpp"

void C ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width / 2, y, x + width, y );
	core.line( x + width / 2, y + width, x + width, y + width );
	core.circle( width / 2, x + width / 2, y + width / 2, 0);
}

void H ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );
	core.line( x + width, y, x + width, y + width );
	core.line( x, y + width / 2, x + width, y + width / 2 );
}

void I ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width, y );
	core.line( x, y + width, x + width, y + width );
	core.line( x + width / 2, y, x + width / 2, y + width );
}

void R ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );
	core.line( x, y + width / 2, x + 0.90 * width, y + width );

	// For the upper curved part of R.
	core.line( x, y, x + 0.55 * width, y );
	core.line( x, y + width / 2, x + 0.55 * width, y + width / 2 );
	core.circle( width / 4, x + 0.55 * width, y + width / 4, 1 );
}

void A ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y + width, x + width / 2, y );
	core.line( x + width / 2, y, x + width, y + width );
	core.line( x + 0.25 * width, y + width / 2, x + 0.75 * width, y + width / 2 );
}

void G ( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width / 2, y, x + width, y );
	core.line( x + width / 2, y + width, x + width, y + width );
	core.line( x + width, y + width / 2, x + width, y + width );
	core.line( x + width / 2, y + width / 2, x + width, y + width / 2 );

	core.circle( width / 2, x + width / 2, y + width / 2, 0 );
}

int main()
{
	const int width = 100,
		gap = 30;
	
	GraphicsEngine core;

	core.initgraph();

	int x = 100, y = 100;

	int i = 0;
	int chardist = width + gap;
	
	C( core, x + i++ * chardist, y, width );
	H( core, x + i++ * chardist, y, width );
	I( core, x + i++ * chardist, y, width );
	R( core, x + i++ * chardist, y, width );
	A( core, x + i++ * chardist, y, width );
	G( core, x + i++ * chardist, y, width );

	core.closegraph();

	return 0;
}
