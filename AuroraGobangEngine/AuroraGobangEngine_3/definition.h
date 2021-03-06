#pragma once
#include <stack>
#include <vector>

#define RANGE 15

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : (-(x)))

#define COLOR(color) (color == BLACK ? "Black" : "White")
#define COLOR_WIN(color) (color == BLACK ? "BlackWin" : "WhiteWin")

enum Color
{
	BLACK = 0,
	WHITE = 1,
	EMPTY = -1
};

inline Color operator!(Color &color)
{
	if		(color == BLACK)	return WHITE;
	else if (color == WHITE)	return BLACK;
	else						return EMPTY;
}

enum Orientation
{
	ROW		= 0,
	COLUMN	= 1,
	LEFT	= 2,
	RIGHT	= 3
};

class Axis
{
public:
	int				row;
	int				column;
	int				axis;

	Axis(int _row, int _column)
		: row(_row)
		, column(_column)
		, axis(_row * 100 + _column)
	{
	}
};

class Boundary
{
	typedef std::stack<int> Container;
private:
	Container					up;
	Container					down;
	Container					left;
	Container					right;
public:
	Boundary() = default;
	void change_boundary(Axis axis)
	{
		if (up.size() != 0)
		{
			up.push(MIN(axis.row, up.top()));
			down.push(MAX(axis.row, down.top()));
			left.push(MIN(axis.column, left.top()));
			right.push(MAX(axis.column, right.top()));
		}
		else
		{
			up.push(axis.row);
			down.push(axis.row);
			left.push(axis.column);
			right.push(axis.column);
		}
	}

	void undo_change_boundary()
	{
		up.pop();
		down.pop();
		left.pop();
		right.pop();
	}

	int GetLeft()		{ return MAX(left.top() - 2, 0); }
	int GetUp()		{ return MAX(up.top() - 2, 0); }
	int GetRight()		{ return MIN(right.top() + 2, RANGE - 1); }
	int GetDown()		{ return MIN(down.top() + 2, RANGE - 1); }

	std::vector<Axis> GetRangeAxis()
	{
		std::vector<Axis> all_axis;
		for (int row = GetUp(); row < GetDown(); row++)
			for (int column = GetLeft(); column < GetRight(); column++)
				all_axis.push_back(Axis(row, column));
		return all_axis;
	}
};

