#ifndef GAME_H
#define GAME_H



#include "Scene.hpp"
#include "RenderPoint.hpp"

class Hud;
class Renderer;
class Camera;
class Light;
class GameObject;



class Engine
{
	private: // data members
		Hud * hud;
		Renderer * renderer;
		Scene mScene;
		Camera * camera;
		Light * light;
		bool running;

	public: // functions
		Engine();
		virtual ~Engine();

		void build();
		bool run( Renderer* renderer );
		void stop();

	private:
		void control();
		bool draw( Renderer* renderer );
		void drawHud();
};

#endif // GAME_H
