/*
 * main.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: Daniel G Billings Jr
 */


#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <random>
#include <SFML/Audio.hpp>
#include "LayerManager.hpp"
#include "Sprite.hpp"
#include "DrawManager.hpp"
#include "CrunchyBoxDraw.hpp"
#include "VectIndexMap.hpp"
#include "ASManager.hpp"

void CreateGround(b2World& World, float X, float Y);
void CreateBox(b2World& World, int MouseX, int MouseY); // Spawns a box at MouseX, MouseY

crunch::LayerManager layers;
crunch::DrawManager drawManager;
crunch::drawObjects objects;
crunch::VectIndexMap<sf::Texture> textures;

const float SCALE = 30.0f;
bool stop = false;
int main(int argc, char *argv[])
{
	for(int i = 0;i < argc;i++)
	{
		std::cout << argv[i] << "\n";
	}
	std::cout << "Arguments are only echoed back at this time\n";
	bool running = true;

	sf::RenderWindow window(sf::VideoMode(1024,768), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	crunch::ASManager manager;
	manager.buildScripts();
	manager.changeFunc("void main()");
	/**** BOX2D STUFF*******/
	/** Prepare the world */
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);
	crunch::CrunchyBoxDraw crunchyDraw(window, SCALE);
	CreateGround(World, 400.f, 500.f);
	window.setFramerateLimit(60);	//< This is SFML, but limiting to 60 frames is just for Box2D, will have better timing solution later
	World.SetDebugDraw(&crunchyDraw);
	//crunchyDraw.SetFlags( b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	/**** END BOX2D*****///TODO: (create bindings for shit for angelscript later)
	while(running)
	{
		sf::Event event;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int mouseX = sf::Mouse::getPosition(window).x;
			int mouseY = sf::Mouse::getPosition(window).y;
			CreateBox(World, mouseX, mouseY);
		}
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				running = false;
		}
		/***** BOX2D *****/
		World.Step(1/60.f, 8, 3);
		/***** END BOX2D *****/
		manager.runScript();
		window.clear();
		window.draw(shape);
		layers.queue(drawManager);
		drawManager.draw(window, objects, sf::RenderStates::Default, SCALE);
		/***** BOX2D *****/
		World.DrawDebugData();//box2Ddebug drawing
		/**** END BOX2D ****/

		window.display();
		std::cout << World.GetBodyCount() << "\n";

	}
	window.close();
	return(0);
}

void CreateGround(b2World& world, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;  // Sets the density of the body
    FixtureDef.shape = &Shape; // Sets the shape
    Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}

void CreateBox(b2World& world, int mouseX, int mouseY)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	b2CircleShape circleShape;
	b2Body* body;
	static int32_t count = 0;

	count--;
	stop = true;
	bodyDef.position = b2Vec2(mouseX/SCALE, mouseY/SCALE);
	bodyDef.angle = 45.0f*3.14/180;
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);

	shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
	circleShape.m_radius = (32.f/2)/SCALE;
	fixtureDef.density = 5.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);
	body->ApplyTorque(200.f, true);

	crunch::Sprite tempSprite;
	sf::Texture tempTexture;


	crunch::virtualIndex_t textureIndex = textures.newItem(tempTexture);
	textures[textureIndex].loadFromFile("crate2.png");
	textures[textureIndex].setSmooth(true);
	crunch::virtualIndex_t spriteIndex = objects.sprites.newItem(tempSprite);
	objects.sprites[spriteIndex].setPhysicsObj(body);
	objects.sprites[spriteIndex].setTexture(textures[textureIndex]);
	objects.sprites[spriteIndex].setScale(32.0f/16.0f, 32.0f/16.0f);
	objects.sprites[spriteIndex].setTextureRect(512-16, 512-16, 16, 16);
	layers.addSpriteToLayer(count, spriteIndex);
}
