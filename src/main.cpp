#include "raylib.h"

#include "resource_dir.h"
#include "Program.hpp"

int main ()
{
	SearchAndSetResourceDir("resources");
    InitAudioDevice();
	SetTargetFPS(60);

	raylib::Window window(1000, 1000, "Galaga", FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	Program Galaga;
	ImageManager::Load(1);
	SoundManager::Load();

	if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Window failed to initialize!");
    return 1;
}
	bool confirm = false;
	int spriteToggle = 1;

	Galaga.addPlayer(new Player((GetScreenWidth() / 2), GetScreenHeight() * 0.75f,1), 1);
	while (!confirm && !WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		Galaga.PlayerSelectScreen();
		if (IsKeyPressed(KEY_ONE)) confirm = true;
		EndDrawing();
		if (IsKeyPressed(KEY_TWO)){
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 60, GetScreenHeight() * 0.75f,2), 2);
			confirm = true;
		}
		if (IsKeyPressed(KEY_THREE)){
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 60, GetScreenHeight() * 0.75f,2), 2);
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 120, GetScreenHeight() * 0.75f,3), 3);
			confirm = true;
		}
		if (IsKeyPressed(KEY_FOUR)){
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 60, GetScreenHeight() * 0.75f,2), 2);
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 120, GetScreenHeight() * 0.75f,3), 3);
			Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 180, GetScreenHeight() * 0.75f,4), 4);
			confirm = true;
		}
		if (IsKeyPressed(KEY_V)){
			ImageManager::Unload();
			ImageManager::Load(1);
			spriteToggle = 1;
		}
		if (IsKeyPressed(KEY_B)){
			ImageManager::Unload();
			ImageManager::Load(2);
			spriteToggle = 2;
		}

		if(spriteToggle == 1)Galaga.DrawSpriteToggle(1);
		if(spriteToggle == 2)Galaga.DrawSpriteToggle(2);
	}
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		Galaga.Update();
		Galaga.Draw();
		Galaga.KeyInputs();

		EndDrawing();
	}

	ImageManager::Unload();
	SoundManager::Unload();
	CloseAudioDevice();
	window.Close();
	return 0;
}
