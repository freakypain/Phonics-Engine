#include "Time.hpp"
#include "Hud.hpp"
#include "Renderer.hpp"
#include "ShaderProgram.hpp"
#include "Engine.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"


// Behaviorus
#include "Behaviours\WASDBehaviour.hpp"
#include "Behaviours/WASDBehaviour.hpp"

// Colliders
#include "Colliders/SphereCollider.hpp"

// Lights
#include "Lights/Spotlight.hpp"

// External
#include <cassert>


Engine::Engine() : window(NULL), hud(NULL), renderer(NULL), scene(NULL), camera(NULL), light(NULL)
{
	//window = new sf::RenderWindow( sf::VideoMode( 800, 600, 32 ), "Santa smash"/*, sf::Style::Fullscreen*/); // get a window
	//std::cout << "Init Glew" << glewInit() << std::endl;

	//hud = new Hud( window );

	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	//renderer = new Renderer( window );
}

Engine::~Engine()
{
	//dtor
}

void Engine::build()
{
    // Shader List
	//ShaderProgram * shaderPoint = new ShaderProgram("shaders/pointlight.vert", "shaders/pointLight.frag");

	// Camera
	camera = new Camera( "Camera", glm::vec3( 30, 40, 25) );
    //camera->setBehaviour( new WASDBehaviour( camera, window ) );

	// Add to Universe
   // scene->add( camera );

}

void Engine::run()
{
	running = true;
	while ( running ) {
		Time::update();
		control();
		if ( running ) { // control may have changed running;
			update( Time::step() );
			draw();
		}
	}
}

void Engine::stop()
{
}

// private functions

void Engine::control()
{
	sf::Event event;
	while( window->pollEvent( event ) ) { // we must empty the event queue
		if ( event.type == sf::Event::Closed ) {
			window->close(); // oeps, still drawing after this one !!!!!!
			running = false; // running = false;
		}
	}
}


void Engine::update( float step )
{
	assert( scene != NULL );
	scene->update( step );
}

void Engine::draw()
{
	assert( window != NULL );
	assert( renderer != NULL );
	assert( scene != NULL );

	renderer->draw( scene );
	hud->draw();
	window->display(); // swap colorbuffer to screen
}
