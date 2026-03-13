#include "Player.hpp"

void Player::draw() {
    if (disabled) return;
    if (HitBox::drawHitbox) this->hitBox.draw();
    switch (playerNumber) {
        case 1:
            if (!(Iframes %4 ==0 && Iframes > 0)){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 0, 17, 18}, 
                           Rectangle{this->position.first, this->position.second, 30, 30}, 
                           Vector2{0, 0}, 0, WHITE);
            }
            break;
        case 2:
        if (!(Iframes %4 ==0 && Iframes > 0)){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 18, 17, 18}, 
                           Rectangle{this->position.first, this->position.second, 30, 30}, 
                           Vector2{0, 0}, 0, WHITE);
            }
            break;
        case 3:
        if (!(Iframes %4 ==0 && Iframes > 0)){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{216, 91, 17, 18}, 
                           Rectangle{this->position.first, this->position.second, 30, 30}, 
                           Vector2{0, 0}, 0, WHITE);
            }
            break;
        case 4:
        if (!(Iframes %4 ==0 && Iframes > 0)){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{234, 91, 17, 18}, 
                           Rectangle{this->position.first, this->position.second, 30, 30}, 
                           Vector2{0, 0}, 0, WHITE);
            }
            break;
        }
}


void Player::update() {
    if (disabled) return;
    this->hitBox.box.x = this->position.first;
    this->hitBox.box.y = this->position.second;
    this->cooldown--;
    this->missileCooldown--;
    this->missileRegen--;
    this->shieldCooldown--;
    this->Iframes--;

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
    if (disabled) return;
    switch (playerNumber){
        case 1:
            if (IsKeyDown('Q')||IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
            if (IsKeyDown('E')||IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
            if (IsKeyDown(KEY_SPACE)) this->attack();
            if (IsKeyPressed('R')||IsKeyPressed(KEY_UP)) this->missileAttack();
            if (IsKeyPressed('W')||IsKeyPressed(KEY_DOWN)) this->useShield();
            break;
        case 2:
            if (IsKeyDown('I')||IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
            if (IsKeyDown('P')||IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
            if (IsKeyDown(KEY_SPACE)) this->attack();
            if (IsKeyPressed('U')||IsKeyPressed(KEY_UP)) this->missileAttack();
            if (IsKeyPressed('O')||IsKeyPressed(KEY_DOWN)) this->useShield();
            break;
        case 3:
            if (IsKeyDown('Z')||IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
            if (IsKeyDown('C')||IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
            if (IsKeyDown(KEY_SPACE)) this->attack();
            if (IsKeyPressed('V')||IsKeyPressed(KEY_UP)) this->missileAttack();
            if (IsKeyPressed('X')||IsKeyPressed(KEY_DOWN)) this->useShield();
            break;
        case 4:
            if (IsKeyDown(',')||IsKeyDown(KEY_LEFT)) this->position.first -= this->speed;
            if (IsKeyDown('/')||IsKeyDown(KEY_RIGHT)) this->position.first += this->speed;
            if (IsKeyDown(KEY_SPACE)) this->attack();
            if (IsKeyPressed('M')||IsKeyPressed(KEY_UP)) this->missileAttack();
            if (IsKeyPressed('.')||IsKeyPressed(KEY_DOWN)) this->useShield();
            break;
    }
}


void Player::attack() {
    if (disabled) return;
    if (cooldown <= 0) {
        Projectile::projectiles.push_back(Projectile(position.first + + this->hitBox.box.width / 2, position.second, 0));
        PlaySound(SoundManager::shoot);
        cooldown = 30;
    }
}

void Player::missileAttack(){
    if (disabled) return;
    if (missileCooldown <= 0 && missileCount > 0) {
        Projectile::projectiles.push_back(Projectile(position.first + +(missileTube*20), position.second, 10, 20, 2,playerNumber));
        PlaySound(SoundManager::missileLaunch);
        missileCooldown = 15;
        missileCount--;
        missileTube = (missileTube + 1) % 2;
    }
}

void Player::useShield() {
    if (disabled) return;
    if (shieldCharge >= 3) {
        Projectile::projectiles.push_back(Projectile(position.first-this->hitBox.box.width/2, position.second-10, 60, 10, 4,playerNumber));
        PlaySound(SoundManager::shieldDeploy);
        shieldCooldown = 50;
        shieldCharge = 0;
    }
}