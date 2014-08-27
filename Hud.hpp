#ifndef HUD_H
#define HUD_H

class RenderPoint;

class Hud
{
	private:
		//sf::RenderWindow * window;
		//sf::Font font;
		//sf::Texture marvinTex;
		//sf::Sprite marvin;
	public:
		//Hud( sf::RenderWindow * aWindow );
		Hud( RenderPoint * renderer );
		virtual ~Hud( );
		void draw( );
};

#endif // HUD_H