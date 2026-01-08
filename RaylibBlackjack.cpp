/**
* Blackjack made with RayLib
* It's a very simple Blackjack game made in C++
* 
* Repo: https://github.com/FauZaPespi/RaylibBlackjack
* Discord: fauzapespi
*/

#include <iostream>
#include "raylib.h"
#include "RaylibBlackjack.h"
#include <string>
#include <random>

struct Card {
	Vector2 cardPos;
	char title;
	int value;
};

int getRandom(int min, int max) {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

// Retourne 0 si c'est player et 1 si c'est croupier et 2 si push
int checkWinner(int playerScore, int croupierScore) {
	if (playerScore == croupierScore)
		return 2;
	if (playerScore > 21 || playerScore < croupierScore)
		return 1;
	if (croupierScore > 21 || croupierScore < playerScore)
		return 0;
}

int main()
{
	printf("### Blackjack Raylib ###");
	const int screenWidth = 800;
	const int screenHeight = 600;

	// Game objects
	int gameTurn = 0;
	Card cards[6];
	Card croupierCards[6];
	int cardsIndex = 0;
	int croupierCardsIndex = 0;
	bool hasStand = false;
	const Vector2 cardSize = { 80, 120 };
	int playerTotal = 0;
	int croupierTotal = 0;
	int currentWinner = -1;

	InitWindow(screenWidth, screenHeight, "Blackjack Raylib - FauZa v0.0.2");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if ((gameTurn == 0 && croupierCardsIndex == 0) || (hasStand && croupierTotal < 17)) {
			int val = getRandom(1, 11);

			char viewVal = '?';
			if (val == 11) viewVal = 'A';
			else if (val == 10) viewVal = 'Q';
			else viewVal = '0' + val;

			croupierCards[croupierCardsIndex] = {
				{150 + (cardSize.x * croupierCardsIndex), 150},
				viewVal,
				val
			};

			croupierCardsIndex++;
			croupierTotal += val;
		}

		// Logic
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !hasStand)
		{
			// Rester
			hasStand = true;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameTurn < 6 && !hasStand && playerTotal < 21)
		{
			// Tirer
			int val = 0;
			val = getRandom(1, 11);
			// 11 => A et -1 => H (caché)
			char viewVal = '?';
			if (val == 11)
				viewVal = 'A';
			else if (val == 10)
				viewVal = 'Q';
			else
				viewVal = '0' + val;

			cards[cardsIndex] = { {150 + (cardSize.x * cardsIndex), 360}, viewVal, val };
			cardsIndex++;
			gameTurn++;
			playerTotal += val;
		}
		currentWinner = checkWinner(playerTotal, croupierTotal);

		// Drawing
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// Left side
		DrawText("Blackjack with RayLib - v0.0.1", 10, 10 + (20 * 0), 20, LIGHTGRAY);
		DrawText("Use [LEFT] Click to HIT", 10, 10 + (20 * 1), 20, LIGHTGRAY);
		DrawText("Use [RIGHT] Click to STAND", 10, 10 + (20 * 2), 20, LIGHTGRAY);

		// Right side
		DrawText("Game stats:", screenWidth - 250, 10 + (20 * 0), 20, LIGHTGRAY);
		std::string gameTurnLbl = "Game turn: " + std::to_string(gameTurn);
		DrawText(gameTurnLbl.c_str(), screenWidth - 150, 10 + (20 * 1), 20, LIGHTGRAY);
		std::string gameStandLbl = "Stand: " + std::to_string(hasStand);
		DrawText(gameStandLbl.c_str(), screenWidth - 150, 10 + (20 * 2), 20, LIGHTGRAY);
		std::string playerTotalLbl = "Player : " + std::to_string(playerTotal);
		DrawText(playerTotalLbl.c_str(), screenWidth - 150, 10 + (20 * 3), 20, LIGHTGRAY);
		std::string croupierTotalLbl = "Croupier : " + std::to_string(croupierTotal);
		DrawText(croupierTotalLbl.c_str(), screenWidth - 150, 10 + (20 * 4), 20, LIGHTGRAY);
		std::string winnerLbl = "Winner : " + std::to_string(currentWinner);
		DrawText(winnerLbl.c_str(), screenWidth - 150, 10 + (20 * 5), 20, LIGHTGRAY);

		// Title
		std::string winnerTitle = "";
		if (currentWinner == 2)
			winnerTitle = "PUSH <=>";
		if (currentWinner == 1)
			winnerTitle = "Croupier";
		if (currentWinner == 0)
			winnerTitle = "Player";

		if (hasStand)
			DrawText(winnerTitle.c_str(), (screenWidth/2)-75, 10 + (20 * 5), 50, LIGHTGRAY);

		for (int i = 0; i < cardsIndex; i++)
		{
			Card card = cards[i];
			char text[3] = { card.title, '\0' };
			DrawRectangle(card.cardPos.x, card.cardPos.y, cardSize.x, cardSize.y, MAROON);
			DrawText(text, card.cardPos.x + (cardSize.x / 2) - 5, card.cardPos.y + (cardSize.y / 2) - 5, 20, LIGHTGRAY);
			std::string valueStr = std::to_string(card.value);
			DrawText(valueStr.c_str(), card.cardPos.x + (cardSize.x / 2) - 5, card.cardPos.y + (cardSize.y / 2) - 25, 10, LIGHTGRAY);
		}

		for (int i = 0; i < croupierCardsIndex; i++)
		{
			Card card = croupierCards[i];
			char text[3] = { card.title, '\0' };
			DrawRectangle(card.cardPos.x, card.cardPos.y, cardSize.x, cardSize.y, MAROON);
			DrawText(text, card.cardPos.x + (cardSize.x / 2) - 5, card.cardPos.y + (cardSize.y / 2) - 5, 20, LIGHTGRAY);
			std::string valueStr = std::to_string(card.value);
			DrawText(valueStr.c_str(), card.cardPos.x + (cardSize.x / 2) - 5, card.cardPos.y + (cardSize.y / 2) - 25, 10, LIGHTGRAY);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
