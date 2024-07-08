#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "targets.h"
#include "menus.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Game
{
private:
	//Classes
	Targets targets;
	Menus menus;
	bool mouseHeld;

	//Variables
	std::string status; //playing, paused, lost, quit, main
	bool restartGame;

	//Window
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;
	float width_proportion;
	float height_proportion;

	//Audio
	sf::Music soundtrack;
	bool soundEnabled;

	//Time
	sf::Clock deltaClock;
	sf::Time deltaTime;

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	//Textures
	sf::Texture backgrround_texture;
	sf::Texture foreground_texture;
	sf::Texture crosshair_texture;
	sf::Texture heart_texture;
	sf::Texture key_texture;

	//Game objects
	sf::Sprite background;
	sf::Sprite foreground;
	sf::Sprite crosshair;



	//Interface
	sf::Font textFont1;
	sf::Font textFont2;
	sf::Text pointsText;
	sf::Text healthText;
	sf::Text reloadKeyText;
	sf::Sprite heart;
	sf::Sprite keySprite;
	sf::Text waveText;


	//Private functions
	void initVars();
	void initWindow();
	void initBackground();
	void initForeground();
	void initInterface();
	void initCrosshair();
	void initMusic();

public:
	//Constructors / Destructors
	Game(); 
	virtual ~Game();

	//Accesors
	const bool running() const;

	//Functions
	void updateDelta();
	void updateMouse();
	void updateInterface();
	void updateCrosshair();
	void updateStatus();
	void updateMusic();
	void update();

	void renderBackground();
	void renderForeground();
	void renderInterface();
	void renderCrosshair();
	void render();
};
