#pragma once
#include <cassert>

enum Color
{
	Black = 0,
	White = 1,
	Empty = -1
};

inline Color operator!(Color& color)
{
	if (color == Black)
		return White;
	else if (color == White)
		return Black;
	else
		return Empty;
}