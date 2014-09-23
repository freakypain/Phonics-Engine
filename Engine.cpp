// External
#include <iostream>
#include <memory>
#include <cassert>

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




Engine::Engine() : hud(0), renderer(0), camera(0), light(0)
{
	//window = new sf::RenderWindow( sf::VideoMode( 800, 600, 32 ), "Santa smash"/*, sf::Style::Fullscreen*/); // get a window
	//std::cout << "Init Glew" << glewInit() << std::endl;

	//hud = new Hud( window );

	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	//renderer = new Renderer( window );
	
	//scene = new Scene("World");
}

Engine::~Engine()
{
	//dtor
}

void Engine::build()
{
    // Shader List
	//ShaderProgram * shaderPoint = new ShaderProgram("shaders/pointlight.vert", "shaders/pointLight.frag");

	// Add Plane to the world
	GameObject *  ground = new GameObject( "Ground", glm::vec3( 0, 1, 0 ) );
	//ground->setMesh( Mesh::load( "models/floor.obj" ) );
	//ground->setTexture( Texture::load( "test.png" ) );

	// Camera
	// TODO fix camera to unique pointer
	//std::unique_ptr<Camera> camera("Camera", glm::vec3(30, 40, 25));
	camera = new Camera( "Camera", glm::vec3( 30, 40, 25) );
    //camera->setBehaviour( new WASDBehaviour( camera, window ) );

	

	// Add to Universe
	scene.add(camera);
  //  scene->add( camera );

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
// TODO Fix control
void Engine::control()
{

}
/*
void Engine::control()
{
	sf::Event event;
	while( window->pollEvent( event ) ) { // we must empty the event queue
		if ( event.type == sf::Event::Closed ) {
			window->close(); // oeps, still drawing after this one !!!!!!
			running = false; // running = false;
		}
	}
}*/


void Engine::update( float step )
{
	//scene->update( step );
	scene.update( step );
}

void Engine::draw()
{
	//assert( window != 0 );
	assert( renderer != 0 );
	//assert( scene != 0 );

	//renderer->draw( scene );
	hud->draw();

	// TODO Fix window display renderer 
	//window->display(); // swap colorbuffer to screen
}
