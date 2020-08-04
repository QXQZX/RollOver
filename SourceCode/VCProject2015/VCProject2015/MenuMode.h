#pragma once
#include "LessonX.h"

namespace Menu {
    extern CStaticSprite adventure;	    // ð��ģʽ
    extern CStaticSprite mini;			// ������Ϸ
    extern CStaticSprite edu;			// ����ģʽ

    void		OnMouseMove(const float fMouseX, const float fMouseY);
    void		OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
    void		OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
    void		OnKeyUp(const int iKey);
    void		OnSpriteColSprite(const char* szSrcName, const char* szTarName);
    void		OnSpriteColWorldLimit(const char* szName, const int iColSide);
};
