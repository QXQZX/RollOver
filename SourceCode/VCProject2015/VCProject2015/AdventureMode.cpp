#include "AdventureMode.h"

bool		Adventure::left_pressed;	// �������Ƿ���;
Card*		Adventure::card;			// ֲ�￨d;
Plant*		Adventure::seed;			// ֲ������
Shovel*		Adventure::shovel;			// ѡ����С����
CSprite		Adventure::background("background");
CSprite     Adventure::game_over("GameOver");
CSprite     Adventure::game_close("GameClose");
CSprite     Adventure::play_again("PlayAgain");

void Adventure::OnMouseMove(const float fMouseX, const float fMouseY) {
	if (left_pressed && shovel) {
		shovel->SetSpritePosition(fMouseX, fMouseY);
	}
	else if (left_pressed && seed) {
		seed->SetSpritePosition(fMouseX, fMouseY);
	}
}
void Adventure::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {


	if (iMouseType == MOUSE_LEFT) {
		left_pressed = true;
		card = nullptr;
		seed = nullptr;
		shovel = nullptr;

		if (game_over.IsSpriteVisible()) {
			if (game_close.IsPointInSprite(fMouseX, fMouseY)) {
				CSystem::LoadMap("menu.t2d");
				g_GameMain.reload();
				g_GameMain.map_id = CGameMain::MapType::MenuType;
			}

			if (play_again.IsPointInSprite(fMouseX, fMouseY)) {
				game_over.SetSpriteVisible(false);
				game_close.SetSpriteVisible(false);
				play_again.SetSpriteVisible(false);
				std::string s = "adventure_level";
				g_GameMain.reload();
				CSystem::LoadMap(std::string(s + std::to_string(g_GameMain.adventure_level_id) + ".t2d").c_str());
			}
		}

		// ��ֵ���� ���Ч��
		std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
		for (const auto& sprite : sprites) {
			// ѡ�е�λ����̫��
			if (sprite->get_type() == "Sun") {
				Sun* sun = reinterpret_cast<Sun*>(sprite);
				sun->SpriteMoveTo(-43.275, -33.275, 100, true);
				sun->SetSpriteLifeTime(1);
				g_GameMain.add_sun(sun->get_num());
				sun->set_exist(false);
				left_pressed = false;
				break;
			}

			// ѡ�е�λ����С���������κ�����
			if (sprite->get_type() == "Car") {
				continue;
			}

			// ѡ�в���
			if (sprite->get_type() == "Shovel") {
				shovel = reinterpret_cast<Shovel*>(sprite);
				break;
			}

			// ѡ�п�Ƭ
			std::string type = sprite->get_type();
			// ����λCard��ʾ ֲ�￨
			if (type.substr(type.size() - 4, 4) == "Card") {
				// ��갴�� ѡ��ֲ�￨
				card = reinterpret_cast<Card*>(sprite);
				// ���ѡ�еĿ� ��ȴ���
				if (card->ready(fTimeDelta)) {
					if (sprite->get_type() == "PeaShooterCard") {
						seed = g_GameMain.create_pea_shooter(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "SunflowerCard") {
						seed = g_GameMain.create_sunflower(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "CherryBombCard") {
						// ���µ�ʱ�� �����ж��Ƿ��Զ���ը
						seed = g_GameMain.create_cherry_bomb(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "PotatoMineCard") {
						// ���µ�ʱ�� �����ж��Ƿ��ͷ
						seed = g_GameMain.create_potato_mine(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "WallNutCard") {
						seed = g_GameMain.create_wall_nut(fMouseX, fMouseY);
					}
					else if (sprite->get_type() == "JalapenoCard") {
						// ���µ�ʱ�� �����ж��Ƿ��Զ���ը
						seed = g_GameMain.create_jalapeno(fMouseX, fMouseY, fTimeDelta);
					}
					else if (sprite->get_type() == "ThreePeaterCard") {
						std::cout << "Three" << std::endl;
						seed = g_GameMain.create_three_peater(fMouseX, fMouseY);
					}
					seed->SetSpriteColorAlpha(100);
				}
				else {
					card = nullptr;
				}
				break;
			}
		}
	}
}

void Adventure::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {
	float x_slot[10] = { -39, -28.5, -18, -7.5, 2, 12, 22, 32, 43, 55 };
	float y_slot[5] = { -17, -5, 9, 20, 32 };

	int x = 0, y = 0;
	for (int i = 1; i < 10; i++) {
		if (abs(fMouseX - x_slot[x]) > abs(fMouseX - x_slot[i])) {
			x = i;
		}
	}
	if (iMouseType == MOUSE_LEFT) {
		if (left_pressed && seed && card) {
			for (int i = 1; i < 5; i++) {
				if (abs(fMouseY - y_slot[y] + seed->GetSpriteHeight() / 2) > abs(fMouseY - y_slot[i] + seed->GetSpriteHeight() / 2)) {
					y = i;
				}
			}
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
			seed->SetSpriteColorAlpha(255);
			bool planting = true;

			for (const auto& sprite : sprites) {
				// ������ֲ�� ������
				if (sprite->get_type() == "Plant") {
					planting = false;
					break;
				}

				// �н�ʬ �����
				if (sprite->get_type() == "Zombie") {
					if (card->get_type() == "CherryBombCard") {
						planting = true;
					}
					else {
						planting = false;
					}
					break;
				}
			}

			// ������� & �������
			if (planting && g_GameMain.planting(seed) && card) {
				seed->SetSpritePosition(x_slot[x], y_slot[y] - seed->GetSpriteHeight() / 2);
				seed->set_exist(true);
				card->plant_time(fTimeDelta);
			}
			else {
				seed->DeleteSprite();
			}
		}
		else if (left_pressed && shovel) {
			std::vector<PvZSprite*>&& sprites = g_GameMain.get_sprites_by_position(fMouseX, fMouseY);
			// λ������ֲ�� ����
			for (const auto& sprite : sprites) {
				std::cout << sprite->GetName() << std::endl;
				if (sprite->get_type() == "Plant") {
					Plant* p = reinterpret_cast<Plant*>(sprite);
					p->die();
					break;
				}
			}
			shovel->SetSpritePosition(12.093, -32.500);
		}
		left_pressed = false;
		seed = nullptr;
		shovel = nullptr;
	}
}

void Adventure::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {

}

void Adventure::OnKeyUp(const int iKey) {

}

void Adventure::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {
	if (!game_over.IsSpriteVisible() && std::string(szTarName) == "background") {
		game_over.SetSpriteVisible(true);
		game_close.SetSpriteVisible(true);
		play_again.SetSpriteVisible(true);
		return;
	}
	PvZSprite* src = g_GameMain.get_sprite_by_name(szSrcName);
	PvZSprite* tar = g_GameMain.get_sprite_by_name(szTarName);

	if (src && tar) {

		// С������
		if (src->get_type() == "Car" && tar->get_type() == "Zombie") {
			std::cout << "src:" << src->get_type() << "  tar:" << tar->get_type() << std::endl;
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			Car* c = reinterpret_cast<Car*>(src);
			c->SetSpriteLinearVelocityX(25.0);
			z->die(0);
		}

		// ��ʬ���빥����Χ
		if (src->get_type() == "Range" && tar->get_type() == "Zombie") {
			// ת�����丸�����ָ��
			PvZSprite* pvz = g_GameMain.get_sprite_by_name(src->GetSpriteMountedParent());
			Plant* p = reinterpret_cast<Plant*>(pvz);
			p->attack(fTimeDelta);
		}

		// ��ʬ��ֲ��
		if (src->get_type() == "Zombie" && tar->get_type() == "Plant") {
			Zombie* z = reinterpret_cast<Zombie*>(src);
			Plant* p = reinterpret_cast<Plant*>(tar);
			z->eat_plant(p, fTimeDelta);
		}

		// �ӵ���ʬ
		if (src->get_type() == "Arms" && tar->get_type() == "Zombie") {
			Arms* a = reinterpret_cast<Arms*>(src);
			Zombie* z = reinterpret_cast<Zombie*>(tar);
			z->attacked_by(a);
		}
	}
}

void Adventure::OnSpriteColWorldLimit(const char* szName, const int iColSide) {

}