#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

#include "cell.h"
#include "player.h"
#include "raylib.h"
#include "textureLoader.h"

class Player;  // forward declare
class Cell;

class Game {
   private:
    struct GameState {
        bool gameover;
        bool paused;
        Player winner;
    };
    struct PlayerColor {
        Color color;
        Texture2D coin;
    };

   public:
    Game(TextureLoader& textureManager, float screenWidth, float screenHeight, std::vector<Player>& players);
    void updateRes(float newScreenWidth, float newScreenHeight);
    void draw();
    void tick(Vector2 mousePos, std::vector<Player>& players);
    void setPlayerColor(Player& player, int n);
    Player getTurnPlayer() { return turnPlayer; }
    void setTurnPlayer(Player player) { turnPlayer = player; }
    void setPlayerIndex(int idx) { playerIndex = idx; }
    int getPlayerIndex() { return playerIndex; }
    void unpause() { paused = false; }
    void pause() { paused = true; }
    GameState getGameState();
    bool newGameRequest{false};
    void reset(std::vector<Player>& players);

   private:
    bool paused{true};
    bool gameover{false};
    Player winner;
    TextureLoader textureManager{};
    static constexpr int COLS{7};
    static constexpr int ROWS{6};
    float screenWidth{};
    float screenHeight{};
    float width{screenWidth * 0.75f};
    float height{screenHeight * 0.75f};
    Vector2 screenPos{(screenWidth - width) / 2.f, (screenHeight - height) / 2.f};
    Rectangle recSrc{
        screenPos.x,
        screenPos.y,
        width,
        height};
    std::vector<std::vector<Cell>> grid2d;
    int playerIndex{GetRandomValue(0, 1)};
    Player turnPlayer{};
    static const int sizeOfPlayerColors{2};
    PlayerColor colors[sizeOfPlayerColors];
    bool winCon(Player& player);
};

#endif