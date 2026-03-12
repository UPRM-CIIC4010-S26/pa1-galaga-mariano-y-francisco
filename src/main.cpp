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
	ImageManager::Load();
	SoundManager::Load();

	if (!IsWindowReady()) {
    TraceLog(LOG_ERROR, "Window failed to initialize!");
    return 1;
}
	bool confirm = false;

	Galaga.addPlayer(new Player((GetScreenWidth() / 2) - 15, GetScreenHeight() * 0.75f,1), 1);
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
