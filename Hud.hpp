#ifndef HUD_H
#define HUD_H

class RenderPoint;

class Hud
{
	public:
		Hud( );
		virtual ~Hud( );
		void draw( );
		void set2D();
};

#endif // HUD_H