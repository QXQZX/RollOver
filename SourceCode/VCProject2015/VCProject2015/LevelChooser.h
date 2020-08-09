#pragma once
#include "LessonX.h"
extern long double fTimeDelta;

namespace LevelChooser {
    extern bool			left_pressed;   // �������Ƿ���
    extern CStaticSprite level_1;	    // ��һ��
    extern CStaticSprite level_2;	    // �ڶ���
    extern CStaticSprite level_3;	    // ������

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};

