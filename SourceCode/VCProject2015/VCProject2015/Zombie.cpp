#include "Zombie.h"
#include "Plant.h"
#include "SuperSound.h"
const std::string Zombie::type = "Zombie";

Zombie::Zombie(const char* sprite_name, int health, int move_speed, double power) :
	PvZSprite(sprite_name),
	health(health),
	move_speed(move_speed),
	power(power),
	next_attack(0),
	attack_interval(1),
	eating(false),
	eating_plant(nullptr)
{

}

const std::string Zombie::get_type() {
	return type;
}
bool Zombie::is_eating() {
	return eating;
}

void Zombie::set_eating(bool eating) {
	this->eating = eating;
}

void Zombie::set_plant(Plant* plant) {
	eating_plant = plant;
}
Plant* Zombie::get_plant() {
	return eating_plant;
}

void Zombie::set_eating_plant(Plant* eating_plant) {
	this->eating_plant = eating_plant;
}

bool Zombie::attacked_by(Arms* arm) {
	if (this->health <= 0) {
		return true;
	}
	else {
		return false;
	}
}

/////////////////////////
// ��ͨ��ʬ

OrdinaryZombie::OrdinaryZombie(const char* zombie_name) : Zombie(zombie_name, 200, 2, 50)
{

}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void OrdinaryZombie::move() {
	this->eating = false;
	this->set_status();
	this->SetSpriteLinearVelocityX(-this->move_speed);
}

void OrdinaryZombie::stop() {
	this->set_status();
	this->SetSpriteLinearVelocityX(0);
}

void OrdinaryZombie::eat_plant(Plant* plant, long double delta_time) {
	if (delta_time - next_attack > attack_interval) {
		SuperSound::closeAndPlay("open-eat", "play-eat", "close-eat");
		plant->attacked_by(this);
		next_attack = delta_time;
	}
}

bool OrdinaryZombie::attacked_by(Arms* arms) {
	//SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");
	this->health -= arms->get_power();
	if (this->health <= 0) {
		this->die(arms->get_power());
	}
	else {
		this->set_status();
	}
	arms->after_hit();
	return Zombie::attacked_by(arms);
}

/// <summary>
/// ��������
/// </summary>
void OrdinaryZombie::die(int power) {
	if (power < 1800) {
		this->SetSpriteWidth(20.625);
		this->SetSpriteHeight(10.625);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);

	}
	else {
		this->SetSpriteLinearVelocityX(0);
		this->SetSpriteWidth(9.875);
		this->SetSpriteHeight(14.125);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
	}
	this->SetSpriteCollisionActive(false, false);
	// ������������
	this->SetSpriteLifeTime(1);
	exist = false;
}

double OrdinaryZombie::get_power() {
	return power;
}

OrdinaryZombie::~OrdinaryZombie() {
	std::cout << "~OrdinaryZombie()" << std::endl;
}

void OrdinaryZombie::set_status() {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	float currentPositionY = this->GetSpritePositionY();
	if (this->health > 100) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);

			}
		}
		else {
			if (currentAnimation != "OrdinaryZombieAnimation") {
				this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
			}
		}
	}
	else if (this->health <= 100) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
				this->SetSpriteWidth(11.125);
				this->SetSpriteHeight(12.875);
				this->SetSpritePositionY(currentPositionY + 1);
			}
		}
		else {
			if (currentAnimation != "ZombieLoseHeadAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);
				this->SetSpriteWidth(10.000);
				this->SetSpriteHeight(11.875);
				this->SetSpritePositionY(currentPositionY + 1);
			}
		}
	}
}

/////////////////////////
// ·�Ͻ�ʬ

BarricadeZombie::BarricadeZombie(const char* zombie_name) : Zombie(zombie_name, 640, 2, 50)
{

}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void BarricadeZombie::move() {
	this->eating = false;
	this->set_status();
	this->SetSpriteLinearVelocityX(-this->move_speed);
}

void BarricadeZombie::stop() {
	this->set_status();
	this->SetSpriteLinearVelocityX(0);
}

void BarricadeZombie::eat_plant(Plant* plant, long double delta_time) {
	if (delta_time - next_attack > attack_interval) {
		SuperSound::closeAndPlay("open-eat", "play-eat", "close-eat");
		plant->attacked_by(this);
		next_attack = delta_time;
	}
}



bool BarricadeZombie::attacked_by(Arms* arms) {
	this->health -= arms->get_power();
	//SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");
	std::cout << "·�Ͻ�ʬ��ǰѪ����" << this->health << std::endl;

	if (this->health <= 0) {
		this->die(arms->get_power());
	}
	else {
		this->set_status();
	}
	arms->after_hit();
	return Zombie::attacked_by(arms);
}

/// <summary>
/// ��������
/// </summary>
void BarricadeZombie::die(int power) {
	if (power < 1800) {
		this->SetSpriteWidth(20.625);
		this->SetSpriteHeight(10.625);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
	}
	else {
		this->SetSpriteLinearVelocityX(0);
		this->SetSpriteWidth(9.875);
		this->SetSpriteHeight(14.125);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
	}
	this->SetSpriteCollisionActive(false, false);
	// ������������
	this->SetSpriteLifeTime(1);
	exist = false;
}

double BarricadeZombie::get_power() {
	return power;
}

BarricadeZombie::~BarricadeZombie() {
	std::cout << "~OrdinaryZombie()" << std::endl;
}

void BarricadeZombie::set_status() {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	float currentPositionY = this->GetSpritePositionY();
	if (this->health > 270) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "BarricadeZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("BarricadeZombieAttackAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(18.00);
			}


		}
		else {
			if (currentAnimation != "BarricadeZombieAnimation") {
				this->AnimateSpritePlayAnimation("BarricadeZombieAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(18.00);
			}

		}
	}
	else if (this->health >= 90) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(15.50);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
		else {
			if (currentAnimation != "OrdinaryZombieAnimation") {
				this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(15.50);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
	else
	{
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
				this->SetSpriteWidth(11.125);
				this->SetSpriteHeight(12.875);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}


		}
		else {
			if (currentAnimation != "ZombieLoseHeadAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);

				this->SetSpriteWidth(10.000);
				this->SetSpriteHeight(11.875);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
}


/////////////////////////
// ��Ͱ��ʬ

BucketheadZombie::BucketheadZombie(const char* zombie_name) : Zombie(zombie_name, 1370, 2, 50)
{

}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void BucketheadZombie::move() {
	this->eating = false;
	this->set_status();
	this->SetSpriteLinearVelocityX(-this->move_speed);
}

void BucketheadZombie::stop() {
	this->set_status();
	this->SetSpriteLinearVelocityX(0);
}

void BucketheadZombie::eat_plant(Plant* plant, long double delta_time) {
	if (delta_time - next_attack > attack_interval) {
		SuperSound::closeAndPlay("open-eat", "play-eat", "close-eat");
		plant->attacked_by(this);
		next_attack = delta_time;
	}
}



bool BucketheadZombie::attacked_by(Arms* arms) {
	this->health -= arms->get_power();
	//SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");
	std::cout << "��Ͱ��ʬ��ǰѪ����" << this->health << std::endl;

	if (this->health <= 0) {
		this->die(arms->get_power());
	}
	else {
		this->set_status();
	}
	arms->after_hit();
	return Zombie::attacked_by(arms);
}

/// <summary>
/// ��������
/// </summary>
void BucketheadZombie::die(int power) {
	if (power < 1800) {
		this->SetSpriteWidth(20.625);
		this->SetSpriteHeight(10.625);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
	}
	else {
		this->SetSpriteLinearVelocityX(0);
		this->SetSpriteWidth(9.875);
		this->SetSpriteHeight(14.125);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
	}
	this->SetSpriteCollisionActive(false, false);
	// ������������
	this->SetSpriteLifeTime(1);
	exist = false;
}

double BucketheadZombie::get_power() {
	return power;
}

BucketheadZombie::~BucketheadZombie() {
	std::cout << "~OrdinaryZombie()" << std::endl;
}

void BucketheadZombie::set_status() {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	float currentPositionY = this->GetSpritePositionY();
	if (this->health > 270) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "BucketheadZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("BucketheadZombieAttackAnimation", false);
				this->SetSpriteWidth(11.5);
				this->SetSpriteHeight(17.625);
			}


		}
		else {
			if (currentAnimation != "BucketheadZombieAnimation") {
				this->AnimateSpritePlayAnimation("BucketheadZombieAnimation", false);
				this->SetSpriteWidth(11.5);
				this->SetSpriteHeight(17.625);
			}

		}
	}
	else if (this->health >= 90) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieAttackAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(15.50);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
		else {
			if (currentAnimation != "OrdinaryZombieAnimation") {
				this->AnimateSpritePlayAnimation("OrdinaryZombieAnimation", false);
				this->SetSpriteWidth(10.875);
				this->SetSpriteHeight(15.50);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
	else
	{
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "ZombieLoseHeadAttackAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAttackAnimation", false);
				this->SetSpriteWidth(11.125);
				this->SetSpriteHeight(12.875);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}


		}
		else {
			if (currentAnimation != "ZombieLoseHeadAnimation") {
				this->AnimateSpritePlayAnimation("ZombieLoseHeadAnimation", false);

				this->SetSpriteWidth(10.000);
				this->SetSpriteHeight(11.875);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
}


/////////////////////////
// ����ү

NewspaperZombie::NewspaperZombie(const char* zombie_name) : Zombie(zombie_name, 450, 2, 50)
{
	this->hasnewspaper = true;
}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void NewspaperZombie::move() {
	this->eating = false;
	this->set_status();
	this->SetSpriteLinearVelocityX(-this->move_speed);
}

void NewspaperZombie::stop() {
	this->set_status();
	this->SetSpriteLinearVelocityX(0);
}

void NewspaperZombie::eat_plant(Plant* plant, long double delta_time) {
	if (delta_time - next_attack > attack_interval) {
		SuperSound::closeAndPlay("open-eat", "play-eat", "close-eat");
		plant->attacked_by(this);
		next_attack = delta_time;
	}
}



bool NewspaperZombie::attacked_by(Arms* arms) {
	int last_health = this->health;
	this->health -= arms->get_power();
	if (last_health >= 350 && this->health < 350) {
		SuperSound::closeAndPlay("open-news-paper-broken", "play-news-paper-broken", "close-news-paper-broken");
	}
	//SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");

	if (this->health <= 0) {
		this->die(arms->get_power());
	}
	else {
		this->set_status();
	}
	arms->after_hit();
	return Zombie::attacked_by(arms);
}

/// <summary>
/// ��������
/// </summary>
void NewspaperZombie::die(int power) {
	if (power < 1800) {
		this->SetSpriteWidth(20.625);
		this->SetSpriteHeight(10.625);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("NewspaperZombieDieAnimation", false);
	}
	else {
		this->SetSpriteLinearVelocityX(0);
		this->SetSpriteWidth(9.875);
		this->SetSpriteHeight(14.125);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
	}
	this->SetSpriteCollisionActive(false, false);
	// ������������
	this->SetSpriteLifeTime(1);
	exist = false;
}

double NewspaperZombie::get_power() {
	return power;
}

NewspaperZombie::~NewspaperZombie() {

}

void NewspaperZombie::set_status() {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	float currentPositionY = this->GetSpritePositionY();
	if (this->health > 350) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "NewspaperZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieAttackAnimation", false);
				this->SetSpriteWidth(12.0);
				this->SetSpriteHeight(17.125);
			}


		}
		else {
			if (currentAnimation != "NewspaperZombieAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieAnimation", false);
				this->SetSpriteWidth(12.0);
				this->SetSpriteHeight(17.125);
			}

		}
	}
	else if (this->health >= 90) {

		if (this->hasnewspaper) {
			if (currentAnimation != "NewspaperZombieLoseNewspaperAnimation")
			{
				this->SetSpriteLinearVelocityX(0);
				this->power = 0;
				this->AnimateSpritePlayAnimation("NewspaperZombieLoseNewspaperAnimation", false);
				std::thread t([=] {
					while (!this->IsAnimateSpriteAnimationFinished())
						Sleep(50);
					this->power = 70;
					this->move_speed = this->move_speed + 2;
					this->SetSpriteLinearVelocityX(-this->move_speed);
					this->hasnewspaper = false;
					this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAnimation", false);
					this->SetSpriteWidth(12.0);
					this->SetSpriteHeight(15.5);

					});
				t.detach();
			}

		}
		else if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "NewspaperZombieCrazyAttackAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAttackAnimation", false);
				this->SetSpriteWidth(11.5);
				this->SetSpriteHeight(15.5);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
		else {
			if (currentAnimation != "NewspaperZombieCrazyAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieCrazyAnimation", false);
				this->SetSpriteWidth(12.0);
				this->SetSpriteHeight(15.5);
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
	else
	{
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "NewspaperZombieLoseHeadAttackAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieLoseHeadAttackAnimation", false);
				this->SetSpriteWidth(10.8);
				this->SetSpriteHeight(12.5);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}


		}
		else {
			if (currentAnimation != "NewspaperZombieLoseHeadAnimation" && currentAnimation != "NewspaperZombieLoseNewspaperAnimation") {
				this->AnimateSpritePlayAnimation("NewspaperZombieLoseHeadAnimation", false);
				this->SetSpriteWidth(10.8);
				this->SetSpriteHeight(12.5);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
}


/////////////////////////
// �����ʬ

FootballZombie::FootballZombie(const char* zombie_name) : Zombie(zombie_name, 1400, 3.5, 50)
{

}

/// <summary>
/// �ý�ʬ��ʼ�ƶ�
/// </summary>
void FootballZombie::move() {
	this->eating = false;
	this->set_status();
	this->SetSpriteLinearVelocityX(-this->move_speed);
}

void FootballZombie::stop() {
	this->set_status();
	this->SetSpriteLinearVelocityX(0);
}

void FootballZombie::eat_plant(Plant* plant, long double delta_time) {
	if (delta_time - next_attack > attack_interval) {
		SuperSound::closeAndPlay("open-eat", "play-eat", "close-eat");
		plant->attacked_by(this);
		next_attack = delta_time;
	}
}



bool FootballZombie::attacked_by(Arms* arms) {
	this->health -= arms->get_power();
	//SuperSound::closeAndPlay("open-hit", "play-hit", "close-hit");
	std::cout << "�����ʬ��ǰѪ����" << this->health << std::endl;

	if (this->health <= 0) {
		this->die(arms->get_power());
	}
	else {
		this->set_status();
	}
	arms->after_hit();
	return Zombie::attacked_by(arms);
}

/// <summary>
/// ��������
/// </summary>
void FootballZombie::die(int power) {
	if (power < 1800) {
		this->SetSpriteWidth(20.625);
		this->SetSpriteHeight(10.625);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("ZombieDieAnimation", false);
	}
	else {
		this->SetSpriteLinearVelocityX(0);
		this->SetSpriteWidth(9.875);
		this->SetSpriteHeight(14.125);
		this->SetSpriteLinearVelocityX(0);
		this->AnimateSpritePlayAnimation("BoomDieAnimation", false);
	}
	this->SetSpriteCollisionActive(false, false);
	// ������������
	this->SetSpriteLifeTime(1);
	exist = false;
}

double FootballZombie::get_power() {
	return power;
}

FootballZombie::~FootballZombie() {

}

void FootballZombie::set_status() {
	std::string currentAnimation = this->GetAnimateSpriteAnimationName();
	float currentPositionY = this->GetSpritePositionY();
	if (this->health > 530) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "FootballZombieAttackAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieAttackAnimation", false);
				this->SetSpriteWidth(16.25);
				this->SetSpriteHeight(17.0);
			}


		}
		else {
			if (currentAnimation != "FootballZombieAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieAnimation", false);
				this->SetSpriteWidth(19.25);
				this->SetSpriteHeight(20.0);
			}

		}
	}
	else if (this->health >= 150) {
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "FootballZombieLoseHatAttackAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieLoseHatAttackAnimation", false);
				this->SetSpriteWidth(16.25);
				this->SetSpriteHeight(17.0);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
		else {
			if (currentAnimation != "FootballZombieLoseHatAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieLoseHatAnimation", false);
				this->SetSpriteWidth(19.25);
				this->SetSpriteHeight(20.0);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
	else
	{
		if (eating_plant && eating_plant->is_exist()) {
			if (currentAnimation != "FootballZombieLoseHeadAttackAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieLoseHeadAttackAnimation", false);
				this->SetSpriteWidth(15.25);
				this->SetSpriteHeight(16.0);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}


		}
		else {
			if (currentAnimation != "FootballZombieLoseHeadAnimation") {
				this->AnimateSpritePlayAnimation("FootballZombieLoseHeadAnimation", false);
				this->SetSpriteWidth(17.25);
				this->SetSpriteHeight(18.0);
				float currentPositionY = this->GetSpritePositionY();
				this->SetSpritePositionY(currentPositionY + 1);
			}

		}
	}
}