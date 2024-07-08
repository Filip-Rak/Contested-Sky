#include "Menus.h"

//constructor / destructor
Menus::Menus()
{
	this->initVariables();
	this->initPause();
	this->initMain();
	this->initLost();
}

Menus::~Menus()
{
}

void Menus::initVariables()
{
	//top_score
	std::fstream file("save.txt", std::ios::in);
	std::string score;
	if (std::getline(file, score))
		this->top_score = std::stoi(score);
	else
		this->top_score = 0;

	file.close();

	//font
	this->font.loadFromFile("assets/fonts/nulshock_bd.otf");

	//stats
	this->refreshStats = true;
}

//private methods
void Menus::initPause()
{
	//background
	float screen_y = sf::VideoMode::getDesktopMode().height;
	float screen_x = sf::VideoMode::getDesktopMode().width;
	this->pause_background.setSize(sf::Vector2f(screen_x / 1.5f, screen_y / 1));
	this->pause_background.setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
	this->pause_background.setOutlineColor(sf::Color(0.f, 0.f, 0.f, 255.f));
	this->pause_background.setOutlineThickness(1.f);

	this->pause_background.setPosition((screen_x - this->pause_background.getSize().x) / 2.f, (screen_y - this->pause_background.getSize().y) / 2.f);

	//"Paused" text
	this->pause_top_text.setFont(this->font);
	this->pause_top_text.setCharacterSize(80.f);
	this->pause_top_text.setString("Game is paused");
	this->pause_top_text.setFillColor(sf::Color::White);

	this->pause_top_text.setPosition(525.f, 85.f);

	std::string texts[this->pause_button_num] = { "Continue", "Enable music", "Main menu"};
	//Buttons and text
	for (int i = 0; i < this->pause_button_num; i++)
	{
		this->pause_buttons[i].setSize(sf::Vector2f(600.f, 150.f));
		this->pause_buttons[i].setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
		//this->pause_buttons[i].setOutlineColor(sf::Color(0.f, 0.f, 0.f, 255.f));
		this->pause_buttons[i].setOutlineThickness(1.f);

		this->pause_buttons[i].setPosition((screen_x - this->pause_buttons[i].getSize().x) / 2.f, (screen_y - this->pause_buttons[i].getSize().y) / 2.f - 200.f + 100.f * (i + 1) + this->pause_buttons[i].getSize().y * i);


		//Texts
		this->pause_button_texts[i].setFont(this->font);
		this->pause_button_texts[i].setCharacterSize(50.f);
		this->pause_button_texts[i].setFillColor(sf::Color::White);
		this->pause_button_texts[i].setString(texts[i]);

		this->pause_button_texts[i].setPosition(this->pause_buttons[i].getPosition().x + 20.f, this->pause_buttons[i].getPosition().y + 30.f);
	}
}

void Menus::initMain()
{
	float offset_left = 100.f;
	float offset_top = 200.f;

	//background
	this->main_background_texture.loadFromFile("assets/menus/main_background.png");
	this->main_background_sprite.setTexture(this->main_background_texture);
	this->main_background_sprite.setPosition(0.f, 0.f);

	//overlay
	this->main_overlay.setSize(sf::Vector2f(700.f, 1080.f));
	this->main_overlay.setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
	this->main_overlay.setOutlineColor(sf::Color(0.f, 0.f, 0.f, 255.f));
	this->main_overlay.setOutlineThickness(1.f);

	this->main_overlay.setPosition(1920 - main_overlay.getSize().x - offset_left, 0.f);


	//Title text
	this->title_text.setFont(this->font);
	this->title_text.setCharacterSize(60.f);
	this->title_text.setString("Contested\nSky");

	this->title_text.setPosition(main_overlay.getPosition().x + 100.f, 50.f);


	//buttons and text
	std::string texts[this->main_buttons_num] = {"Start game", "Enable music", "Quit"};

	for (int i = 0; i < this->main_buttons_num; i++)
	{
		//buttons
		this->main_buttons[i].setSize(sf::Vector2f(600.f, 150.f));
		this->main_buttons[i].setFillColor(sf::Color::Red);
		this->main_buttons[i].setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
		this->main_buttons[i].setOutlineColor(sf::Color(255.f, 255.f, 255.f, 255.f));
		this->main_buttons[i].setOutlineThickness(1.f);

		this->main_buttons[i].setPosition(this->main_overlay.getPosition().x + (this->main_overlay.getSize().x - this->main_buttons[i].getSize().x) / 2.f, offset_top + 100.f * (i + 1) + (this->main_buttons[i].getSize().y) * i);
		

		//Texts
		this->main_buttons_texts[i].setFont(this->font);
		this->main_buttons_texts[i].setCharacterSize(50.f);
		this->main_buttons_texts[i].setFillColor(sf::Color::White);
		this->main_buttons_texts[i].setString(texts[i]);

		this->main_buttons_texts[i].setPosition(this->main_buttons[i].getPosition().x + 20.f, this->main_buttons[i].getPosition().y + 30.f);
	}

}

void Menus::initLost()
{
	//Top text
	this->lost_text_top.setFont(this->font);
	this->lost_text_top.setCharacterSize(100.f);
	this->lost_text_top.setString("Defeated");
	this->lost_text_top.setFillColor(sf::Color::White);

	this->lost_text_top.setPosition(625.f, 50.f);

	//stats
	this->lost_stats.setFont(this->font);
	this->lost_stats.setCharacterSize(35.f);
	this->lost_stats.setFillColor(sf::Color::White);
	this->lost_stats.setString("Shots fired: x\nShots hit: x\nHit precentage: x%");

	this->lost_stats.setPosition(665.f, 300.f);

	//buttons and texts
	std::string texts[this->lost_buttons_num] = { "Main menu", "Quit" };

	for (int i = 0; i < this->lost_buttons_num; i++)
	{
		this->lost_buttons[i].setSize(sf::Vector2f(600.f, 150.f));
		this->lost_buttons[i].setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
		this->lost_buttons[i].setOutlineColor(sf::Color::White);
		this->lost_buttons[i].setOutlineThickness(1.f);

		this->lost_buttons[i].setPosition(this->pause_buttons[i].getPosition().x, this->pause_buttons[i].getPosition().y + 250.f);


		//texts
		this->lost_buttons_texts[i].setFont(this->font);
		this->lost_buttons_texts[i].setCharacterSize(55.f);
		this->lost_buttons_texts[i].setFillColor(sf::Color::White);
		this->lost_buttons_texts[i].setString(texts[i]);

		this->lost_buttons_texts[i].setPosition(this->lost_buttons[i].getPosition().x + 20.f, this->lost_buttons[i].getPosition().y + 30.f);
	}
}


void Menus::updatePause(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld, bool& soundEnabled)
{
	//set strings
	if (soundEnabled)
		this->pause_button_texts[1].setString("Disable music");
	else
		this->pause_button_texts[1].setString("Enable music");

	for (int i = 0; i < this->pause_button_num; i++)
	{
		if (this->pause_buttons[i].getGlobalBounds().contains(mousePosView))
		{
			this->pause_buttons[i].setFillColor(sf::Color::White);
			this->pause_button_texts[i].setFillColor(sf::Color::Black);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!mouseHeld)
				{
					mouseHeld = true;
					switch (i)
					{
					case 0:
						//resumed game
						status = "playing";
						break;
					case 1:
						if (this->pause_button_texts[i].getString()[0] == 'D')
						{
							//disable music;
							soundEnabled = false;
							this->pause_button_texts[i].setString("Enable music");
							break;
						}
						else
						{
							//enable music;
							soundEnabled = true;
							this->pause_button_texts[i].setString("Disable music");
							break;
						}
						
					case 2:
						status = "main";
						break;
					}
				}
			}
			else
				mouseHeld = false;
		}
		else
		{
			this->pause_buttons[i].setFillColor(sf::Color::Black);
			this->pause_button_texts[i].setFillColor(sf::Color::White);
		}
	}
}

void Menus::updateMain(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld, bool& soundEnabled, bool &restartGame)
{
	//set strings
	if(soundEnabled)
		this->main_buttons_texts[1].setString("Disable music");
	else
		this->main_buttons_texts[1].setString("Enable music");


	for (int i = 0; i < this->main_buttons_num; i++)
	{
		if (this->main_buttons[i].getGlobalBounds().contains(mousePosView))
		{
			this->main_buttons[i].setFillColor(sf::Color::White);
			this->main_buttons_texts[i].setFillColor(sf::Color::Black);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!mouseHeld)
				{
					mouseHeld = true;
					switch (i)
					{
					case 0:
						//resumed game
						status = "playing";
						restartGame = true;
						break;
					case 1:
						if (this->main_buttons_texts[i].getString()[0] == 'D')
						{
							//disable music;
							soundEnabled = false;
							break;
						}
						else
						{
							//enable music;
							soundEnabled = true;
							break;
						}

					case 2:
						status = "quit";
						break;
					}
				}
			}
			else
				mouseHeld = false;
		}
		else
		{
			this->main_buttons[i].setFillColor(sf::Color::Black);
			this->main_buttons_texts[i].setFillColor(sf::Color::White);
		}
	}
}

void Menus::updateStats(int shots_fired, int shots_hit, int score)
{
	if (this->refreshStats)
	{
		this->refreshStats = false;

		//update stats
		float hitPrecentage;
		if (shots_hit != 0)
		{
			hitPrecentage = (float(shots_hit) / float(shots_fired)) * 100;
			hitPrecentage = std::round(hitPrecentage);
		}
		else
			hitPrecentage = 0;

		std::string statsString = "Shots fired:\t\t\t\t" + std::to_string(shots_fired);
		statsString += "\nShots hit:\t\t\t\t\t" + std::to_string(shots_hit);
		statsString += "\nHit precentage:      \t" + std::to_string(int(hitPrecentage));

		//update top score
		if (score > this->top_score)
		{
			statsString += "\nPrevious top score:   " + std::to_string(this->top_score);
			updateTopScore(score);
		}
		else
			statsString += "\nCurrent top score:   " + std::to_string(this->top_score);

		this->lost_stats.setString(statsString);
	}
}

void Menus::updateLost(sf::Vector2f mousePosView, std::string& status, bool& mouseHeld)
{
	//Ui update
	for (int i = 0; i < this->lost_buttons_num; i++)
	{
		if (this->lost_buttons[i].getGlobalBounds().contains(mousePosView))
		{
			this->lost_buttons[i].setFillColor(sf::Color::White);
			this->lost_buttons_texts[i].setFillColor(sf::Color::Black);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!mouseHeld)
				{
					mouseHeld = true;
					switch (i)
					{
					case 0:
						//main menu
						status = "main";
						break;
					case 1:
						//quit game
						status = "quit";
						break;
					}
				}
			}
			else
				mouseHeld = false;
		}
		else
		{
			this->lost_buttons[i].setFillColor(sf::Color::Black);
			this->lost_buttons_texts[i].setFillColor(sf::Color::White);
		}
	}
}

void Menus::updateTopScore(int score)
{
	//update in file
	std::fstream file("save.txt", std::ios::out);
	file << score;
	file.close();

	//update in memory
	this->top_score = score;
}

//public methods
void Menus::update(sf::Vector2f mousePosView, std::string &status, bool &mouseHeld, bool &soundEnabled, bool &restartGame, int shots_fired, int shots_hit, int score)
{
	if (status != "lost")
		this->refreshStats = true;

	//menus
	if (status == "paused")
		this->updatePause(mousePosView, status, mouseHeld, soundEnabled);
	else if (status == "main")
		this->updateMain(mousePosView, status, mouseHeld, soundEnabled, restartGame);
	else if (status == "lost")
	{
		this->updateStats(shots_fired, shots_hit, score);
		this->updateLost(mousePosView, status, mouseHeld);
	}
}

void Menus::renderPause(sf::RenderTarget& target)
{
	target.draw(this->pause_background);
	target.draw(this->pause_top_text);
	
	for (int i = 0; i < this->pause_button_num; i++)
	{
		target.draw(this->pause_buttons[i]);
		target.draw(this->pause_button_texts[i]);
	}
}

void Menus::renderMain(sf::RenderTarget& target)
{
	target.draw(this->main_background_sprite);
	target.draw(this->main_overlay);
	target.draw(this->title_text);

	for (int i = 0; i < this->main_buttons_num; i++)
	{
		target.draw(this->main_buttons[i]);
		target.draw(this->main_buttons_texts[i]);
	}
}
void Menus::renderLost(sf::RenderTarget& target)
{
	target.draw(this->pause_background);
	target.draw(this->lost_text_top);
	target.draw(this->lost_stats);

	for (int i = 0; i < this->lost_buttons_num; i++)
	{
		target.draw(this->lost_buttons[i]);
		target.draw(this->lost_buttons_texts[i]);
	}
}

void Menus::render(sf::RenderTarget& target, std::string& status)
{
	if (status == "paused")
		this->renderPause(target);
	else if (status == "main")
		this->renderMain(target);
	else if (status == "lost")
		this->renderLost(target);
}
