#include "Projectile.hpp"

void Projectile::draw() {
    if (HitBox::drawHitbox) this->hitBox.draw();
    if (ID == 0 ||ID == 1){
        DrawRectangleGradientV(this->position.first, this->position.second, 2, 5, (ID == 1) ? WHITE : YELLOW, (ID == 1) ? YELLOW : WHITE);
    }
    if (ID == 2) {
        switch (variant){
        case 1: 
            missile1();
            break;
        case 2:
            missile2();
            break;
        case 3:
            missile3();
            break;
        case 4:
            missile4();
            break;
        }

    }
    if (ID == 3) {
        DrawRectangle(this->position.first, this->position.second, 4, 4, RED);
    }
    if (ID == 4) {
        switch(variant){
            case 1:
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{75, 40, 25, 6}, 
                Rectangle{this->position.first, this->position.second, 60, 15}, 
                Vector2{0, 0}, 0, WHITE);
                break;
            case 2:
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{102, 40, 25, 6}, 
                Rectangle{this->position.first, this->position.second, 60, 15}, 
                Vector2{0, 0}, 0, WHITE);
                break;
            case 3:
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{156, 40, 25, 6}, 
                Rectangle{this->position.first, this->position.second, 60   , 15}, 
                Vector2{0, 0}, 0, WHITE);
                break;
            case 4:
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{129, 40, 25, 6}, 
                Rectangle{this->position.first, this->position.second, 60, 15}, 
                Vector2{0, 0}, 0, WHITE);
                break;
            }
    }
}

void Projectile::update() {
    this->hitBox.box.x = this->position.first;
    this->hitBox.box.y = this->position.second;

    if (ID == 0) { // Player bullet
        this->position.first += this->speed * cos(this->angle * M_PI / 180);
        this->position.second -= this->speed * sin(this->angle * M_PI / 180);
    }

    if (ID == 1) { // Enemy bullet
        this->position.first += this->speed * cos(this->angle * M_PI / 180);
        this->position.second += this->speed * sin(this->angle * M_PI / 180);
    }

    if (ID == 2) { // Missile
        timeout++;
        if(timeout <=7) {
            this->position.first += (this->speed+7-timeout) * cos(this->angle * M_PI / 180);
            this->position.second -= (this->speed+7-timeout) * sin(this->angle * M_PI / 180);
        }
        
        
        else if (timeout <= 20) {
            this->position.first += (this->speed-5) * cos(this->angle * M_PI / 180);
            this->position.second -= (this->speed-5) * sin(this->angle * M_PI / 180);
        }
        else{
            this->position.first += (this->speed+3) * cos(this->angle * M_PI / 180);
            this->position.second -= (this->speed+3) * sin(this->angle * M_PI / 180);
        }
    }

    if (ID == 3) { // Shrapnel
        this->position.first += this->speed * cos(this->angle * M_PI / 180);
        this->position.second += this->speed * sin(this->angle * M_PI / 180);
        timeout ++;
        if (timeout >= 30) {
            this->del = true;
        }
        
    }

    if (ID == 4) { // Shield
        timeout++;
        if (timeout <= 15) {
            this->position.first += (this->speed-2) * cos(this->angle * M_PI / 180);
            this->position.second -= (this->speed-2) * sin(this->angle * M_PI / 180);
        }
        if (timeout >= 30) {
            this->del = true;
        }
    }

    if (this->position.second > GetScreenHeight() || this->position.second < 0) this->del = true;
}

void Projectile::CleanProjectiles() {
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].del) {
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

void Projectile::ProjectileCollision() {
    for (int i = 0; i < projectiles.size(); i++) {
        for (int j = i + 1; j < projectiles.size(); j++) {
            if (HitBox::Collision(projectiles[i].getHitBox(), projectiles[j].getHitBox()) && projectiles[i].ID != projectiles[j].ID) {
                projectiles[i].del = projectiles[i].ID != 2 && projectiles[i].ID != 4;
                projectiles[j].del = projectiles[j].ID != 2 && projectiles[j].ID != 4;
            }
        }
        
    }
}