#pragma once
#include "raylib-cpp/raylib-cpp.hpp"

class ImageManager {
    public:
        inline static Texture2D SpriteSheet;

        static void Load(int alt) {
            switch(alt){
                case 1:
                SpriteSheet = LoadTextureFromImage(LoadImage("images/Arcade - Galaga - Miscellaneous - General Sprites 7.png"));
                break;
                case 2:
                SpriteSheet = LoadTextureFromImage(LoadImage("images/Arcade - Galaga - Miscellaneous - General Sprites 7alt.png"));
                break;
            }
        }

        static void Unload() {
            UnloadTexture(SpriteSheet);
        }
};