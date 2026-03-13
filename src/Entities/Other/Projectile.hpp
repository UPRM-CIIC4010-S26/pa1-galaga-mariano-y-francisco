#pragma once
#define _USE_MATH_DEFINES
#include "Hitbox.hpp"
#include "SoundManager.hpp"
#include "ImageManager.hpp"

class Projectile {
    protected:
        std::pair<float, float> position = std::pair<float, float>(0, 0);
        HitBox hitBox = HitBox();
        float angle = 90;
        int speed = 6;
        int timeout = 0;
        int variant = 1;
    public: 
        bool del = false;
        int ID;
        inline static std::vector<Projectile> projectiles;

        Projectile(float x, float y, int ID) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, 2, 5);
            this->ID = ID;
        }

        Projectile(float x, float y, float angle, int ID) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, 2, 5);
            this->angle = angle;
            this->ID = ID;
        }

        Projectile(float x, float y, float size_x, float size_y, int ID) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, size_x, size_y);
            this->ID = ID;
        }

        Projectile(float x, float y, float size_x, float size_y, int ID , int variant) {
            this->position.first = x;
            this->position.second = y;
            this->hitBox = HitBox(x, y, size_x, size_y);
            this->ID = ID;
            this->variant = variant;
        }

        HitBox getHitBox() { return hitBox; }
        std::pair<double, double> getPosition() { return position; }
        void missile1(){
            if(timeout <=20) {
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{54, 59, 5, 10}, 
                Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        else switch (timeout%6){
            case 0:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{61, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 1:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{61, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 2:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{68, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 3:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{68, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 4:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{75, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
            case 5:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{75, 59, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
        }
        }
        void missile2(){
            if(timeout <=20) {
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{189, 78, 5, 10}, 
                Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        else switch (timeout%6){
            case 0:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{196, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 1:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{196, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 2:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 3:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 4:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
            case 5:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 78, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
        }
    }
        void missile3(){
        if(timeout <=20) {
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{189, 94, 5, 10}, 
                Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        else switch (timeout%6){
            case 0:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{196, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 1:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{196, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 2:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 3:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 4:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
            case 5:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{203, 94, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
        }}
        void missile4(){
        if(timeout <=20) {
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{230, 79, 5, 10}, 
                Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        else switch (timeout%6){
            case 0:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{237, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 1:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{237, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 2:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{244, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 3:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{244, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                   break;
            case 4:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{251, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
            case 5:
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{251, 79, 5, 10}, 
                   Rectangle{this->position.first, this->position.second+8, 10, 20}, 
                   Vector2{0, 0}, 0, WHITE);
                break;
        }}
        void draw();
        void update();
        static void CleanProjectiles();
        static void ProjectileCollision();

};
