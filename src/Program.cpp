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

        Enemy::ManageEnemies(player->hitBox);
        StdEnemy::attackReset();
        ManageEnemyRespawns();
        player->update();
        if (players2) player2->update();
        if (players3) player3->update();
        if (players4) player4->update();

        for (std::pair<std::pair<float, float>, Enemy*> p : Enemy::enemies) {
            if (p.second && HitBox::Collision(player->hitBox, p.second->hitBox) && player->getIframes() <= 0) {
                Animation::animations.push_back(
                    Animation(player->position.first, player->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                if(!players2)Projectile::projectiles.clear();
                if(!players2)player->position.first = GetScreenWidth() / 2 - 15;
                p.second->health = 0;
                if(!players2) pauseFrames = 120;
                if (player->getLives() > 1) {
                    player->setMissiles(std::max(player->getMissiles(), 2));
                    player->setShield(3);
                }
                player->setIframes(60);
                player->setLives(player->getLives()-1);
            }
            if(players2) if (p.second && HitBox::Collision(player2->hitBox, p.second->hitBox)&& player2->getIframes()<=0) {
                Animation::animations.push_back(
                    Animation(player2->position.first, player2->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                p.second->health = 0;
                if (player2->getLives() > 1) {
                    player2->setMissiles(std::max(player2->getMissiles(), 2));
                    player2->setShield(3);
                }
                player2->setIframes(60);
                player2->setLives(player2->getLives()-1);
            if (players3) if (p.second && HitBox::Collision(player3->hitBox, p.second->hitBox)&& player3->getIframes()<=0) {
                Animation::animations.push_back(
                    Animation(player3->position.first, player3->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                p.second->health = 0;
                if (player3->getLives() > 1) {
                    player3->setMissiles(std::max(player3->getMissiles(), 2));
                    player3->setShield(3);
                }
                player3->setIframes(60);
                player3->setLives(player3->getLives()-1);
            }
            if (players4) if (p.second && HitBox::Collision(player4->hitBox, p.second->hitBox)&& player4->getIframes()<=0) {
                Animation::animations.push_back(
                    Animation(player4->position.first, player4->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet)
                );

                PlaySound(SoundManager::gameOver);
                p.second->health = 0;
                if (player4->getLives() > 1) {
                    player4->setMissiles(std::max(player4->getMissiles(), 2));
                    player4->setShield(3);
                }
                player4->setIframes(60);
                player4->setLives(player->getLives()-1);
            }
        }
        }

        for (Projectile& p : Projectile::projectiles) { 
            if (HitBox::Collision(player->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player->getIframes()<=0) {
                PlayerReset(1);
            }
            if (player2) if (HitBox::Collision(player2->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player2->getIframes()<=0) {
                PlayerReset(2);
            }
            if (players3) if (HitBox::Collision(player3->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player3->getIframes()<=0) {
                PlayerReset(3);
            }
            if (players4) if (HitBox::Collision(player4->hitBox, p.getHitBox()) && (p.ID == 1 || p.ID == 3) && player4->getIframes()<=0) {
                PlayerReset(4);
            }

            p.update();       
        }
        for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) 
        if (p.second && p.second->health <= 0) {
            score += p.second->scoreValue;
            p.second = nullptr;
        }
        if(players4) if ((player->getLives() <= 0 && player2->getLives() <= 0 && player3->getLives() <= 0 && player4->getLives() <= 0) && pauseFrames <= 0) gameOver = true;
        if(players3&&!players4) if ((player->getLives() <= 0 && player2->getLives() <= 0 && player3->getLives() <= 0) && pauseFrames <= 0) gameOver = true;
        if(players2&&!players3) if ((player->getLives() <= 0 && player2->getLives() <= 0) && pauseFrames <= 0) gameOver = true;
        if(!players2) if (player->getLives() <= 0 && pauseFrames <= 0) gameOver = true;
        Projectile::CleanProjectiles();
        Projectile::ProjectileCollision();
        if (players2){
        if (player->getLives() <= 0) player->setDisabled(true);
        if (players2) if ( player2->getLives()<= 0) player2->setDisabled(true);
        if (players3) if ( player3->getLives()<= 0) player3->setDisabled(true);
        if (players4) if ( player4->getLives()<= 0) player4->setDisabled(true);

        if (player->getLives() > 0 && player->isDisabled()) player->setDisabled(false),player->setIframes(300),player->position.first = (GetScreenWidth() / 2), player->position.second = GetScreenHeight() * 0.75f;
        if (players2) if (player2->getLives() > 0 &&player2->isDisabled()) player2->setDisabled(false),player2->setIframes(300),player2->position.first = (GetScreenWidth() / 2) - 60, player2->position.second = GetScreenHeight() * 0.75f;
        if (players3) if (player3->getLives() > 0 &&player3->isDisabled()) player3->setDisabled(false),player3->setIframes(300),player3->position.first = (GetScreenWidth() / 2) - 120, player3->position.second = GetScreenHeight() * 0.75f;
        if (players4) if (player4->getLives() > 0 &&player4->isDisabled()) player4->setDisabled(false),player4->setIframes(300),player4->position.first = (GetScreenWidth() / 2) - 180, player4->position.second = GetScreenHeight() * 0.75f;
    }

        if (score >= newlive) {
            if (player->getLives() < 5)player->setLives(player->getLives()+1);
            if (players2) if (player2->getLives() < 5)player2->setLives(player2->getLives()+1);
            if (players3) if (player3->getLives() < 5)player3->setLives(player3->getLives()+1);
            if (players4) if (player4->getLives() < 5)player4->setLives(player4->getLives()+1);
            newlive += (1000*difficultyTweak);
        }
    
}
}

void Program::Draw() {
    background.Draw();
    if (pauseFrames <= 0 && !gameOver) player->draw();
    if (pauseFrames <= 0 && !gameOver && players2) player2->draw();
    if (pauseFrames <= 0 && !gameOver && players3) player3->draw();
    if (pauseFrames <= 0 && !gameOver && players4) player4->draw();
    for (Animation& a : Animation::animations) a.draw();
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 55.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
                Rectangle{10.0f, GetScreenHeight() - 72.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
                DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 86.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
    for (int i = 0; i < player->getLives(); i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 0, 17, 18}, 
            Rectangle{10.0f + i * 30, GetScreenHeight() - 30.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }
    for (int i = 0; i < player->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{42, 57, 7, 11}, 
               Rectangle{35.0f + i * 20, GetScreenHeight() - 60.0f, 14, 22}, 
               Vector2{0, 0}, 0, WHITE);
    }
    for (int i = 0; i < player->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 65, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 55.0f, 20, 20},
                Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 58, 6, 7}, 
                Rectangle{10.0f, GetScreenHeight() - 72.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{83, 53, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 86.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }    
    }
    if (players2) {
        for (int i = 0; i < player2->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{177, 76, 7, 11}, 
               Rectangle{GetScreenWidth() - 50.0f - i * 20, GetScreenHeight() - 60.0f, 14, 22}, 
               Vector2{0, 0}, 0, WHITE);}

        for (int i = 0; i < player2->getLives(); i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{0, 18, 17, 18}, 
            Rectangle{GetScreenWidth()-30.0f - i * 30, GetScreenHeight() - 30.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 55.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 72.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 86.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        for (int i = 0; i < player2->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{260, 87, 6, 6}, 
            Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 55.0f, 20, 20}, 
            Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{260, 80, 6, 7}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 72.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{260, 75, 6, 6}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 86.0f, 20, 20},
                Vector2{0, 0}, 0, WHITE);
            }
        }                

    }
    if (players3) {
    for (int i = 0; i < player3->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{177, 92, 7, 11}, 
               Rectangle{35.0f + i * 20, GetScreenHeight() - 200.0f, 14, 22}, 
               Vector2{0, 0}, 0, WHITE);}

    for (int i = 0; i < player3->getLives(); i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{217, 91, 17, 18}, 
            Rectangle{10.0f + i * 30, GetScreenHeight() - 170.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }

            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
            Rectangle{10.0f, GetScreenHeight() - 195.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
            Rectangle{10.0f, GetScreenHeight() - 212.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
            Rectangle{10.0f, GetScreenHeight() - 226.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
    for (int i = 0; i < player3->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{276, 87, 6, 6}, 
            Rectangle{10.0f, GetScreenHeight() - 195.0f, 20, 20}, 
            Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{276, 80, 6, 7}, 
                Rectangle{10.0f, GetScreenHeight() - 212.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{276, 75, 6, 6}, 
                Rectangle{10.0f, GetScreenHeight() - 226.0f, 20, 20},
                Vector2{0, 0}, 0, WHITE);
            }
        }                
    }
    if (players4) {
    for (int i = 0; i < player4->getMissiles(); i++) {  
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{218, 77, 7, 11}, 
               Rectangle{GetScreenWidth() - 50.0f - i * 20, GetScreenHeight() - 200.0f, 14, 22}, 
               Vector2{0, 0}, 0, WHITE);}
    for (int i = 0; i < player4->getLives(); i++) {
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{234, 91, 17, 18}, 
            Rectangle{GetScreenWidth()-30.0f - i * 30, GetScreenHeight() - 170.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
        }
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 65, 6, 6}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 195.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 58, 6, 7}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 212.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{90, 53, 6, 6}, 
            Rectangle{GetScreenWidth() - 30.0f, GetScreenHeight() - 226.0f, 20, 20}, 
            Vector2{0, 0}, 0, WHITE);
    for (int i = 0; i < player4->getShield(); i++) {
        if (i>=0){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{268, 87, 6, 6}, 
            Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 195.0f, 20, 20}, 
            Vector2{0, 0}, 0,WHITE);
        }
        if (i>=1){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{268, 80, 6, 7}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 212.0f, 20, 20}, 
                Vector2{0, 0}, 0, WHITE);
        }
        if (i>=2){
            DrawTexturePro(ImageManager::SpriteSheet, Rectangle{268, 75, 6, 6}, 
                Rectangle{GetScreenWidth() -30.0f, GetScreenHeight() - 226.0f, 20, 20},
                Vector2{0, 0}, 0, WHITE);
            }
        }                
    
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
    int difficulty = std::max(std::min(score / 1000, 5+(difficultyTweak*3)), 3);
    respawnCooldown -= difficulty;
    if (respawnCooldown <= 0) {
        respawnCooldown = 900;
        for (std::pair<std::pair<float, float>, Enemy*>& p : Enemy::enemies) {
            if (!p.second && p.first.second != 150) {
                int eType = GetRandomValue(1, 3);

                if (eType == 1) {
                    p.second = new StEnemy(GetScreenWidth() / 2 - 15, 0, true);
                } else {
                    if (difficulty >= 5) {p.second = new StdEnemy(GetScreenWidth() / 2 - 15, 0, true, 1);
                    if (difficulty >=7) respawnCooldown = 0;
                    }
                    else {p.second = new StdEnemy(GetScreenWidth() / 2 - 15, 0, true);
                    if (difficulty >= 4) respawnCooldown = 0;
                    }
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
    DrawText("Pause: D", 5, 30, 30, WHITE);
    DrawText("Press Enter", (GetScreenWidth() / 2) - 75, GetScreenHeight() / 2, 24, GRAY);
    DrawText("Move: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() -185, 30, WHITE);
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{98, 53, 16, 19},
                Rectangle{(GetScreenWidth() / 2) - 310.0f, GetScreenHeight() - 200.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE); 
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{115, 53, 16, 19},
                Rectangle{(GetScreenWidth() / 2) - 255.0f, GetScreenHeight() - 200.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Missiles: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() - 125, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{132, 53, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 270.0f, GetScreenHeight() - 140.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Shield: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() - 65, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{149, 53, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 300.0f, GetScreenHeight()- 80.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Shoot: ", (GetScreenWidth() / 2) -120, GetScreenHeight() / 2 - 75, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{166, 53, 80, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 20.0f, (GetScreenHeight() / 2) - 90.0f, 250, 59}, 
                Vector2{0, 0}, 0, WHITE);
    if(players2) {
    DrawText(":Move", (GetScreenWidth() / 2) + 310, GetScreenHeight() -185, 30, WHITE);
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{183, 34, 16, 19},
                Rectangle{(GetScreenWidth() / 2) + 195.0f, GetScreenHeight() - 200.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE); 
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{200, 34, 16, 19},
                Rectangle{(GetScreenWidth() / 2) + 250.0f, GetScreenHeight() - 200.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText(":Missiles", (GetScreenWidth() / 2) + 270, GetScreenHeight() - 125, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{217, 34, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) + 210.0f, GetScreenHeight() - 140.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText(":Shield", (GetScreenWidth() / 2) + 300, GetScreenHeight() - 65, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{234, 34, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) + 240.0f, GetScreenHeight()- 80.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    }
    if(players3) {
    DrawText("Move: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() -385, 30, WHITE);
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{251, 34, 16, 19},
                Rectangle{(GetScreenWidth() / 2) - 310.0f, GetScreenHeight() - 400.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE); 
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{268, 34, 16, 19},
                Rectangle{(GetScreenWidth() / 2) - 255.0f, GetScreenHeight() - 400.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Missiles: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() - 325, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{285, 34, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 270.0f, GetScreenHeight() - 340.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText("Shield: ", (GetScreenWidth() / 2) - 400, GetScreenHeight() - 265, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{302, 34, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) - 300.0f, GetScreenHeight()- 280.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    }
    if(players4) {
    DrawText(":Move", (GetScreenWidth() / 2) + 310, GetScreenHeight() -385, 30, WHITE);
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{251, 54, 16, 19},
                Rectangle{(GetScreenWidth() / 2) + 195.0f, GetScreenHeight() - 400.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE); 
    DrawTexturePro(ImageManager::SpriteSheet, Rectangle{268, 54, 16, 19},
                Rectangle{(GetScreenWidth() / 2) + 250.0f, GetScreenHeight() - 400.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText(":Missiles", (GetScreenWidth() / 2) + 270, GetScreenHeight() - 325, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{285, 54, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) + 210.0f, GetScreenHeight() - 340.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    DrawText(":Shield", (GetScreenWidth() / 2) + 300, GetScreenHeight() - 265, 30, WHITE);
        DrawTexturePro(ImageManager::SpriteSheet, Rectangle{302, 54, 16, 19}, 
                Rectangle{(GetScreenWidth() / 2) + 240.0f, GetScreenHeight()- 280.0f, 50, 59}, 
                Vector2{0, 0}, 0, WHITE);
    }
}

void Program::PlayerSelectScreen(){
    DrawText("Galaga", (GetScreenWidth() / 2 - 237), 75, 144, WHITE);
    DrawText("Select Player Count", (GetScreenWidth() / 2) - 200, 400, 48, WHITE);
    DrawText("Press 1 for Single Player", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 20, 24, WHITE);
    DrawText("Press 2 for Two Players", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 20, 24, RED);
    DrawText("Press 3 for Three Players", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 60, 24, BLUE);
    DrawText("Press 4 for Four Players", (GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 100, 24, YELLOW);
    DrawText("Press V for sprite sheet 1",(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 140, 24, WHITE);
    DrawText("Press B for sprite sheet 2",(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 + 180, 24, WHITE);
}

void Program::DrawSpriteToggle(int sheet){
    switch(sheet){
        case 1:
        DrawText("Sprites 1",(GetScreenWidth() / 2) + 200, GetScreenHeight() / 2 + 140, 24, WHITE);
        break;
        case 2:
        DrawText("Sprites 2",(GetScreenWidth() / 2) + 200, GetScreenHeight() / 2 + 180, 24, RED);
        break;
    }
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
    DrawText("Final Score", (GetScreenWidth() / 2) - 100, GetScreenHeight() / 2 + 40, 40, WHITE);
    DrawText(TextFormat("%i pts",score),(GetScreenWidth() / 2) - 100, GetScreenHeight() / 2 + 80, 40, WHITE);
}

void Program::KeyInputs() {
    if ((!gameOver && !startup && IsKeyPressed('D')) || (paused && IsKeyPressed(KEY_ENTER))) paused = !paused;
    if (!paused && !startup && IsKeyPressed('S')) gameOver = !gameOver;
    if (!gameOver && !paused && IsKeyPressed('A')) startup = !startup;
    if (IsKeyPressed('H')) HitBox::drawHitbox = !HitBox::drawHitbox;
    if (IsKeyPressed('G')) {
        score += 500;
        std::cout << "Score increased by 500. Current score: " << score << std::endl;
    }
    if (IsKeyPressed('F')) {
        player->setMissiles(player->getMissiles() + 1);
        if (players2) player2->setMissiles(player2->getMissiles() + 1);
        if (players3) player3->setMissiles(player3->getMissiles() + 1);
        if (players4) player4->setMissiles(player4->getMissiles() + 1);        
    }
    if (gameOver && IsKeyPressed(KEY_ENTER)) {
        gameOver = false;
        Projectile::projectiles.clear();
        Reset();
    }

    if (startup && IsKeyPressed(KEY_ENTER)) {
        startup = false;
    }

    if (!startup && !paused && !gameOver && pauseFrames <= 0) player->keyInputs();
    if (!startup && !paused && !gameOver && pauseFrames <= 0 && players2) player2->keyInputs();
    if (!startup && !paused && !gameOver && pauseFrames <= 0 && players3) player3->keyInputs();
    if (!startup && !paused && !gameOver && pauseFrames <= 0 && players4) player4->keyInputs();       
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
        case 3:
    Animation::animations.push_back(
        Animation(player3->position.first, player3->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet));
    break;
        case 4:
    Animation::animations.push_back(
        Animation(player4->position.first, player4->position.second, 16, 0, 33, 34, 30 ,30, 3, ImageManager::SpriteSheet));
    break;
}
    PlaySound(SoundManager::gameOver);
    if(!players2) Projectile::projectiles.clear();
    switch (identifier) {
        case 1:
    if(!players2)player->position.first = GetScreenWidth() / 2 - 15;
    if(!players2)pauseFrames = 120;
    if (player->getLives() > 1) {
        player->setMissiles(std::max(player->getMissiles(), 2));
        player->setShield(3);
    }
    player->setLives(player->getLives()-1);
    player->setIframes(60);
    break;
        case 2:
    if (player2->getLives() > 1) {
        player2->setMissiles(std::max(player2->getMissiles(), 2));
        player2->setShield(3);
    }
    player2->setIframes(60);
    player2->setLives(player2->getLives()-1);
    break;
        case 3:
    if (player3->getLives() > 1) {
        player3->setMissiles(std::max(player3->getMissiles(), 2));
        player3->setShield(3);
    }
    player3->setIframes(60);
    player3->setLives(player3->getLives()-1);
    break;
        case 4:
    if (player4->getLives() > 1) {
        player4->setMissiles(std::max(player4->getMissiles(), 2));
        player4->setShield(3);
    }
    player4->setIframes(60);
    player4->setLives(player4->getLives()-1);
    break;
}
}

void Program::Reset() {
    Enemy::enemies.clear();
    StdEnemy::attackInProgress = false;
    player = new Player((GetScreenWidth() / 2), GetScreenHeight() * 0.75f, 1);
    if (players2) player2 = new Player((GetScreenWidth() / 2) - 60, GetScreenHeight() * 0.75f, 2);
    if (players3) player3 = new Player((GetScreenWidth() / 2) - 120, GetScreenHeight() * 0.75f, 3);
    if (players4) player4 = new Player((GetScreenWidth() / 2) - 180, GetScreenHeight() * 0.75f, 4);
    score = 0;
    respawnCooldown = 1080;
    respawns = 0;
    count = 0;
    delay = 0;
    player->setLives(3);
    if (players2) player2->setLives(3);
    if (players3) player3->setLives(3);
    if (players4) player4->setLives(3);
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