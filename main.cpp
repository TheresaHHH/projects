#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include <vector> 
#include <cstdlib>
#include "Header.h"

using namespace std;
#include <iostream>
void setMineCounter(vector<sf::Sprite>& digitCount, sf::Sprite& mineCounts, vector<sf::Texture>& mineCounterV, int& mineCounter)
{
	digitCount.clear();
	if (mineCounter >= 0)
	{
		//cout << "52 "<<endl;
		mineCounts.setTexture(mineCounterV[0]);
		mineCounts.setPosition(0, 512);
	}
	else {
		//cout << "57 " << endl;
		mineCounts.setTexture(mineCounterV[10]);
		mineCounts.setPosition(0, 512);
	}
	digitCount.push_back(mineCounts);
	int mineCounter2 = abs(mineCounter);
	int a = (mineCounter2 / 10) % 10;
	int b = mineCounter2 % 10;
	mineCounts.setTexture(mineCounterV[a]);
	mineCounts.setPosition(21, 512);
	//cout << (mineCounter2 / 10) % 10 ;
	digitCount.push_back(mineCounts);
	mineCounts.setTexture(mineCounterV[b]);
	mineCounts.setPosition(42, 512);
	//cout << mineCounter2 % 10 << endl;
	digitCount.push_back(mineCounts);
}
void faceAddtoVector(vector<sf::Texture>& facesTextureV)
{
	sf::Texture faceT;
	faceT.loadFromFile("images/face_happy.png");
	facesTextureV.push_back(faceT);
	faceT.loadFromFile("images/face_lose.png");
	facesTextureV.push_back(faceT);
	faceT.loadFromFile("images/face_win.png");
	facesTextureV.push_back(faceT);
}

void nearMineAddToVector(vector<sf::Texture>& nearMineV)
{
	sf::Texture numberT;
	numberT.loadFromFile("images/number_1.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_2.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_3.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_4.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_5.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_6.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_7.png");
	nearMineV.push_back(numberT);
	numberT.loadFromFile("images/number_8.png");
	nearMineV.push_back(numberT);
}

void openFile(vector<Tile>& tiles, Tile(&board)[25][16], vector<char>& mineMap, string fileName, int& mineCounter, int& mineNumber)
{
	mineMap.clear();
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "cool";
	}

	string line;
	for (int i = 0; i < 16; i++)
	{
		getline(file, line, '\n');
		copy(line.begin(), line.end(), back_inserter(mineMap));
	}

	testBoard(tiles, board, mineMap, mineCounter, mineNumber);
}

void drawTiles(vector<Tile>& tiles, vector<sf::Sprite>& backgroungS, sf::RenderWindow& window)
{
	for (int i = 0; i < 400; i++) {
		window.draw(backgroungS[i]);
	}
	for (int i = 0; i < 400; i++) {
		window.draw(tiles[i].s);
	}
}

void drawCounter(sf::RenderWindow& window, vector<sf::Sprite>digitCount)
{
	for (int i = 0; i < 3; i++) {
		window.draw(digitCount[i]);
	}
}

bool isTileClicked(vector<Tile>& tiles, sf::Vector2f pos , int& index)
{
	bool b = false;
	for (int i = 0; i < 400; i++)
	{
		//tiles[i].s.getGlobalBounds().contains(pos);
		if (tiles[i].s.getGlobalBounds().contains(pos)) {
			index = i;
			b = true;
		}
	}
	return b;
}
bool isRestClicked(vector<Tile>& tiles, sf::Vector2f pos, sf::Sprite& faceS)
{
	bool b = false;
	if (faceS.getGlobalBounds().contains(pos))
	{
		b = true;
	}
	return b;
}

void resetGame(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& tileHidden, vector<sf::Texture>&facesTextureV, sf::Sprite& faceS, int& mineCounter, bool& isLost, bool& isWin)
{
	for (int i = 0; i < 400; i++)
	{
		tiles[i].ifClicked = false;
		tiles[i].isFlag = false;
		tiles[i].ifHasMine = false;
		tiles[i].nearMines = 0;
		tiles[i].s.setTexture(tileHidden);
		board[tiles[i].col][tiles[i].row].ifClicked = false;
		board[tiles[i].col][tiles[i].row].isFlag = false;
		board[tiles[i].col][tiles[i].row].ifHasMine = false;
		board[tiles[i].col][tiles[i].row].nearMines = 0;
		board[tiles[i].col][tiles[i].row].s.setTexture(tileHidden);
	}
	isWin = false;
	isLost = false;
	faceS.setTexture(facesTextureV[0]);
	//mineMap.clear();
	mineCounter = 50;
}

void testBoard(vector<Tile>& tiles, Tile(&board)[25][16], vector<char>& mineMap, int& mineCounter, int& mineNumber)
{
	//cout << mineMap.size();
	int countMine = 0;
	for (int i = 0; i < 400; i++)
	{
		if (mineMap[i] == '1')
		{
			countMine++;
			tiles[i].ifHasMine = true;
			board[tiles[i].col][tiles[i].row].ifHasMine = true;
		}
	}
	mineCounter = countMine;
	mineNumber = countMine;
	//cout << mineMap.size();
	for (int i = 0; i < 400; i++)
	{
		tiles[i].nearMines = checkNearmine(tiles[i],board );
		board[tiles[i].col][tiles[i].row].nearMines = tiles[i].nearMines;
		//cout << tiles[i].nearMines;
	}

}

void debugGame(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& mineT, sf::Texture& tileRevealed, vector<sf::Texture>& nearMineV)
{

	for (int i = 0; i < 400; i++)
	{
		if (tiles[i].ifHasMine == true)
		{
			tiles[i].s.setTexture(mineT);
			board[tiles[i].col][tiles[i].row].s.setTexture(mineT);
		}
		else
		{
			//tiles[i].ifClicked = true;
			//board[tiles[i].col][tiles[i].row].ifClicked = true;
			//setTile(tiles[i], tileRevealed, nearMineV, mineT);
		}
	}

}

void checkIfwin(vector<Tile>& tiles, Tile(&board)[25][16], int& mineCounter, int& mineNumber, bool& isLost, bool& isWin)
{
	int number = 0;
	for (int i =0; i<400; i++) 
	{
		if (tiles[i].ifClicked==false) 
		{
			number++;
		}
	}


	if (mineNumber== number && isLost==false && mineCounter==0)
	{
		isWin = true;
	}
}

int checkNearmine(Tile& t, Tile(&board)[25][16] )
{
	int nearMine = 0;
	if (checkIfMine(t))
	{
		nearMine = 0;
	}
	else {
		//A tile has eight neighbors 
		//1
		if (isTile(t.col, t.row - 1) == true)
		{
			if (checkIfMine(board[t.col][t.row - 1]) == true)
			{
				nearMine++;
			}
		}

		//2
		if (isTile(t.col - 1, t.row) == true)
		{
			//cout << "Hi";
			if (checkIfMine(board[t.col - 1][t.row]) == true)
			{
				nearMine++;
			}
		}
		//3
		if (isTile(t.col + 1, t.row) == true)
		{
			if (checkIfMine(board[t.col + 1][t.row]) == true)
			{
				nearMine++;
			}
		}
		//4
		if (isTile(t.col + 1, t.row + 1) == true)
		{
			if (checkIfMine(board[t.col + 1][t.row + 1]) == true)
			{
				nearMine++;
			}
		}
		//5
		if (isTile(t.col, t.row + 1) == true)
		{
			if (checkIfMine(board[t.col][t.row + 1]) == true)
			{
				nearMine++;
			}
		}
		//6
		if (isTile(t.col - 1, t.row + 1) == true)
		{
			if (checkIfMine(board[t.col - 1][t.row + 1]) == true)
			{
				nearMine++;
			}
		}
		//7
		if (isTile(t.col + 1, t.row - 1) == true)
		{
			if (checkIfMine(board[t.col + 1][t.row - 1]) == true)
			{
				nearMine++;
			}
		}
		//8
		if (isTile(t.col - 1, t.row - 1) == true)
		{
			if (checkIfMine(board[t.col - 1][t.row - 1]) == true)
			{
				nearMine++;
			}
		}
	}
	return nearMine;
}

bool checkIfMine(Tile& tile)
{
	bool b = false;
	if (tile.ifHasMine == true)
	{
		b = true;
	}

	return b;
}
bool isTile(int col, int row)
{
	return (col >= 0) && (row >= 0) && (col <= 24) && (row <= 15);
}
void setNearMineCount(Tile& tile, int number)
{
	tile.nearMines = number;
}
void setTile(vector<Tile>& tiles, Tile(&board)[25][16], int index, Tile& t, sf::Texture& tileRevealed, vector<sf::Texture>& nearMineV, sf::Texture& mineT, bool& isLost)
{
	if (t.ifClicked == true)
	{
		if (t.ifHasMine == false)
		{
			if (t.nearMines == 0)
			{
				board[t.col][t.row].s.setTexture(tileRevealed);
				t.s.setTexture(tileRevealed);
				autoReveal(tiles, board, tileRevealed, tiles[index],nearMineV);
			}
			else {
				board[t.col][t.row].s.setTexture(nearMineV[t.nearMines - 1]);
				t.s.setTexture(nearMineV[t.nearMines - 1]);
			}
		}
		else {
			isLost = true;
			board[t.col][t.row].s.setTexture(mineT);
			t.s.setTexture(mineT);
		}
	}

}

void autoReveal(vector<Tile>& tiles, Tile(&board)[25][16], sf::Texture& tileRevealed, Tile& t, vector<sf::Texture>& nearMineV)
{
	//A tile has eight neighbors 
		//1
	if (isTile(t.col, t.row - 1) == true)
	{
		if (board[t.col][t.row - 1].ifClicked == false&& board[t.col][t.row - 1].ifHasMine == false)
		{
			if (board[t.col][t.row - 1].nearMines == 0 )
			{
				
				board[t.col][t.row - 1].s.setTexture(tileRevealed);
				tiles[board[t.col][t.row - 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col][t.row - 1].ifClicked = true;
				tiles[board[t.col][t.row - 1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col][t.row - 1], nearMineV);

			}
			else {
				board[t.col][t.row-1].s.setTexture(nearMineV[board[t.col][t.row - 1].nearMines - 1]);
				tiles[board[t.col][t.row - 1].positionIndex].s.setTexture(nearMineV[board[t.col][t.row - 1].nearMines - 1]);
				//
				board[t.col][t.row - 1].ifClicked = true;
				tiles[board[t.col][t.row - 1].positionIndex].ifClicked = true;
			}
		}

		
	}

	//2
	if (isTile(t.col - 1, t.row) == true)
	{
		if (board[t.col - 1][t.row].ifClicked == false&& board[t.col-1][t.row].ifHasMine == false)
		{
			if (board[t.col - 1][t.row].nearMines == 0 )
			{
				board[t.col - 1][t.row].s.setTexture(tileRevealed);
				tiles[board[t.col - 1][t.row].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col-1][t.row ].ifClicked = true;
				tiles[board[t.col-1][t.row ].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col-1][t.row ], nearMineV);
			}
			else {
				board[t.col-1][t.row].s.setTexture(nearMineV[board[t.col-1][t.row].nearMines - 1]);
				tiles[board[t.col-1][t.row].positionIndex].s.setTexture(nearMineV[board[t.col-1][t.row].nearMines - 1]);
				//
				board[t.col - 1][t.row].ifClicked = true;
				tiles[board[t.col - 1][t.row].positionIndex].ifClicked = true;
			}
		}
	}
	//3
	if (isTile(t.col + 1, t.row) == true)
	{
		if (board[t.col + 1][t.row].ifClicked == false&& board[t.col+1][t.row].ifHasMine == false)
		{
			if (board[t.col + 1][t.row].nearMines == 0 )
			{
				board[t.col + 1][t.row].s.setTexture(tileRevealed);
				tiles[board[t.col + 1][t.row].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col + 1][t.row].ifClicked = true;
				tiles[board[t.col + 1][t.row].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col+1][t.row ], nearMineV);
			}
			else {
				board[t.col+1][t.row].s.setTexture(nearMineV[board[t.col+1][t.row ].nearMines - 1]);
				tiles[board[t.col+1][t.row].positionIndex].s.setTexture(nearMineV[board[t.col+1][t.row].nearMines - 1]);
				//
				board[t.col + 1][t.row].ifClicked = true;
				tiles[board[t.col + 1][t.row].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col+1][t.row], nearMineV);
			}
		}
	}
	//4
	if (isTile(t.col + 1, t.row + 1) == true)
	{
		if (board[t.col + 1][t.row + 1].ifClicked == false&& board[t.col + 1][t.row+1].ifHasMine == false)
		{
			if (board[t.col + 1][t.row + 1].nearMines == 0 )
			{
				board[t.col + 1][t.row + 1].s.setTexture(tileRevealed);
				tiles[board[t.col + 1][t.row + 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col + 1][t.row+1].ifClicked = true;
				tiles[board[t.col + 1][t.row+1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col+1][t.row + 1], nearMineV);
			}
			else {
				board[t.col+1][t.row+1].s.setTexture(nearMineV[board[t.col+1][t.row+1].nearMines - 1]);
				tiles[board[t.col+1][t.row+1].positionIndex].s.setTexture(nearMineV[board[t.col+1][t.row+1].nearMines - 1]);
				//
				board[t.col + 1][t.row + 1].ifClicked = true;
				tiles[board[t.col + 1][t.row + 1].positionIndex].ifClicked = true;
			}
		}
	}
	//5
	if (isTile(t.col, t.row + 1) == true)
	{
		if (board[t.col][t.row + 1].ifClicked == false && board[t.col][t.row+1].ifHasMine == false)
		{
			if (board[t.col][t.row + 1].nearMines == 0 )
			{
				board[t.col][t.row + 1].s.setTexture(tileRevealed);
				tiles[board[t.col][t.row + 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col][t.row + 1].ifClicked = true;
				tiles[board[t.col][t.row + 1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col][t.row + 1], nearMineV);
			}
			else {
				board[t.col][t.row + 1].s.setTexture(nearMineV[board[t.col][t.row + 1].nearMines - 1]);
				tiles[board[t.col][t.row + 1].positionIndex].s.setTexture(nearMineV[board[t.col][t.row + 1].nearMines - 1]);
				//
				board[t.col][t.row + 1].ifClicked = true;
				tiles[board[t.col][t.row + 1].positionIndex].ifClicked = true;
			}
		}
	}
	//6
	if (isTile(t.col - 1, t.row + 1) == true)
	{
		if (board[t.col - 1][t.row + 1].ifClicked == false&& board[t.col - 1][t.row+1].ifHasMine == false)
		{
			if (board[t.col - 1][t.row + 1].nearMines == 0 )
			{
				board[t.col - 1][t.row + 1].s.setTexture(tileRevealed);
				tiles[board[t.col - 1][t.row + 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col-1][t.row + 1].ifClicked = true;
				tiles[board[t.col-1][t.row + 1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col-1][t.row + 1], nearMineV);
			}
			else {
				board[t.col - 1][t.row + 1].s.setTexture(nearMineV[board[t.col - 1][t.row + 1].nearMines - 1]);
				tiles[board[t.col - 1][t.row + 1].positionIndex].s.setTexture(nearMineV[board[t.col - 1][t.row + 1].nearMines - 1]);
				//
				board[t.col - 1][t.row + 1].ifClicked = true;
				tiles[board[t.col - 1][t.row + 1].positionIndex].ifClicked = true;
			}
		}
	}
	//7
	if (isTile(t.col + 1, t.row - 1) == true)
	{
		if (board[t.col + 1][t.row - 1].ifClicked == false && board[t.col + 1][t.row-1].ifHasMine == false)
		{
			if (board[t.col + 1][t.row - 1].nearMines == 0 )
			{
				board[t.col + 1][t.row - 1].s.setTexture(tileRevealed);
				tiles[board[t.col + 1][t.row - 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col + 1][t.row - 1].ifClicked = true;
				tiles[board[t.col + 1][t.row - 1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col+1][t.row - 1], nearMineV);
			}
			else {
				board[t.col + 1][t.row - 1].s.setTexture(nearMineV[board[t.col + 1][t.row - 1].nearMines - 1]);
				tiles[board[t.col + 1][t.row - 1].positionIndex].s.setTexture(nearMineV[board[t.col + 1][t.row - 1].nearMines - 1]);
				//
				board[t.col + 1][t.row - 1].ifClicked = true;
				tiles[board[t.col + 1][t.row - 1].positionIndex].ifClicked = true;
			}
		}
	}
	//8
	if (isTile(t.col - 1, t.row - 1) == true)
	{
		if (board[t.col - 1][t.row - 1].ifClicked == false && board[t.col-1][t.row-1].ifHasMine == false)
		{
			if (board[t.col - 1][t.row - 1].nearMines == 0 )
			{
				board[t.col - 1][t.row - 1].s.setTexture(tileRevealed);
				tiles[board[t.col - 1][t.row - 1].positionIndex].s.setTexture(tileRevealed);
				//
				board[t.col - 1][t.row - 1].ifClicked = true;
				tiles[board[t.col - 1][t.row - 1].positionIndex].ifClicked = true;
				//
				autoReveal(tiles, board, tileRevealed, board[t.col-1][t.row - 1], nearMineV);
			}
			else {
				board[t.col - 1][t.row - 1].s.setTexture(nearMineV[board[t.col - 1][t.row - 1].nearMines - 1]);
				tiles[board[t.col - 1][t.row - 1].positionIndex].s.setTexture(nearMineV[board[t.col - 1][t.row- 1].nearMines - 1]);
				//
				board[t.col - 1][t.row - 1].ifClicked = true;
				tiles[board[t.col - 1][t.row - 1].positionIndex].ifClicked = true;
			}
		}
	}
}

void randGame(vector<Tile>& tiles, Tile(&board)[25][16]) //places mines randomly
{
	int i= 0;
	while(i<50)
	{
		int x = rand() % 25;
		int y = rand() % 16;
		if (board[x][y].ifHasMine==false) 
		{
			board[x][y].ifHasMine = true;
			tiles[board[x][y].positionIndex].ifHasMine = true;
			i++;
		}
	}
	for (int i = 0; i < 400; i++)
	{
		tiles[i].nearMines = checkNearmine(tiles[i], board);
		board[tiles[i].col][tiles[i].row].nearMines = tiles[i].nearMines;
		//cout << tiles[i].nearMines;
	}
}

void drawAll(vector<Tile>& tiles, vector<sf::Sprite>& backgroungS, vector<sf::Sprite>digitCount, sf::RenderWindow& window, sf::Sprite& faceS, sf::Sprite& debugS, sf::Sprite& test1S, sf::Sprite& test2S, sf::Sprite& test3S, vector<sf::Texture>& mineCounterV, sf::Sprite& mineCounts, int& mineCounter)
{
	//cout << mineCounter;
	window.clear(sf::Color::White);//set background color to white
	drawTiles(tiles, backgroungS ,window);
	setMineCounter(digitCount, mineCounts, mineCounterV, mineCounter);
	drawCounter(window, digitCount );
	//tiles[28].s.setTexture(tileRevealed);
	window.draw(faceS);
	window.draw(debugS);
	window.draw(test1S);
	window.draw(test2S);
	window.draw(test3S);
}
int main()
{
	//declarations
	vector<Tile>tiles;
	vector<sf::Sprite>backgroundS;
	Tile board [25][16];
	int index = 0;
	bool isLost = false;
	bool isWin = false;
	//create window
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "My window");
	//
	//create tile
	sf::Texture tileHidden, tileRevealed, mineT, flagT;
	tileHidden.loadFromFile("images//tile_hidden.png");
	tileRevealed.loadFromFile("images//tile_revealed.png");
	mineT.loadFromFile("images//mine.png");
	flagT.loadFromFile("images//flag.png");
	//backgroundS.setColor(sf::Color::Black);
	
	int j = 0;
	int y = 0;

	for (int i = 0; i < 400; i++)
	{
		sf::Sprite bkg;
		bkg.setTexture(tileRevealed);
		//
		Tile tile;
		tile.col = j;
		tile.row = y;
		tile.positionIndex = i;
		j++;
		//sf::Sprite s(tileHidden);
		tile.s.setTexture(tileHidden);
		bkg.setPosition(32 * (j - 1), 32 * y);
		//std::cout << "(" << tile.col << "," << tile.row << ")"<< std::endl;
		tile.ifClicked = false;
		tile.ifHasMine = false;
		tile.isFlag = false;
		tile.s.setPosition(32 * (j - 1), 32 * y);
		tiles.push_back(tile);
		backgroundS.push_back(bkg);
		board[tile.col][tile.row] = tile;
		if (j % 25 == 0)
		{
			j = 0;
			y++;
		}
	}

	//create mine counter
	int mineCounter = 50;
	int mineNumber = 50;
	vector<sf::Sprite>digitCount;
	sf::Sprite mineCounts;
	sf::Texture t[11];
	for (int i = 0; i < 11; i++)
	{
		t[i].loadFromFile("images//digits.png", sf::IntRect(i * 21, 0, 21, 32));
	}
	vector<sf::Texture>mineCounterV;
	for (int i = 0; i < 11; i++)
	{
		mineCounterV.push_back(t[i]);
	}
	//setMineCounter(digitCount, mineCounts, mineCounterV);

	//creat near mine
	vector<sf::Texture>nearMineV;
	nearMineAddToVector(nearMineV);

	//draw face
	vector<sf::Texture>facesTextureV;
	faceAddtoVector(facesTextureV);

	//sf::Sprite faceS
	sf::Sprite faceS;
	faceS.setTexture(facesTextureV[0]);
	faceS.setPosition(368, 512);

	//draw debug
	sf::Texture debugT;
	debugT.loadFromFile("images//debug.png");
	sf::Sprite debugS(debugT);
	debugS.setPosition(496, 512);

	//draw test123
	sf::Texture test1T, test2T, test3T;
	test1T.loadFromFile("images//test_1.png");
	test2T.loadFromFile("images//test_2.png");
	test3T.loadFromFile("images//test_3.png");
	sf::Sprite test1S(test1T), test2S(test2T), test3S(test3T);
	test1S.setPosition(560, 512);
	test2S.setPosition(624, 512);
	test3S.setPosition(688, 512);

	resetGame(tiles, board, tileHidden, facesTextureV, faceS, mineCounter, isLost, isWin);
	randGame(tiles, board);
	while (window.isOpen())
	{ 
		auto mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mp(mousePos);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//cout << "Hi  " << index;
				if (isTileClicked(tiles, mp, index) == true)
				{
					tiles[index].ifClicked = true;
					board[tiles[index].col][tiles[index].row].ifClicked = true;
					//tiles[index].s.setTexture(tileRevealed);
					//board[tiles[index].col][tiles[index].row].s.setTexture(tileRevealed);
					setTile(tiles, board, index, tiles[index], tileRevealed, nearMineV, mineT, isLost);
				}
				else if (isRestClicked(tiles,mp, faceS) == true)
				{
					resetGame(tiles, board, tileHidden, facesTextureV, faceS, mineCounter, isLost, isWin);
					randGame(tiles, board);
				}
				else if (test1S.getGlobalBounds().contains(mp) == true)
				{
					//loads test board
					vector<char>mineMap;
					resetGame(tiles, board, tileHidden, facesTextureV, faceS, mineCounter, isLost, isWin);
					openFile(tiles, board, mineMap, "boards//testboard1.brd", mineCounter, mineNumber);
				}
				else if (test2S.getGlobalBounds().contains(mp) == true)
				{
					vector<char>mineMap;
					resetGame(tiles, board, tileHidden, facesTextureV, faceS, mineCounter, isLost, isWin);
					//loads test board
					openFile(tiles, board, mineMap, "boards//testboard2.brd", mineCounter, mineNumber);
				}
				else if (test3S.getGlobalBounds().contains(mp) == true)
				{
					vector<char>mineMap;
					resetGame(tiles, board, tileHidden, facesTextureV, faceS, mineCounter, isLost, isWin);
					//loads test board
					openFile(tiles, board, mineMap, "boards//testboard3.brd", mineCounter, mineNumber);
				}
				else if (debugS.getGlobalBounds().contains(mp) == true)
				{
					//debug mode
					debugGame(tiles, board, mineT, tileRevealed, nearMineV);
					//setTile(tiles[index], tileRevealed, nearMineV, mineT);
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (isTileClicked(tiles, mp, index) == true)
				{
					if (tiles[index].isFlag == false && tiles[index].ifClicked == false)
					{
						tiles[index].isFlag = true;
						board[tiles[index].col][tiles[index].row].isFlag = true;
						tiles[index].s.setTexture(flagT);
						board[tiles[index].col][tiles[index].row].s.setTexture(flagT);
						mineCounter = mineCounter - 1;
					}
					else if (tiles[index].isFlag == true && tiles[index].ifClicked == false)
					{
						tiles[index].isFlag = false;
						board[tiles[index].col][tiles[index].row].isFlag = false;
						tiles[index].s.setTexture(tileHidden);
						board[tiles[index].col][tiles[index].row].s.setTexture(tileHidden);
						mineCounter = mineCounter + 1;
					}
					setMineCounter(digitCount, mineCounts, mineCounterV, mineCounter);
				}

			}

			//checks game status
			checkIfwin(tiles, board, mineCounter, mineNumber,isLost, isWin);
			if (isLost==true) 
			{
				faceS.setTexture(facesTextureV[1]);
				debugGame(tiles, board, mineT, tileRevealed, nearMineV);
			}
			else if (isWin == true)
			{
				faceS.setTexture(facesTextureV[2]);
			}
			//window.draw(backgroundS);
			drawAll(tiles, backgroundS,digitCount, window, faceS, debugS, test1S, test2S, test3S, mineCounterV, mineCounts, mineCounter);
			
			//window.draw(testS);
			window.display();
		}
	}
	return 0;
}