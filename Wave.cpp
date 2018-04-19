#include "Wave.h"

void Wave::killBox(int centerX, int centerY, int width, int height)
{
	//Kills all mobs around a specified position
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
