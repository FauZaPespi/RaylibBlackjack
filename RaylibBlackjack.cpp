#include <iostream>
#include "raylib.h"
#include "RaylibBlackjack.h"
#include <string>

struct Card {
    Vector2 cardPos;
    char title;
    int value;
};

int main()
{
    printf("### Blackjack Raylib ###");
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Game objects
    int gameTurn = 0;
    Card cards[6];
    int cardsIndex = 0;
    bool hasStand = false;
    const Vector2 cardSize = { 80, 120 };

    InitWindow(screenWidth, screenHeight, "Blackjack Raylib - FauZa v0.0.1");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Logic
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !hasStand)
        {
            // Rester
            hasStand = true;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && gameTurn < 6 && !hasStand)
        {
            // Tirer
            int val = 0;
            while (val )
            int val = rand();
            cards[cardsIndex] = { {150 + (cardSize.x * cardsIndex), 360}, '6', 6 };
            cardsIndex++;
            gameTurn++;
        }


        // Drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Blackjack with RayLib - v0.0.1", 10, 10 + (20 * 0), 20, LIGHTGRAY);
        DrawText("Use [LEFT] Click to HIT", 10, 10 + (20*1), 20, LIGHTGRAY);
        DrawText("Use [RIGHT] Click to STAND", 10, 10 + (20*2), 20, LIGHTGRAY);

        DrawText("Game stats:", screenWidth-250, 10 + (20 * 0), 20, LIGHTGRAY);
        std::string gameTurnLbl = "Game turn: " + std::to_string(gameTurn);
        DrawText(gameTurnLbl.c_str(), screenWidth - 150, 10 + (20 * 1), 20, LIGHTGRAY);
        std::string gameStandLbl = "Stand: " + std::to_string(hasStand);
        DrawText(gameStandLbl.c_str(), screenWidth - 150, 10 + (20 * 2), 20, LIGHTGRAY);

        for (Card card : cards)
        {
            char text[2] = { card.title, '\0' };
            DrawRectangle(card.cardPos.x, card.cardPos.y, cardSize.x, cardSize.y, MAROON);
            DrawText(text, card.cardPos.x+(cardSize.x/2)-5, card.cardPos.y + (cardSize.y / 2)-5, 20, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
