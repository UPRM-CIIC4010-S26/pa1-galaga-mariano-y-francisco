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
        Player* player3;
        Player* player4;
        int respawnCooldown = 1080;
        int respawns = 0;
        int count = 0;
        int delay = 0;
        bool players1 = false;
        bool players2 = false;
        bool players3 = false;
        bool players4 = false;
        int difficultyTweak = 0;


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
                    if (!players1) players1 = true;
                    break;
                case 2:
                    this->player2 = newPlayer;
                    if (!players2) players2 = true;
                    break;
                case 3:
                    this->player3 = newPlayer;
                    if (!players3) players3 = true;
                    break;
                case 4:
                    this->player4 = newPlayer;
                    if (!players4) players4 = true;
                    break;
            }
            if(players2) difficultyTweak = 2;
            if(players3) difficultyTweak = 3;
            if(players4) difficultyTweak = 4;
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