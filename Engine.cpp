// External
#include <iostream>
#include <memory>
#include <cassert>

// Includes
#include "Hud.hpp"
#include "Renderer.hpp"
#include "Engine.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"

// Behaviour
#include "Behaviours/WASDBehaviour.hpp"

// Colliders
#include "Colliders/SphereCollider.hpp"

// Lights
#include "Light.hpp"
#include "Lights\PointLight.hpp"
#include "Lights/Spotlight.hpp"

// Primitives
#include "Primitive.hpp"
#include "Primitives\Sphere.hpp"
#include "Primitives\Plane.hpp"





Engine::Engine() : hud(0), renderer(nullptr), camera(nullptr), light(nullptr)
{
	//window = new sf::RenderWindow( sf::VideoMode( 800, 600, 32 ), "Santa smash"/*, sf::Style::Fullscreen*/); // get a window
	//std::cout << "Init Glew" << glewInit() << std::endl;

	//hud = new Hud( window );

	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	//renderer = new Renderer( window );
	
	//scene = new Scene("World");

	// Set timer
	Time mTime;

	// Set Scebe
	Scene mScene("World");
}

Engine::~Engine()
{
	//dtor
}

void Engine::build()
{
	// Create floor
	std::unique_ptr<GameObject> floor(new GameObject("Floor", Vector3(-8.0f, 3.0f, 8.0f)));
	floor->setPrimitive(new Plane(Material(Colour(0.0f, 0.0f, 0.2f), 1.0f, 1.0f, 0.2f), Vector3(0, 1, 0), 2.0f, false));
	mScene.add(floor.get());


	// Create spehere
	std::unique_ptr<GameObject> ball(new GameObject("Ball", Vector3(-8.0f, 3.0f, 8.0f)));
	ball->setPrimitive( new Sphere( Material( Colour( 1.0f, 3.0f, 0.1f), 0.2f, 0.0f, 1.0f ), Vector3( -8.0f, 3.0f, 8.0f ), 1.0f, true ) );
	mScene.add(ball.get());

	// Create Light
	std::unique_ptr<GameObject> pointLight(new GameObject("pointLight", Vector3(5.0f, 25.0f, 0.0f)));
	pointLight->setLight( new PointLight(Colour(1.0f, 1.2f, 3.0f), Vector3(5.0f, 25.0f, 0.0f)));
	mScene.add(pointLight.get());

	// Camera
	// TODO fix camera to unique pointer
	//std::unique_ptr<Camera> camera("Camera", glm::vec3(30, 40, 25));
	//camera = new Camera( "Camera", glm::vec3( 30, 40, 25) );
    //camera->setBehaviour( new WASDBehaviour( camera ) );
		

	// Prepare Universe
	mScene.prepare();

}

bool Engine::run( Renderer* renderer )
{
	// Update Timer
	mTime.update();

	// Update Scene
	mScene.update( mTime.getStep() ); // Update Scene every frame

	// Render scene
	return draw( renderer ); 
}

void Engine::stop()
{

}


bool Engine::draw( Renderer* renderer )
{

	// Start Rendering
	bool draw = renderer->draw( mScene );

	//assert( window != 0 );
	//assert( renderer != 0 );
	//assert( scene != 0 );

	//renderer->draw( scene );
	//hud->draw();

	// TODO Fix window display renderer 
	//window->display(); // swap colorbuffer to screen

	return draw;
}
