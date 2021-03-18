#include <iostream>
#include <conio.h>
#include <stdlib.h>

enum eDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

bool gameOver;
const int fieldWidth = 30;
const int fieldHeight = 20;

char wallChar = '#';
char fruitChar = '@';
char snakeChar = '0';

int x, y, fruitX, fruitY, score;

eDirection direction;

void positionFruit()
{
  fruitX = rand() % fieldWidth;
  fruitY = rand() % fieldHeight;
}

void Setup()
{
  gameOver = false;
  score = 0;
  direction = STOP;

  x = fieldWidth / 2 - 1;
  y = fieldHeight / 2 - 1;

  positionFruit();
}

void Draw() {
  system("cls"); // clear command line's;

  for (int i = 0; i < fieldWidth + 1; i++)
    std::cout << wallChar;
  std::cout << std::endl;

  for (int i = 0; i < fieldHeight; i++) {
    for (int j = 0; j < fieldWidth; j++) {
      if (j == 0 || j == fieldWidth - 1)
        std::cout << wallChar;

      if (i == y && j == x)
        std::cout << snakeChar;
      else if (i == fruitY && j == fruitX)
        std::cout << fruitChar;
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < fieldWidth + 1; i++)
    std::cout << wallChar;

  std::cout << std::endl << std::endl;

  std::cout << "Score: " << score << std::endl;
}

void Input() {
  if (_kbhit()) {
    switch (_getch()) {
      case 'a':
        direction = LEFT;
        break;
      case 'd':
        direction = RIGHT;
        break;
      case 'w':
        direction = UP;
        break;
      case 's':
        direction = DOWN;
        break;

      case 'x':
        gameOver = true;
        break;

      default:
        break;
    }
  }
}

void Logic() {
  switch (direction) {
    case LEFT:
      x = x - 1;
      break;
    case RIGHT:
      x = x + 1;
      break;
    case UP:
      y = y - 1;
      break;
    case DOWN:
      y = y + 1;
      break;
  }

  if (x > fieldWidth || x < 0 || y > fieldHeight || y < 0)
    gameOver = true;

  if (x == fruitX && y == fruitY)
  {
    score += rand();
    positionFruit();
  }
}

int main() {
  Setup();

  while (!gameOver) {
    Draw();
    Input();
    Logic();
  }

  return 0;
}