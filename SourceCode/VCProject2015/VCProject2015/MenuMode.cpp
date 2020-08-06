#include "MenuMode.h"

CStaticSprite Menu::adventure("AdventureGame");		// ð��ģʽ
CStaticSprite Menu::mini("MiniGame");				// ������Ϸ
CStaticSprite Menu::edu("EduGame");					// ����ģʽ
CStaticSprite Menu::help_btn("helpBtn");			// ������ť
CStaticSprite Menu::help_msg("helpMsg");			// ������Ϣ���
CStaticSprite Menu::help_close("helpClose");		// �رհ�����Ϣ

void Menu::OnMouseMove(const float fMouseX, const float fMouseY) {
	// �������λ�� ��ʾ��ͬͼƬ
	adventure.SetStaticSpriteImage("AdventureModeImageMap", adventure.IsPointInSprite(fMouseX, fMouseY));
	mini.SetStaticSpriteImage("MiniModeImageMap", mini.IsPointInSprite(fMouseX, fMouseY));
	edu.SetStaticSpriteImage("EduModeImageMap", edu.IsPointInSprite(fMouseX, fMouseY));
}

void Menu::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY) {
	// �����ͬ��ť ���ز�ͬ��ͼ
	if (adventure.IsPointInSprite(fMouseX, fMouseY)) {
		CSystem::LoadMap("levelChooser.t2d");
		g_GameMain.map_id = CGameMain::MapType::LevelChooserType;
	}
	else if (mini.IsPointInSprite(fMouseX, fMouseY)) {
		// ...
	}
	else if (edu.IsPointInSprite(fMouseX, fMouseY)){
		CSystem::LoadMap("bowling.t2d");
		g_GameMain.map_id = CGameMain::MapType::BowlingType;
	}

	if (help_btn.IsPointInSprite(fMouseX, fMouseY)) {
		help_msg.SpriteMoveTo(1.094, -5.124, 50, true);
	}
	if (help_close.IsPointInSprite(fMouseX, fMouseY)) {
		help_msg.SpriteMoveTo(-0.198, -64.815, 80, true);
	}
}

void Menu::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY) {}
void Menu::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress) {}
void Menu::OnKeyUp(const int iKey) {}
void Menu::OnSpriteColSprite(const char* szSrcName, const char* szTarName) {}
void Menu::OnSpriteColWorldLimit(const char* szName, const int iColSide) {}