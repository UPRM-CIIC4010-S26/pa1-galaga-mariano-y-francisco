#include "Program.hpp"

Program::Program() {
    score = 0;
    Background::sideWalls = std::pair<HitBox, HitBox>{ 
        HitBox(0, 0, 10, GetScreenHeight()), 
        HitBox(GetScreenWidth() - 10, 0, 10, GetScreenHeight())
    };

    Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{350, 150}, 
            new SpEnemy(350, 150)
        });

    Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{600, 150}, 
            new SpEnemy(600, 150)
        });

    for (int i = 0; i < 30; i++) {
        float x = 250 + 50 * (i % 10);
        float y = 200 + 50 * (i / 10);

        Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{x, y}, 
            new StdEnemy(x, y)
        });
    }
}

void Program::Update() {
    for (Animation& a : Animation::animations) a.update();
    for (int i = 0; i < Animation::animations.size(); i++) {
        if (Animation::animations[i].done) Animation::animations.erase(Animation::animations.begin() + i);
    }
    pauseFrames = std::max(pauseFrames - 1, 0);

    if (!startup && !paused && !gameOver && pauseFrames <= 0) {
        switch (GetRandomValue(0, playerCount-1)) {
        case 0:
            Enemy::ManageEnemies(player->hitBox);
            break;
        case 1:
        Enemy::ManageEnemies(player2->hitBox);
        break;
        }
        StdEnemy::attackReset();
        ManageEnemyRespawns();
        player->update();
        if (playerCount > 1) player2->update();

        for (std::pair<std::pair<float, float>, Enemy*> p : Enemy::enemies) {
            if (p.second && HitBox::Collision(player->hitBox, p.second->hitBox) && player->getIframes() <= 0) {
                Animation::animations.push_back(
                    Animation(player->position.first, player->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                if(playerCount == 1)Projectile::projectiles.clear();
                if(playerCount == 1)player->position.first = GetScreenWidth() / 2 - 15;
                p.second->health = 0;
                if(playerCount == 1) pauseFrames = 120;
                if (lives > 1) {
                    player->setMissiles(std::max(player->getMissiles(), 2));
                    player->setShield(3);
                }
                player->setIframes(60);
                lives--;
            }
            if(playerCount > 1) if (p.second && HitBox::Collision(player2->hitBox, p.second->hitBox)&& player2->getIframes()<=0) {
                Animation::animations.push_back(
                    Animation(player2->position.first, player2->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                p.second->health = 0;
                if (lives2 > 1) {
                    player2->setMissiles(std::max(player2->getMissiles(), 2));
                    player2->setShield(3);
                }
                player2->setIframes(60);
                lives2--;
            }
        }

        for (Projectile& p : Projectile::projectiles) { 
            if (HitBox::Collision(player->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player->getIframes()<=0) {
                PlayerReset(1);
            }
            if (playerCount > 1) if (HitBox::Collision(player2->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player2->getIframes()<=0) {
                PlayerReset(2);
            }
            p.update(); 
        }
        for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) 
        if (p.second && p.second->health <= 0) {
            score += p.second->scoreValue;
            p.second = nullptr;
        }
        if (playerCount >1) if ((lives <= 0 && lives2 <= 0) && pauseFrames <= 0) gameOver = true;
        if(playerCount == 1) if (lives <= 0 && pauseFrames <= 0) gameOver = true;
        Projectile::CleanProjectiles();
        Projectile::ProjectileCollision();
        if (playerCount >1){
        if (lives <= 0) player->setDisabled(true);
        if (lives2 <= 0) player2->setDisabled(true);
        if (lives > 0&&player->isDisabled()) player->setDisabled(false),player->setIframes(300),player->position.first = (GetScreenWidth() / 2) - 15, player->position.second = GetScreenHeight() * 0.75f;
        if (lives2 > 0&&player2->isDisabled()) player2->setDisabled(false),player2->setIframes(300),player2->position.first = (GetScreenWidth() / 2) - 60, player2->position.second = GetScreenHeight() * 0.75f;
        }

        if (score >= newlive) {
            if (lives < 5){
                lives++;
            }
            if (lives2 < 5 && playerCount > 1){
                lives2++;
            }
            newlive += (1000*playerCount);
        }
    }
}


void Program::Draw() {
    background.Draw();
    if (pauseFrames <= 0 && !gameOver) player->draw();
    if (pauseFrames <= 0 && !gameOver && playerCount > 1) player2->draw();
    for (Animation& a : Animation::animations) a.draw();
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 90.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
                Rectangle{10.0f, GetScreenHeight() - 107.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 121.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
    for (int i = 0; i < lives; i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 0, 17, 18}, 
            Rectangle{10.0f + i * 30, GetScreenHeight() - 30.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }
    for (int i = 0; i < player->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{37, 54, 15, 20}, 
               Rectangle{0.0f + i * 20, GetScreenHeight() - 70.0f, 30, 40}, 
               Vector2{0, 0}, 0, WHITE);
    }
        for (int i = 0; i < player->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 65, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 90.0f, 20, 20}, 
                Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 58, 6, 7}, 
                Rectangle{10.0f, GetScreenHeight() - 107.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 53, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 121.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }    
    }
    if (playerCount > 1) {
        for (int i = 0; i < player2->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{37, 54, 15, 20}, 
               Rectangle{GetScreenWidth() - 35.0f - i * 20, GetScreenHeight() - 70.0f, 30, 40}, 
               Vector2{0, 0}, 0, WHITE);}
    for (int i = 0; i < lives2; i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 18, 17, 18}, 
            Rectangle{GetScreenWidth()-30.0f - i * 30, GetScreenHeight() - 30.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }
    for (int i = 0; i < player2->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 65, 6, 6}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 90.0f, 20, 20}, 
                Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 58, 6, 7}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 107.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 53, 6, 6}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 121.0f, 20, 20},
                Vector2{0, 0}, 0, WHITE);
            }
        }                
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
                Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 90.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
                Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 107.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
                Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 121.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                }
    





    for (Projectile p : Projectile::projectiles) p.draw();
    for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) if (p.second) p.second->draw();
    if (!gameOver) DrawText(TextFormat("Score: %i", score), 10, 10, 24, WHITE);

    if (startup) DrawStartup();
    if (paused) DrawPauseScreen();
    if (gameOver) DrawGameOver();
}

        
void Program::ManageEnemyRespawns() {
    delay = std::max(delay - 1, 0);
    int difficulty = std::max(std::min(score / 1000, 5), 2);
    respawnCooldown -= difficulty;
    if (respawnCooldown <= 0) {
        respawnCooldown = 900;
        for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) {
            if (!p.second && p.first.second != 150) {
                int eType = GetRandomValue(1, 3);

                if (eType == 1) {
                    p.second = new StEnemy(GetScreenWidth() / 2 - 15, 0, true);
                } else {
                    if (difficulty >= 5) p.second = new StdEnemy(GetScreenWidth() / 2 - 15, 0, true, 1);
                    else p.second = new StdEnemy(GetScreenWidth() / 2 - 15, 0, true);
                    respawnCooldown /= 2;
                }

                respawns++;
                break;
            } else if (!p.second && p.first.second == 150) {
                p.second = new SpEnemy(GetScreenWidth() / 2 - 15, 0, true);
                respawns++;
                break;
            }
        }
    }

    if(respawns >= 4) {
        count = GetRandomValue(4, 6);
        respawns = 0;
    }

    if (count > 0 && delay <= 0) {
        Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{0, 0}, 
            new DyEnemy(GetScreenWidth(), 300)
        });

        count--;
        delay = 30;
    }
}

void Program::DrawStartup() {
    DrawRectangle(0, 0, (float)GetScreenWidth(), (float)GetScreenHeight(), Color{0, 0, 0, 125});
    DrawText("Galaga", (GetScreenWidth() / 2 - 237), 75, 144, WHITE);
    DrawText("Press Enter", (GetScreenWidth() / 2) - 75, GetScreenHeight() / 2, 24, GRAY);
    DrawText("Move: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() / 2 -120, 30, WHITE);
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{98, 53, 16, 19}, // A button
                Rectangle{(GetScreenWidth() / 2) - 310.0f, (GetScreenHeight() / 2) - 135.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE); 
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{115, 53, 16, 19}, // D button
                Rectangle{(GetScreenWidth() / 2) - 255.0f, (GetScreenHeight() / 2) - 135.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Missiles: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() / 2 - 50, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{132, 53, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 270.0f, (GetScreenHeight() / 2) - 65.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Shield: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() / 2 + 20, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{149, 53, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 300.0f, (GetScreenHeight() / 2) + 5.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Shoot: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() / 2 + 90, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{166, 53, 80, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 300.0f, (GetScreenHeight() / 2) + 75.0f, 250, 59}, 
                Vector2{0, 0}, 0, WHITE);
}

void Program::PlayerSelectScreen(){
    DrawText("Galaga", (GetScreenWidth() / 2 - 237), 75, 144, WHITE);
    DrawText("Select Player Count", (GetScreenWidth() / 2) - 200, 400, 48, WHITE);
    DrawText("Press 1 for Single Player", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 20, 24, WHITE);
    DrawText("Press 2 for Two Players", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 20, 24, RED);
}

void Program::DrawPauseScreen() {
    DrawRectangle(0, 0, (float)GetScreenWidth(), (float)GetScreenHeight(), Color{0, 0, 0, 125});
    DrawText("Paused", (GetScreenWidth() / 2) - 85, GetScreenHeight() / 2 - 60, 48, WHITE);
    DrawText("Press Enter", (GetScreenWidth() / 2) - 75, GetScreenHeight() / 2, 24, GRAY);
}

void Program::DrawGameOver() {
    DrawRectangle(0, 0, (float)GetScreenWidth(), (float)GetScreenHeight(), Color{0, 0, 0, 125});
    DrawText("Game Over", (GetScreenWidth() / 2) - 380, 50, 144, WHITE);
    DrawText("Press Enter", (GetScreenWidth() / 2) - 75, GetScreenHeight() / 2, 24, GRAY);
    DrawText(TextFormat("Final Score: %i", score), (GetScreenWidth() / 2) - 100, GetScreenHeight() / 2 + 40, 40, WHITE);
}

void Program::KeyInputs() {
    if ((!gameOver && !startup && IsKeyPressed('P')) || (paused && IsKeyPressed(KEY_ENTER))) paused = !paused;
    if (!paused && !startup && IsKeyPressed('B')) gameOver = !gameOver;
    if (!gameOver && !paused && IsKeyPressed('V')) startup = !startup;
    if (IsKeyPressed('M')) HitBox::drawHitbox = !HitBox::drawHitbox;
    if (IsKeyPressed('G')) {
        score += 500;
        std::cout << "Score increased by 500. Current score: " << score << std::endl;
    }
    if (IsKeyPressed('N')) {
        player->setMissiles(player->getMissiles() + 1);
        std::cout << "Missile added. Current missiles: " << player->getMissiles() << std::endl;
        if (playerCount>1) player2->setMissiles(player2->getMissiles() + 1);
        std::cout << "Missile added. Current missiles: " << player2->getMissiles() << std::endl;
    }
    if (gameOver && IsKeyPressed(KEY_ENTER)) {
        gameOver = false;
        Projectile::projectiles.clear();
        Reset();
    }

    if (startup && IsKeyPressed(KEY_ENTER)) {
        startup = false;
    }

    if (!startup && !paused && !gameOver && pauseFrames <= 0) player->keyInputs(), player2->keyInputs();
   
}

void Program::PlayerReset(int identifier) {
    switch (identifier) {
        case 1:
    Animation::animations.push_back(
        Animation(player->position.first, player->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet));
    break;
        case 2:
    Animation::animations.push_back(
        Animation(player2->position.first, player2->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet));
    break;
}
    PlaySound(SoundManager::gameOver);
    if(playerCount == 1) Projectile::projectiles.clear();
    switch (identifier) {
        case 1:
    if(playerCount == 1)player->position.first = GetScreenWidth() / 2 - 15;
    if(playerCount == 1)pauseFrames = 120;
    if (lives > 1) {
        player->setMissiles(std::max(player->getMissiles(), 2));
        player->setShield(3);
    }
    lives--;
    player->setIframes(60);
    break;
        case 2:
    if (lives2 > 1) {
        player2->setMissiles(std::max(player2->getMissiles(), 2));
        player2->setShield(3);
    }
    player2->setIframes(60);
    lives2--;
    break;
}
}

void Program::Reset() {
    Enemy::enemies.clear();
    StdEnemy::attackInProgress = false;
    player = new Player((GetScreenWidth() / 2) - 15, GetScreenHeight() * 0.75f, 1);
    if (maxPlayerCount > 1) player2 = new Player((GetScreenWidth() / 2) - 60, GetScreenHeight() * 0.75f, 2);
    score = 0;
    respawnCooldown = 1080;
    respawns = 0;
    count = 0;
    delay = 0;
    lives = 3;
    lives2 = 3;
    newlive = 1000;
    Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{350, 150}, 
            new SpEnemy(350, 150)
        });

    Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
            std::pair<float, float>{600, 150}, 
            new SpEnemy(600, 150)
        });
        
    for (int i = 0; i < 30; i++) {
        float x = 250 + 50 * (i % 10);
        float y = 200 + 50 * (i / 10);

        Enemy::enemies.push_back(std::pair<std::pair<float, float>, Enemy*> {
        std::pair<float, float>{x, y}, 
        new StdEnemy(x, y)
        });
    }
}