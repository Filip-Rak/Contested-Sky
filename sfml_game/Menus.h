#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Menus
{
	
private:
	//private vars
	sf::Font font;
	bool refreshStats;

	//Pause Menu
	sf::RectangleShape pause_background;
	sf::Text pause_top_text;

	static const int pause_button_num = 3;
	sf::RectangleShape pause_buttons[pause_button_num];
	sf::Text pause_button_texts[pause_button_num];

	//Main menu
	sf::Texture main_background_texture;
	sf::Sprite main_background_sprite;

	sf::RectangleShape main_overlay;
	sf::Text title_text;
	
	static const int main_buttons_num = 3;
	sf::RectangleShape main_buttons[main_buttons_num];
	sf::Text main_buttons_texts[main_buttons_num];

	//Lost
	//sf::RectangleShape pause_background;
	sf::Text lost_text_top;
	sf::Text lost_stats;
	
	static const int lost_buttons_num = 2;
	sf::RectangleShape lost_buttons[lost_buttons_num];
	sf::Text lost_buttons_texts[lost_buttons_num];


	//private methods
	void initVariables();
	void initPause();
	void initMain();
	void initLost();


	void updatePause(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld, bool& soundEnabled);
	void updateMain(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld, bool& soundEnabled, bool& restartGame);
	void updateLost(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld);
	void updateTopScore(int score);
	void updateStats(int shots_fired, int shots_hit, int score);

	void renderPause(sf::RenderTarget& target);
	void renderMain(sf::RenderTarget& target);
	void renderLost(sf::RenderTarget& target);

public:
//Constructor / Destructor

	Menus();
	virtual ~Menus();

	//Variables
	int top_score;

	//Public methods
	void update(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld, bool& soundEnabled, bool& restartGame, int shots_fired, int shots_hit, int score);
	void render(sf::RenderTarget& target, std::string& status);
};

