#include "Targets.h" 

//Constructor / Destructor

Targets::Targets()
{
	this->initTextures();
	this->initSprites();
	this->initAudio();
}

Targets::~Targets()
{

}

//Private Methods
void Targets::initTextures()
{
	const std::string states[this->states] = { ".png", "_shute.png", "_without.png" };
	for (int i = 0; i < this->states; i++)
	{
		this->green_texture[i].loadFromFile("assets/paras/green" + states[i]);
		this->gray_texture[i].loadFromFile("assets/paras/gray" + states[i]);
		this->purple_texture[i].loadFromFile("assets/paras/purple" + states[i]);
		this->brown_texture[i].loadFromFile("assets/paras/brown" + states[i]);
	}
}

void Targets::initSprites()
{
	for (int i = 0; i < this->states; i++)
	{
		this->greenSprite[i].setTexture(green_texture[i], true);
		this->graySprite[i].setTexture(gray_texture[i], true);
		this->purpleSprite[i].setTexture(purple_texture[i], true);
		this->brownSprite[i].setTexture(brown_texture[i], true);
	}

	this->spriteScale = 0.25f;
}

void Targets::initStats()
{
	const float speeds[this->types] = {100.f, 50.f, 250.f, 175.f};  //basic, heavy, fast, ubershmugger 
	const int hp[this->types] = { 1, 3, 1, 2 };
	for (int i = 0; i < this->types; i++)
	{
		this->speed[i] = speeds[i];
		this->hp[i] = hp[i];
	}

	this->size_modifier = 0.25f;
}

void Targets::initSpawner()
{
	this->wave = 0;
	int spawnPrecent[this->types] = { 100, 0, 0, 0 };
	for(int i=0; i<this->types; i++)
		this->spawn_percentages[i] = spawnPrecent[i];

	this->enemies_to_spawn = this->enemies_to_spawn_left = 3;
	this->spawn_cooldown = 0.4f;
	this->spawn_cooldown_left = 0.f;
}

void Targets::initShooting()
{
	this->reloading = false;
	char keyToPress_char = 'R';
	sf::Keyboard::Key keyToPress = sf::Keyboard::R;
}

void Targets::initAudio()
{
	this->shot_sound_buffer.loadFromFile("assets/audio/shot_sound.ogg");
	this->shotSound.setBuffer(this->shot_sound_buffer);
	this->shotSound.setVolume(8.f);
	
	this->reload_sound_buffer.loadFromFile("assets/audio/reload_sound.ogg");
	this->reloadSound.setBuffer(this->reload_sound_buffer);
	this->reloadSound.setVolume(20.f);
	
	this->falling_sound_buffer.loadFromFile("assets/audio/falling_sound.ogg");
	this->fallingSound.setBuffer(this->falling_sound_buffer);
	this->fallingSound.setVolume(4.f);
	
	this->ricochet_sound_buffer.loadFromFile("assets/audio/hit_sound.ogg");
	this->ricochetSound.setBuffer(this->ricochet_sound_buffer);
	this->ricochetSound.setVolume(12.f);
	
	this->landing_sound_buffer.loadFromFile("assets/audio/landing_sound.ogg");
	this->landingSound.setBuffer(this->landing_sound_buffer);
	this->landingSound.setVolume(100.f);
}

void Targets::restartGame()
{
	//clear paras
	this->spawned_para.clear();

	this->shots_fired = 0;
	this->shots_hit = 0;
	this->score = 0;
	this->health = 3;
	this->initSpawner();
	this->initShooting();
	this->initStats();
}

void Targets::spawnTarget(float x, float y, int type)
{
	//properties
	this->para_buffer.hp = this->hp[type];
	this->para_buffer.hp_max = this->hp[type];
	this->para_buffer.speed = this->speed[type];
	this->para_buffer.isOkieDokie = true;

	//visuals
	switch(type)
	{
		default:
		case 0:
			this->para_buffer.sprite_main = greenSprite[0];
			this->para_buffer.sprite_chute = greenSprite[1];
			this->para_buffer.sprite_trooper = greenSprite[2];
			break;
		case 1:
			this->para_buffer.sprite_main = graySprite[0];
			this->para_buffer.sprite_chute = graySprite[1];
			this->para_buffer.sprite_trooper = graySprite[2];
			break;
		case 2:
			this->para_buffer.sprite_main = purpleSprite[0];
			this->para_buffer.sprite_chute = purpleSprite[1];
			this->para_buffer.sprite_trooper = purpleSprite[2];
			break;
		case 3:
			this->para_buffer.sprite_main = brownSprite[0];
			this->para_buffer.sprite_chute = brownSprite[1];
			this->para_buffer.sprite_trooper = brownSprite[2];
			break;
	}

	para_buffer.sprite_main.setScale(this->spriteScale, this->spriteScale);
	para_buffer.sprite_chute.setScale(this->spriteScale, this->spriteScale);
	para_buffer.sprite_trooper.setScale(this->spriteScale, this->spriteScale);

	//position
	this->para_buffer.sprite_main.setPosition(x, y);
	this->para_buffer.sprite_chute.setPosition(x, y);
	this->para_buffer.sprite_trooper.setPosition(x, y);

	this->spawned_para.push_back(para_buffer);
}

void Targets::updateSpawner()
{
	switch (this->wave)
	{
	case 1:
		this->enemies_to_spawn = 3;
		this->spawn_cooldown = 0.5f;
		break;

	case 2:
		this->enemies_to_spawn = 1;
		this->spawn_percentages[0] = 0;
		this->spawn_percentages[1] = 100;
		break;
	case 3:
		this->spawn_cooldown = 1.f;
		this->enemies_to_spawn = 5;
		this->spawn_percentages[0] = 75;
		this->spawn_percentages[1] = 25;
		break;
	case 4:
		this->spawn_cooldown = 1.f;
		this->enemies_to_spawn = 2;
		this->spawn_percentages[0] = 0;
		this->spawn_percentages[1] = 0;
		this->spawn_percentages[2] = 100;
		break;
	case 5:
		this->enemies_to_spawn = 7;
		this->spawn_percentages[0] = 50;
		this->spawn_percentages[1] = 25;
		this->spawn_percentages[2] = 25;
		break;
	case 6:
		this->spawn_cooldown = 1.2f;
		this->enemies_to_spawn = 10;
		this->spawn_percentages[0] = 30;
		this->spawn_percentages[3] = 20;
		break;

	case 7:
		this->spawn_cooldown = 1.2f;
		this->enemies_to_spawn = 10;
		this->spawn_percentages[0] = 30;
		this->spawn_percentages[1] = 25;
		this->spawn_percentages[2] = 25;
		this->spawn_percentages[3] = 20;
		break;

	default:
		this->spawn_cooldown *= 0.95f;
		this->enemies_to_spawn *= 1.3f;
	}

	this->enemies_to_spawn_left = this->enemies_to_spawn;
}

void Targets::updateSpawning()
{
	this->spawn_cooldown_left -= deltaTimeF;

	if (this->enemies_to_spawn_left > 0)
	{
		if (this->spawn_cooldown_left <= 0)
		{
			this->enemies_to_spawn_left--;
			this->spawn_cooldown_left = this->spawn_cooldown;

			int type_to_spawn = 0;
			for (int i = 0; i < this->types; i++)  //rand who to spawn based on percentages
			{
				if (rand() % 100 <= this->spawn_percentages[i])
				{
					type_to_spawn = i;
					break;
				}
			}

			//rand spawning coordinates
			float x = rand() % static_cast<int>((sf::VideoMode::getDesktopMode().width * 0.8f)) + (sf::VideoMode::getDesktopMode().width * 0.1f);
			float y = -732.f * this->para_buffer.sprite_main.getScale().y;

			this->spawnTarget(x, y, type_to_spawn);
		}
	}
	else
	{
		bool allDealtWith = true;
		for (auto& p : this->spawned_para)
		{
			if (p.sprite_trooper.getPosition().y < sf::VideoMode::getDesktopMode().height)
			{
				allDealtWith = false;
				break;
			}

		}

		if (allDealtWith)
		{
			this->wave++;
			this->updateSpawner();
		}
	}
}

void Targets::updateMovement(std::string& status)
{

	for (int i = 0; i < this->spawned_para.size(); i++)
	{
		if (this->spawned_para[i].hp > 0)
		{
			this->spawned_para[i].sprite_main.move(0.f, this->spawned_para[i].speed * this->deltaTimeF);
			this->spawned_para[i].sprite_chute.move(0.f, this->spawned_para[i].speed * this->deltaTimeF);
			this->spawned_para[i].sprite_trooper.move(0.f, this->spawned_para[i].speed * this->deltaTimeF);
		}
		else
		{
			this->spawned_para[i].sprite_main.setScale(0.f, 0.f);
			this->spawned_para[i].sprite_chute.move(0.f, this->spawned_para[i].speed * this->deltaTimeF);
			this->spawned_para[i].sprite_trooper.move(0.f, this->speed[0] * 4.f * this->deltaTimeF);
		}

		if (this->spawned_para[i].sprite_chute.getPosition().y > sf::VideoMode::getDesktopMode().height)
		{
			if (spawned_para[i].isOkieDokie)
			{
				this->health--;

				if (health <= 0)
					status = "lost";

				if (this->landingSound.getStatus() != 2)
					this->landingSound.play();

			}


			this->spawned_para.erase(this->spawned_para.begin() + i);
		}
	}	
}


void Targets::updateShooting(bool &mouseHeld)
{
	if (this->reloading)
	{
		if (sf::Keyboard::isKeyPressed(this->keyToPress))
		{
			this->reloading = false;
			this->reloadSound.play();
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->reloading)
		{
			if (!mouseHeld)
			{
				//gun fires here
				this->shotSound.play();
				mouseHeld = true;
				this->reloading = true;
				this->keyToPress = this->getRandomKey();
				this->shots_fired++;
				bool scored_a_hit = false;

				for (int i = 0; i < this->spawned_para.size(); i++)
				{
					if (this->spawned_para[i].sprite_main.getGlobalBounds().contains(this->mousePosView))
					{
						this->spawned_para[i].hp--;
						scored_a_hit = true;

						if (this->spawned_para[i].hp <= 0)
						{
							this->fallingSound.play();
							this->spawned_para[i].isOkieDokie = false;
							this->score += this->spawned_para[i].hp_max * 5;
						}
						else  //ricochet sound
							this->ricochetSound.play();  

					}
				}

				if (scored_a_hit)
					this->shots_hit++;

			}
		}
	}
	else
		mouseHeld = false;
}



//Public Methods
void Targets::update(sf::Time delta, sf::Vector2f mousePosView, bool &mouseHeld, std::string& status)
{
	this->mousePosView = mousePosView;
	this->deltaTimeF = delta.asSeconds();

	this->updateSpawning();
	this->updateMovement(status);
	this->updateShooting(mouseHeld);
}

void Targets::render(sf::RenderTarget &target)
{
	//this->window = target;

	for (auto &para : spawned_para)
	{
		target.draw(para.sprite_chute);
		target.draw(para.sprite_trooper);
		target.draw(para.sprite_main);
	}
}


//i hate it
sf::Keyboard::Key Targets::getRandomKey()
{
	const int alphabetSize = 26;

	sf::Keyboard::Key keys[alphabetSize] = {
		sf::Keyboard::Key::A, sf::Keyboard::Key::B, sf::Keyboard::Key::C, sf::Keyboard::Key::D, sf::Keyboard::Key::E, sf::Keyboard::Key::F,
		sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::I, sf::Keyboard::Key::J,sf::Keyboard::Key::K, sf::Keyboard::Key::L,
		sf::Keyboard::Key::M, sf::Keyboard::Key::N, sf::Keyboard::Key::O, sf::Keyboard::Key::P, sf::Keyboard::Key::Q, sf::Keyboard::Key::R,
		sf::Keyboard::Key::S, sf::Keyboard::Key::T, sf::Keyboard::Key::U, sf::Keyboard::Key::V, sf::Keyboard::Key::W, sf::Keyboard::Key::X,
		sf::Keyboard::Key::Y, sf::Keyboard::Key::Z
	};

	int key_id = rand() % alphabetSize;
	this->keyToPress_char = char(key_id + 65);

	return keys[key_id];
}