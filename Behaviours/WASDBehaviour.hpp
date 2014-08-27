#ifndef WASDBEHAVIOUR_H
#define WASDBEHAVIOUR_H

//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
#include "../Behaviour.hpp"


class WASDBehaviour : public Behaviour
{
	private:
		//sf::Window * window;
		//sf::Texture aniText;
		//sf::Sprite aniSprite;

	public:
		//WASDBehaviour( GameObject * aParent, sf::Window * aWindow );
		WASDBehaviour(GameObject * aParent);
		virtual ~WASDBehaviour();

		virtual void update( float step );
};

#endif // WASDBEHAVIOUR_H
