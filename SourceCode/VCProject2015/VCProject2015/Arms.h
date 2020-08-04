#pragma once
#include "PvZSprite.h"
// ��������
class Arms : public PvZSprite {
public:
    Arms(const char* sprite_name, int power);
    virtual void after_hit() = 0;
    virtual int get_power();
    const char* get_type() override;
protected:
    int power;
    static const char* type;
};


// �㶹 �̳�������
class Pea : public Arms
{
public:
    Pea(const char* arms_name);
    void after_hit() override;
};

// ��ը �̳�������
class Boom : public Arms
{
public:
    Boom(const char* arms_name);
    void after_hit() override;
};
