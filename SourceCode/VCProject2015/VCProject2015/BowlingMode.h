#pragma once
#include "LessonX.h"
extern long double fTimeDelta;
extern long double game_start;
extern int bowling_counter;
extern int total_zombie;
namespace Bowling {
    extern bool			    left_pressed;   // �������Ƿ���
    extern Card*            card;		    // ֲ�￨
    extern Plant*           seed;		    // ֲ������
    extern WallNutBowling   bowling;        // 
    extern CSprite          top_side;       // �Ϸ�����ǽ
    extern CSprite          bottom_side;    // �·�����ǽ
    extern CSprite          background;

    extern CSprite          game_over;      // ��Ϸʧ��ͼƬ
    extern CSprite          game_close;     // �������˵���ť
    extern CSprite          play_again;     // ���¿�ʼ��ť

    extern CSprite          game_win;        // ��Ϸʤ��ͼƬ
    extern CSprite          game_close2;    // �������˵���ť
    extern CSprite          next;           // ��һ�ذ�ť 

    // ��Ϸ�еĲ˵�
    extern CSprite          game_menu_btn;
    extern CSprite          game_menu;
    extern CSprite          main_menu;
    extern CSprite          rebegin;
    extern CSprite          continue_;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};

