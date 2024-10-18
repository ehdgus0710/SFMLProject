#pragma once

// std
#include<iostream>
#include <time.h>
#include <math.h>

// 자료구조
#include <unordered_map>
#include <cassert>

// SFML
#include <SFML/Graphics.hpp>


#include "SFML/System/Vector2.hpp"
#include "Singleton.h"


enum class KeyInput
{
	KeyUp,
	KeyDown,
	KeyPressed,
	KeyNone
};