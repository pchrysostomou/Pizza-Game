#include "common.h"

static SDL_Texture* pete[2];

void initPlayer2(void)
{
	player2 = malloc(sizeof(Entity));
	memset(player2, 0, sizeof(Entity));
	stage.entityTail->next = player2;
	stage.entityTail = player2;

	player2->health = 1;

	pete[0] = loadTexture("gfx/pete01.png");
	pete[1] = loadTexture("gfx/pete02.png");

	player2->texture = pete[1];

	SDL_QueryTexture(player2->texture, NULL, NULL, &player2->w, &player2->h);
}

void doPlayer2(void)
{
	player2->dx = 0;

	if (app.keyboard[SDL_SCANCODE_J])
	{
		player2->dx = -PLAYER_MOVE_SPEED;

		player2->texture = pete[1];
	}

	if (app.keyboard[SDL_SCANCODE_I])
	{
		player2->dx = PLAYER_MOVE_SPEED;

		player2->texture = pete[0];
	}

	if (app.keyboard[SDL_SCANCODE_L] && player2->isOnGround)
	{
		player2->riding = NULL;

		player2->dy = -20;

		playSound(SND_JUMP, CH_PLAYER);
	}

	if (app.keyboard[SDL_SCANCODE_I])
	{
		player2->x = player2->y = 0;

		app.keyboard[SDL_SCANCODE_I] = 0;
	}
}