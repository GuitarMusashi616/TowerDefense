#include "Towers.h"

bool Towers::findTower(const sf::Vector2i & position, int &iteratorValue) const
{
	for (auto i = 0; i < size(); i++) {
		auto towerBounds = this->at(i)->getGlobalBounds();
		if (towerBounds.left <= position.x && (towerBounds.left + towerBounds.width) >= position.x) {
			if (towerBounds.top <= position.y && (towerBounds.top + towerBounds.height) >= position.y) {
				iteratorValue = i;
				return true;
			}
		}
	}
	return false;
}

bool Towers::findTowerByPointer(const std::shared_ptr<Tower> & tower, int & iteratorValue) const {
    for (auto i = 0; i < size(); i++) {
        if(this->at(i) == tower) {
            iteratorValue = i;
            return true;
        }
    }
        return false;
}

void Towers::deleteTower(const int iteratorValue)
{
	this->at(iteratorValue).reset();
    
	erase(begin() + iteratorValue);
}
