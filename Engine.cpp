// External
#include <iostream>
#include <memory>
#include <cassert>

#include "Time.hpp"
#include "Hud.hpp"
#include "Renderer.hpp"
#include "Engine.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Light.hpp"


// Behaviorus
#include "Behaviours\WASDBehaviour.hpp"
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





Engine::Engine() : hud(0), renderer(0), camera(0), light(0)
{
	//window = new sf::RenderWindow( sf::VideoMode( 800, 600, 32 ), "Santa smash"/*, sf::Style::Fullscreen*/); // get a window
	//std::cout << "Init Glew" << glewInit() << std::endl;

	//hud = new Hud( window );

	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	//renderer = new Renderer( window );
	
	//scene = new Scene("World");
	Scene mScene("World");
}

Engine::~Engine()
{
	//dtor
}

void Engine::build()
{
	// Create floor
	//GameObject * floor = new GameObject( "Floor", glm::vec3( 0, 1, 0 ) );
	//floor->setPrimitive( new Plane ( Material( Colour( 0.0f, 0.0f, 0.2f ), 1.0f, 1.0f, 0.2f ), Vector3( 0, 1, 0 ), 2.0f, false ) );
	//mScene.add(floor);


	//floor.setPrimitive(new Plane(Material(Colour(0.0f, 0.0f, 0.2f), 1.0f, 1.0f, 0.2f), Vector3(0, 1, 0), 2.0f, false));
	//mScene.add(floor);
	
	std::shared_ptr<GameObject> floor(new GameObject("Test", glm::vec3(-8.0f, 3.0f, 8.0f)));
	floor->setPrimitive(new Plane(Material(Colour(0.0f, 0.0f, 0.2f), 1.0f, 1.0f, 0.2f), Vector3(0, 1, 0), 2.0f, false));
	mScene.add(*floor);


	// Create spehere
	GameObject * ball = new GameObject( "Ball", glm::vec3( -8.0f, 3.0f, 8.0f ) );	
	ball->setPrimitive( new Sphere( Material( Colour( 1.0f, 3.0f, 0.1f), 0.2f, 0.0f, 1.0f ), Vector3( -8.0f, 3.0f, 8.0f ), 1.0f, true ) );
	mScene.add(ball);

	// Create Light.
	GameObject * pointLight = new GameObject("pointLight", glm::vec3(5.0f, 25.0f, 0.0f));
	pointLight->setLight( new PointLight(Colour(1.0f, 1.2f, 3.0f), Vector3(5.0f, 25.0f, 0.0f)));
	mScene.add(pointLight);


	// Top light
	//mLights.push_back( new PointLight( Colour( 1.0f, 1.2f, 3.0f ), Vector3( 5.0f, 25.0f, 0.0f ) ) );


	// Floor Plane
	//mPrimitives.push_back(new Plane(Material(Colour(0.0f, 0.0f, 0.2f), 1.0f, 1.0f, 0.2f), Vector3(0, 1, 0), 2.0f, false));

	// Blue sphere
	//mPrimitives.push_back(new Sphere(Material(Colour(255.0f, 0.0f, 238.1f), 0.6f, 0.0f, 1.0f), Vector3(2.0f, 3.0f, 4.0f), 1.0f, true));
	//mPrimitives.push_back(new Sphere(Material(Colour(1.0f, 3.0f, 0.1f), 0.2f, 0.0f, 1.0f), Vector3(-8.0f, 3.0f, 8.0f), 1.0f, true));
	//mPrimitives.push_back(new Sphere(Material(Colour(0.0f, 0.0f, 0.1f), 0.2f, 1.0f, 1.0f), Vector3(-3.0f, 3.0f, 15.0f), 4.0f, true));
	//mPrimitives.push_back(new Sphere(Material(Colour(1.0f, 1.0f, 0.1f), 0.2f, 0.0f, 1.0f), Vector3(6.0f, 3.0f, 1.0f), 1.0f, true));

	// Mirror sphere
	//	mPrimitives.push_back(new Sphere(Material(Colour( 0.0f, 0.0f, 1.0f ), 0.2f, 1.0f, 0.0f), Vector3(-7.5f, 2.0f, 5.0f), 3.0f, true));


	//ball->setme

	//std::unique_ptr<Primitive> ball(new Sphere(Material(Colour(1.0f, 3.0f, 0.1f), 0.2f, 0.0f, 1.0f), Vector3(-8.0f, 3.0f, 8.0f), 1.0f, true));
	//scene->add
	// Mirror sphere
	//	mPrimitives.push_back(new Sphere(Material(Colour( 0.0f, 0.0f, 1.0f ), 0.2f, 1.0f, 0.0f), Vector3(-7.5f, 2.0f, 5.0f), 3.0f, true));



    // Shader List
	//ShaderProgram * shaderPoint = new ShaderProgram("shaders/pointlight.vert", "shaders/pointLight.frag");

	// Add Plane to the world
	//GameObject *  ground = new GameObject( "Ground", glm::vec3( 0, 1, 0 ) );
	//ground->setMesh( Mesh::load( "models/floor.obj" ) );
	//ground->setTexture( Texture::load( "test.png" ) );

	// Camera
	// TODO fix camera to unique pointer
	//std::unique_ptr<Camera> camera("Camera", glm::vec3(30, 40, 25));
	//camera = new Camera( "Camera", glm::vec3( 30, 40, 25) );
    //camera->setBehaviour( new WASDBehaviour( camera ) );
		

	// Add to Universe
	//scene.add(camera);
  //  scene->add( camera );

	// Prepare Universe
	mScene.prepare();

}

bool Engine::run( Renderer* renderer )
{
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
