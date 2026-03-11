#pragma once
#include "Hitbox.hpp"
#include "Projectile.hpp"
#include "Background.hpp"
#include "ImageManager.hpp"

class Player {
    private:
        int cooldown = 30;
        int speed = 3;
        int missileCount = 2;
        int missileRegen = 600;
        int missileCooldown = 15;
        int missileTube = 0;

    public:
        std::pair<float, float> position;
        HitBox hitBox;

        Player(float x, float y) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, 30, 30);
        }

        int getMissiles() { return missileCount; }
        void setMissiles(int count) { missileCount = count; }

        void draw();
        void update();
        void keyInputs();
        void attack();
        void missileAttack();
};