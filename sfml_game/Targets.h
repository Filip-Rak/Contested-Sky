#pragma once  

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Targets
{
private:
	//Technical
	//sf::RenderTarget& window;
	float deltaTimeF;

	//Audio
	sf::SoundBuffer shot_sound_buffer;
	sf::Sound shotSound;
	sf::SoundBuffer reload_sound_buffer;
	sf::Sound reloadSound;
	sf::SoundBuffer falling_sound_buffer;
	sf::Sound fallingSound;
	sf::SoundBuffer ricochet_sound_buffer;
	sf::Sound ricochetSound;
	sf::SoundBuffer landing_sound_buffer;
	sf::Sound landingSound;

	//Textures
	static const int types = 4;
	static const int states = 3;  //0 - whole, 1 - chute, 2 - trooper
	sf::Texture green_texture[states];
	sf::Texture gray_texture[states];
	sf::Texture purple_texture[states];
	sf::Texture brown_texture[states];

	//Sprites
	sf::Sprite greenSprite[states];
	sf::Sprite graySprite[states];
	sf::Sprite purpleSprite[states];
	sf::Sprite brownSprite[states];
	float spriteScale;

	//Stats
	float speed[types];
	int hp[types];
	float size_modifier;

	//Game objects
	struct para {
		float speed;
		int hp_max;
		int hp;
		bool isOkieDokie;

		sf::Sprite sprite_main;
		sf::Sprite sprite_chute;
		sf::Sprite sprite_trooper;
	};
	
	std::vector<para> spawned_para;
	para para_buffer;


	//Spawning
	int spawn_percentages[types];
	int enemies_to_spawn;
	int enemies_to_spawn_left;
	float spawn_cooldown;
	float spawn_cooldown_left;


	//Shooting
	sf::Vector2f mousePosView;
	sf::Keyboard::Key keyToPress;


	//Private Methods
	void initTextures();
	void initSprites();
	void initStats();
	void initSpawner();
	void initShooting();
	void initAudio();
	sf::Keyboard::Key getRandomKey();

	void updateSpawner();
	void updateSpawning();
	void updateMovement(std::string& status);
	void updateShooting(bool &mouseHeld);


public:
	//Constructor / Destructor
	Targets();
	virtual ~Targets();

	//Vars
	bool reloading;
	char keyToPress_char;
	int score;
	int health;
	int shots_fired;
	int shots_hit;
	int wave;

	//methods
	void restartGame();
	void spawnTarget(float x, float y, int type);
	void update(sf::Time delta, sf::Vector2f mousePosView, bool &mouseHeld, std::string& status);
	void render(sf::RenderTarget &target);
};

