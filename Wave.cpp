#include "Wave.h"

void Wave::killBox(int centerX, int centerY, int width, int height)
{
	//lowers health of all mobs in a rectangle
	int mobX, mobY, halfWidth, halfHeight;
	for (auto &mob : *this) {
		mobX = mob->getPosition().x;
		mobY = mob->getPosition().y;
		halfWidth = width / 2;
		halfHeight = height / 2;

		if ((centerX - halfWidth) <= mobX && mobX <= (centerX + halfWidth)) {
			if ((centerY - halfHeight) <= mobY && mobY <= (centerY + halfHeight)) {
				mob->setHealth(mob->getHealth() - 1);
			}
		}
	}
}

bool Wave::detectBox(int centerX, int centerY, int width, int height)
{
	int mobX, mobY, halfWidth, halfHeight;
	for (auto &mob : *this) {
		mobX = mob->getPosition().x;
		mobY = mob->getPosition().y;
		halfWidth = width / 2;
		halfHeight = height / 2;

		if ((centerX - halfWidth) <= mobX && mobX <= (centerX + halfWidth)) {
			if ((centerY - halfHeight) <= mobY && mobY <= (centerY + halfHeight)) {
				return true;
			}
		}
	}
	return false;
}

void Wave::killCircle(double centerX, double centerY, int radius)
{
	//lowers health of all mobs in a circle
	double mobX, mobY;

	for (auto &mob : *this) {
		mobX = mob->getPosition().x;
		mobY = mob->getPosition().y;

		if (std::sqrt(std::pow(mobX - centerX, 2.) + pow(mobY - centerY, 2.)) <= radius) {
			mob->setHealth(mob->getHealth() - 1);
		}
	}
}


