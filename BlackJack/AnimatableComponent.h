#pragma once
#include <SDL.h>
class AnimatableComponent
{
private:
	PositionComponent *position;
	int entity;
	int index;

public:

	AnimatableComponent(PositionComponent *position) { this->position = position; }

	void dealerUpdate()
	{
		if (position->getX() != 850 + (50 * index))
		{
			double x = (850 + (50 * index) - position->getX());
			double y = (50 - position->getY());

			double normalX = (x / (sqrt((x * x) + (y * y))));
			double normalY = (y / (sqrt((x * x) + (y * y))));
			if (normalX >= 0 && normalY >= 0)
			{
				position->setXvel(static_cast<int>(normalX * 15));
				position->setYvel(static_cast<int>(normalY * 15));
				return;
			}
		}
		if (position->getX() != 850 + (50 * index) || position->getY() != 50)
		{
			position->setX(850 + (50 * index));
			position->setY(50);
		}
		position->setXvel(0);
		position->setYvel(0);
	}
	void playerUpdate()
	{
		if (position->getX() != 850 + (50 * index) && position->getY() != 650)
		{
			double x = (850 + (50 * index) - position->getX());
			double y = (650 - position->getY()); 

			double normalX = (x / (sqrt((x * x) + (y * y))));
			double normalY = (y / (sqrt((x * x) + (y * y))));
			if (normalX >= 0 && normalY >= 0)
			{
				position->setXvel(static_cast<int>(normalX * 15));
				position->setYvel(static_cast<int>(normalY * 15));
				return;
			}
		}
		if (position->getX() != 850 + (50 * index) || position->getY() != 650)
		{
			position->setX(850 + (50 * index));
			position->setY(650);
		}
		position->setXvel(0);
		position->setYvel(0);
	}

	void update()
	{
		switch (entity)
		{
		case 0:
			dealerUpdate();
			break;
		case 1:
			playerUpdate();
			break;
		}
	}

	void setEntity(int entity) { this->entity = entity; }
	void setIndex(int index) { this->index = index; }
};
