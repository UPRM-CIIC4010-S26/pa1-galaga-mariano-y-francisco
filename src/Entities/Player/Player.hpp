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
        int shieldCooldown = 150;
        int shieldCharge = 3;
        int Iframes = 0;
        int playerNumber = 1;
        bool disabled = false;
        int lives = 3;

    public:
        std::pair<float, float> position;
        HitBox hitBox;

        Player(float x, float y, int playerNum) {
            this->position.first = x;
            this->position.second = y;
            this->playerNumber = playerNum;
            this->hitBox = HitBox(x, y, 30, 30);
        }
        int getIframes() { return Iframes; }
        void setIframes(int frames) { Iframes = frames; }
        int getMissiles() { return missileCount; }
        void setMissiles(int count) { missileCount = count; }
        int getShield() { return shieldCharge;}
        void setShield(int charge) { shieldCharge = charge; }
        bool isDisabled() { return disabled; }
        void setDisabled(bool disable) { disabled = disable;}
        int getLives() {return lives;}
        void setLives(int life) {this->lives = life;}

        void draw();
        void update();
        void keyInputs();
        void attack();
        void missileAttack();
        void useShield();
};