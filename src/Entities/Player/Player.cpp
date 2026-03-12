#include "Player.hpp"

void Player::draw() {
    if (HitBox::drawHitbox) this->hitBox.draw();
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 0, 17, 18}, 
                   Rectangle{this->position.first, this->position.second, 30, 30}, 
                   Vector2{0, 0}, 0, WHITE);
}

void Player::update() {
    this->hitBox.box.x = this->position.first;
    this->hitBox.box.y = this->position.second;
    this->cooldown--;
    this->missileCooldown--;
    this->missileRegen--;
    this->shieldCooldown--;

    if (shieldCooldown <= 0 && shieldCharge < 3) {
        shieldCharge++;
        shieldCooldown = 50;
    }

    if (missileRegen <= 0) {
        if (missileCount < 5) missileCount++;
        missileRegen = 600;
    }

    if (HitBox::Collision(Background::sideWalls.first, this->hitBox)) {
        std::pair<double, double> collision = HitBox::CollisionMargins(this->hitBox, Background::sideWalls.first);
        if (abs(collision.second) < abs(collision.first)) {
            this->position.second += collision.second;
        } else {
            this->position.first += collision.first + 1;
        }
    }
    if (HitBox::Collision(Background::sideWalls.second, this->hitBox)) {
        std::pair<double, double> collision = HitBox::CollisionMargins(this->hitBox, Background::sideWalls.second);
        if (abs(collision.second) < abs(collision.first)) {
            this->position.second += collision.second;
        } else {
            this->position.first += collision.first + 1;
        }
    }
}

void Player::keyInputs() {
    if (IsKeyDown('A')||IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
    if (IsKeyDown('D')||IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
    if (IsKeyPressed(KEY_SPACE)) this->attack();
    if (IsKeyPressed('E')) this->missileAttack();
    if (IsKeyPressed('Q')) this->useShield();
}

void Player::attack() {
    if (cooldown <= 0) {
        Projectile::projectiles.push_back(Projectile(position.first + + this->hitBox.box.width / 2, position.second, 0));
        PlaySound(SoundManager::shoot);
        cooldown = 30;
    }
}

void Player::missileAttack(){
    if (missileCooldown <= 0 && missileCount > 0) {
        Projectile::projectiles.push_back(Projectile(position.first + +(missileTube*20), position.second, 10, 20, 2));
        PlaySound(SoundManager::missileLaunch);
        missileCooldown = 15;
        missileCount--;
        missileTube = (missileTube + 1) % 2;
    }
}

void Player::useShield() {
    if (shieldCharge >= 3) {
        Projectile::projectiles.push_back(Projectile(position.first-this->hitBox.box.width/2, position.second-10, 60, 10, 4));
        PlaySound(SoundManager::shieldDeploy);
        shieldCooldown = 50;
        shieldCharge = 0;
    }
}