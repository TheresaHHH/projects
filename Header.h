#pragma once
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;

struct Tile
{
	int positionIndex;
	int col;
	int row;
	int nearMines;
	bool ifHasMine;
	bool isFlag;
	bool ifClicked;
	sf::Sprite s;
};

//draw game
void randGame(vector<Tile>& tiles, Tile(&board)[25][16]);
void resetGame(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& tileHidden, vector<sf::Texture>& facesTextureV,  sf::Sprite& faceS, int& mineCounter, bool& isLost, bool& isWin);
void drawAll(vector<Tile>& tiles, vector<sf::Sprite>& backgroungS, vector<sf::Sprite>digitCount, sf::RenderWindow& window, sf::Sprite& faceS, sf::Sprite& debugS, sf::Sprite& test1S, sf::Sprite& test2S, sf::Sprite& test3S, vector<sf::Texture>& mineCounterV, sf::Sprite& mineCounts, int& mineCounter);
void drawTiles(vector<Tile>& tiles, vector<sf::Sprite>& backgroungS, sf::RenderWindow& window);
void drawCounter(sf::RenderWindow& window, vector<sf::Sprite>digitCount);
void setMineCounter(vector<sf::Sprite>& digitCount, sf::Sprite& mineCounts, vector<sf::Texture>& mineCounterV, int& mineCounter);
void faceAddtoVector(vector<sf::Texture>& facesTextureV);
void setNearMineCount(Tile& tile, int number);
void nearMineAddToVector(vector<sf::Texture>& nearMineV);
void setTile(vector<Tile>& tiles, Tile(&board)[25][16], int index, Tile& t, sf::Texture& tileRevealed, vector<sf::Texture>& nearMineV, sf::Texture& mineT, bool& isLost);
void autoReveal(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& tileRevealed, Tile& t, vector<sf::Texture>& nearMineV);
//check
bool isRestClicked(vector<Tile>& tiles, sf::Vector2f pos, sf::Sprite& faceS);
bool isTileClicked(vector<Tile>& tiles, sf::Vector2f pos, int& index);
bool isTile(int row, int col);
void checkIfwin(vector<Tile>& tiles, Tile(&board)[25][16], int& mineCounter, int& mineNumber, bool& isLost, bool& isWin);
bool checkIfMine(Tile& tile);
int checkNearmine(Tile& tile, Tile(&board)[25][16]);
//testing function
void testBoard(vector<Tile>& tiles, Tile(&board)[25][16], vector<char>& mineMap, int& mineCounter, int& mineNumber);
void openFile(vector<Tile>& tiles, Tile(&board)[25][16], vector<char>& mineMap, string fileName, int& mineCounter, int& mineNumber);
void debugGame(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& mineT, sf::Texture& tileRevealed, vector<sf::Texture>& nearMineV);