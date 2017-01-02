#pragma once
#include "stdafx.h"

struct CharPos
{
	float x;
	float y;
	float z;
};
struct Player
{
	float mid_from_bottom;
	float mid_size;
	float leg_size;
	float foot_size;
	float leg_term;
	float original_mid;
	float head_size;
	float arm_size;
	float noze_size;
	float eye_size;
	float beard_size;
	float mouse_size;
};

enum STATE { IDLE = 0, RUN = 1, JUMP = 2, DIE_BRICK = 3, DIE_MUSH = 4 };

class Character
{
private:
	Player player;
	int char_state = 0;
	int rotate_angle = 0;

	int rotate_arm = 45;
	bool arm_right = true;
	bool arm_left = false;

	int rotate_leg = 45;
	bool leg_right = true;
	bool leg_left = false;

	CharPos m_char_pos{ 0,0 ,0 };
public:
	Character();
	void update_character(int state);
	void make_character();
	CharPos Get_CharPos() const;
	void Set_CharPos(float m_x, float m_y, float m_z);
	~Character();
};

