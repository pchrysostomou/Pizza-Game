/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"



static void capFrameRate(long* then, float* remainder);

char* global_dir = "C:\\Users\\di918039\\source\\repos\\cs1pr-portfolio\\project-visual-studio\\SpringProject";

int WinMain() {
	long then;
	float remainder;

	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

	then = SDL_GetTicks();

	remainder = 0;
	stage.currTime = 0;
	uint64_t startTime = 0.0;

	while (1)
	{
		prepareScene();

		doInput();
		app.delegate.logic();

		app.delegate.draw();
		capFrameRate(&then, &remainder);

		presentScene();
		stage.currTime += 1.0;
		stage.timeElapsed = (stage.currTime - stage.startTime);
		drawText(SCREEN_WIDTH - 1135, 5, 255, 255, 255, TEXT_RIGHT, "TIMER: %0.0f", stage.timeElapsed / 50);
		SDL_RenderPresent(app.renderer);
	}


	return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
