#pragma once
#include "LessonX.h"



namespace Menu {
    extern CStaticSprite adventure;	    // ð��ģʽ
    extern CStaticSprite mini;			// ������Ϸ
    extern CStaticSprite edu;			// ����ģʽ

    extern CStaticSprite help_btn;		// ������ť
    extern CStaticSprite help_msg;		// ������Ϣ���
    extern CStaticSprite help_close;	// �����رհ�ť
    extern CStaticSprite exit_;	        // �˳���Ϸ

    extern CStaticSprite achievement;   // �ɾͰ�ť
    extern CStaticSprite score_board;   // �ɾ����
    extern CStaticSprite score_close;   // �ɾ����ر�

    extern CStaticSprite level_1;
    extern CStaticSprite level_2;
    extern CStaticSprite level_3;
    extern CStaticSprite level_4;
    extern CStaticSprite level_5;

    // ��ʱ
    extern CTextSprite	 bowling_score;
    extern CTextSprite	 level1_score;
    extern CTextSprite	 level2_score;
    extern CTextSprite	 level3_score;
    extern CTextSprite	 level4_score;
    extern CTextSprite	 level5_score;

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};
