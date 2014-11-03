#ifndef HUD_H
#define HUD_H

class RenderPoint;

class Hud
{
	public:
		Hud( RenderPoint * renderer );
		virtual ~Hud( );
		void draw( );
};

#endif // HUD_H