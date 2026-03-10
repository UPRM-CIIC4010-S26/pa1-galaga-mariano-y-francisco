#pragma once
#include "Enemy.hpp"

class DyEnemy : public Enemy {
    private: 
        float angle = 135;
        float aimAngle = 225;
        bool loop = false;

    public:
        DyEnemy(float x, float y) : Enemy(x, y) { 
            this->cooldown = GetRandomValue(90, 300);
            this->health = 1;
            this->scoreValue = 25; 
        }

        DyEnemy(float x, float y, bool newSpawn) : Enemy(x, y) {
            this->cooldown = GetRandomValue(90, 300);
            this->spawning = newSpawn;
            this->health = 1;
            this->scoreValue = 25;
        }

        void draw() override;
        void update(std::pair<float, float> pos, HitBox target) override;
        void attack(HitBox target) override;
};