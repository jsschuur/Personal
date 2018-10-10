#pragma once

class PositionComponent
{
private:
	int x;
	int y;
	int xVel;
	int yVel;
public:
	void init()
	{
		x = 50; //default no animation
		y = 50; //default no animation
		xVel = 0;
		yVel = 0;
	}

	void update()
	{
		x += xVel;
		y += yVel;
	}

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setXvel(int xVel) { this->xVel = xVel; }
	void setYvel(int yVel) { this->yVel = yVel; }

	void reset()
	{
		x = 50;
		y = 50;
		xVel = 0;
		yVel = 0;
	}

	int getX() { return x; }
	int getY() { return y; }
};