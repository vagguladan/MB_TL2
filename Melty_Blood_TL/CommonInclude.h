#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

#include "MBMath.h"
#include "framework.h"

#pragma comment(lib, "Msimg32.lib")


namespace MB::enums
{
	enum class eLayerType
	{
		BackGround,
		Player,
		Floor,
		Enemy,
		Monster,
		Effect,
		UI,
		End,
		HitBox,
		HitBox1P,
		HitBox2P,
		Wall,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		HitBoxCollider,
		Rigidbody,
		End,
	};

	enum class eDir
	{
		Right,
		Left,
		None,
	};

	enum class Saber_Attack
	{
		None,
		Stand_A,
		Stand_B,
		Stand_C,
		Sit_A,
		Sit_B,
		Sit_C,
		Jump_A,
		Jump_B,
		Jump_C
	};

}