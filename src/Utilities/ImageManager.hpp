#pragma once
#include "raylib-cpp/raylib-cpp.hpp"

class ImageManager {
    public:
        inline static Texture2D SpriteSheet;

        static void Load() {
            SpriteSheet = LoadTextureFromImage(LoadImage("images/Arcade - Galaga - Miscellaneous - General Sprites 5.png"));
        }

        static void Unload() {
            UnloadTexture(SpriteSheet);
        }
};