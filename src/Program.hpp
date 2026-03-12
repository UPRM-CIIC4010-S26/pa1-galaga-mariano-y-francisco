#pragma once

#include <iostream>
#include <string>
#include "raylib-cpp/raylib-cpp.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "StdEnemy.hpp"
#include "SpEnemy.hpp"
#include "StEnemy.hpp"
#include "DyEnemy.hpp"
class Program {
    private:
        Background background = Background();
        Player* player;
        Player* player2;
        int respawnCooldown = 1080;
        int respawns = 0;
        int count = 0;
        int delay = 0;
        int lives = 3;
        int lives2 = 3;
        int playerCount = 0;
        int maxPlayerCount = 0;


        int pauseFrames = 0;
        int score = 0;
        int newlive = 0;
        bool startup = true;
        bool paused = false;
        bool gameOver = false;

    public:
        void addPlayer(Player* newPlayer, int identifier) {
            switch (identifier) {
                case 1:
                    this->player = newPlayer;
                    break;
                case 2:
                    this->player2 = newPlayer;
                    break;
            }
            playerCount++;
            maxPlayerCount++;
            newlive += 1000;
        }
        Program();
        
        void Update();
        void Draw();
        void ManageEnemyRespawns();
        void DrawStartup();
        void PlayerSelectScreen();
        void DrawPauseScreen();
        void DrawGameOver();
        void KeyInputs();
        void PlayerReset(int identifier );
        void Reset();
          
        ~Program() {}
};