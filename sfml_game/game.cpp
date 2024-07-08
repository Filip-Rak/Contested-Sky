#include "game.h"


//Constructor / Destructor
Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initBackground();
	this->initForeground();
	this->initInterface();
	this->initCrosshair();
	this->initMusic();
}

Game::~Game()
{
	delete this->window;
}



//private functions
void Game::initVars()
{
	this->window = nullptr; 
	this->status = "main";
	this->restartGame = false;
}

void Game::updateStatus()
{
	if (this->status == "quit")
		this->window->close();

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				if (this->status == "paused")
					this->status = "playing";
				else if(this->status == "playing")
					this->status = "paused";
			}
			else if (ev.key.code == sf::Keyboard::LControl)
				this->window->close();
			break;
		}
	}
}


void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "Contested Sky", sf::Style::Fullscreen);
	this->window->setMouseCursorVisible(false);

	this->width_proportion = this->videoMode.getDesktopMode().width / 1920.f;
	this->height_proportion = this->videoMode.getDesktopMode().height / 1080.f;
}


void Game::initForeground()
{
	//properties
	this->foreground_texture.loadFromFile("assets/foreground.png");
	this->foreground.setTexture(foreground_texture);
	this->foreground.setScale(this->width_proportion, this->height_proportion);

	//position
	this->foreground.setPosition(0.f, 0.f);
}


void Game::initBackground()
{
	//preoperties
	this->backgrround_texture.loadFromFile("assets/background.png");
	this->background.setTexture(backgrround_texture);
	this->background.setScale(this->width_proportion, this->height_proportion);

	//position
	this->background.setPosition(0.f, 0.f);
}


void Game::initInterface()
{
	//Fonts
	this->textFont1.loadFromFile("assets/fonts/nulshock_bd.otf");
	this->textFont2.loadFromFile("assets/fonts/Roboto-Regular.ttf");


	//properties - pointsText
	this->pointsText.setFont(this->textFont1);
	this->pointsText.setCharacterSize(50);
    this->pointsText.setScale(this->width_proportion, this->height_proportion);
	this->pointsText.setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
	this->pointsText.setOutlineThickness(3.f);
	this->pointsText.setOutlineColor(sf::Color::White);

	this->pointsText.setString("Score: ");

	this->pointsText.setPosition(1500.f * width_proportion, 0.f);


	//properties - healthText
	this->healthText.setFont(this->textFont1);
	this->healthText.setCharacterSize(50);
    this->healthText.setScale(this->width_proportion, this->height_proportion);
	this->healthText.setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
	this->healthText.setOutlineThickness(3.f);
	this->healthText.setOutlineColor(sf::Color::White);

	this->healthText.setString("10");

	this->healthText.setPosition(1740.f * width_proportion, 80.f * height_proportion);

	//heart
	this->heart_texture.loadFromFile("assets/heart.png");
	heart.setTexture(heart_texture);
	heart.setScale(width_proportion * 0.2f, height_proportion * 0.2f);
	heart.setPosition(1660.f * width_proportion, 90.f * height_proportion);

    //reload key text
    this->reloadKeyText.setFont(this->textFont2);
    this->reloadKeyText.setCharacterSize(50);
    this->reloadKeyText.setScale(this->width_proportion, this->height_proportion);
    this->reloadKeyText.setFillColor(sf::Color::White);
	this->reloadKeyText.setOutlineColor(sf::Color::Black);
	this->reloadKeyText.setOutlineThickness(3.f);
    this->reloadKeyText.setString("R");

    float x_middle = videoMode.getDesktopMode().width / 2;
    float y_bottom = videoMode.getDesktopMode().height;
    this->reloadKeyText.setPosition((x_middle - 20.f) * width_proportion, y_bottom - 100.f);

	//key sprite
	this->key_texture.loadFromFile("assets/key.png");
	this->keySprite.setTexture(key_texture);
	this->keySprite.setScale(width_proportion, height_proportion);

	this->keySprite.setPosition((x_middle - 59.8f) * width_proportion, (y_bottom - 120.f) * height_proportion);


	//wave text
	this->waveText.setFont(this->textFont1);
	this->waveText.setCharacterSize(50);
	this->waveText.setScale(this->width_proportion, this->height_proportion);
	this->waveText.setFillColor(sf::Color(0.f, 0.f, 0.f, 200.f));
	this->waveText.setOutlineThickness(3.f);
	this->waveText.setOutlineColor(sf::Color::White);
	this->waveText.setString("Wave: 1");

	this->waveText.setPosition(5.f, 5.f);
}


void Game::initCrosshair()
{
	this->crosshair_texture.loadFromFile("assets/crosshair.png");
	this->crosshair.setTexture(this->crosshair_texture);
	this->crosshair.setScale(1.f,1.f);
	this->crosshair.setColor(sf::Color::Green);
}



void Game::initMusic()
{
	this->soundtrack.openFromFile("assets/audio/soundtrack.ogg");
	//this->soundtrack.play();
	this->soundtrack.setLoop(true);
	this->soundtrack.setVolume(12.f);

	this->soundEnabled = false;
}


//Accesors
const bool Game::running() const
{
	return this->window->isOpen();
}

//functions
void Game::updateDelta()
{
	this->deltaTime = deltaClock.restart();
}


void Game::updateMouse()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::updateInterface()
{
	this->pointsText.setString("Score: " + std::to_string(this->targets.score));
	this->healthText.setString(std::to_string(this->targets.health));
    this->reloadKeyText.setString(this->targets.keyToPress_char);
	this->waveText.setString("Wave: " + std::to_string(targets.wave + 1));
}


void Game::updateCrosshair()
{
	float x = this->mousePosView.x - ((287.f * crosshair.getScale().x) / 2.f);
	float y = this->mousePosView.y - ((286.f * crosshair.getScale().y) / 2.f);
	this->crosshair.setPosition(x, y);

	if (this->targets.reloading)
		this->crosshair.setColor(sf::Color::Red);
	else
		this->crosshair.setColor(sf::Color::Green);
}

void Game::updateMusic()
{
	if (this->soundEnabled)
	{
		if (this->soundtrack.getStatus() != 2)
			this->soundtrack.play();
	}
	else
		this->soundtrack.pause();

}

void Game::update()
{
	this->updateStatus();
	this->updateDelta();
	this->updateMouse();

	//Modified by game state
	if(this->status == "playing")
		this->targets.update(this->deltaTime, this->mousePosView, this->mouseHeld, this->status);

	this->menus.update(this->mousePosView, this->status, this->mouseHeld, this->soundEnabled, this->restartGame, targets.shots_fired, targets.shots_hit, targets.score);
	
	if (this->restartGame)
	{
		this->targets.restartGame();
		this->restartGame = false;
	}


	this->updateInterface();
	this->updateCrosshair();
	this->updateMusic();
}



void Game::renderForeground()
{
	this->window->draw(this->foreground);
}

void Game::renderBackground()
{
	this->window->draw(background);
}


void Game::renderInterface()
{
	this->window->draw(this->pointsText);
	this->window->draw(this->healthText);
	this->window->draw(this->heart);
	this->window->draw(this->waveText);

	if (this->targets.reloading)
	{
		this->window->draw(this->keySprite);
		this->window->draw(this->reloadKeyText);
	}
		
}

void Game::renderCrosshair()
{
	this->window->draw(this->crosshair);
}

void Game::render()
{
	this->window->clear();

	//Draw Game
	this->renderBackground();
	this->targets.render(*(this->window));
	this->renderForeground();
	this->renderInterface();
	this->menus.render(*(this->window), this->status);
	this->renderCrosshair();

	this->window->display();
}
