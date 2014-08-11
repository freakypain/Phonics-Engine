#ifndef GAME_H
#define GAME_H

class Hud;
class Renderer;
class Scene;
class Camera;
class Light;
class GameObject;


class Engine
{
	private: // data members
		Hud * hud;
		Renderer * renderer;
		Scene * scene;
		Camera * camera;
		Light * light;
		bool running;

	public: // functions
		Engine();
		virtual ~Engine();

		void build();
		void run();
		void stop();

	private:
		void control();
		void update( float step );
		void draw();
		void drawHud();
};

#endif // GAME_H
