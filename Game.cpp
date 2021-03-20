#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

enum eDirection {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

bool loop = true;
bool gameOver;
bool menuPause;
bool gameStarted;
const int fieldWidth = 40;
const int fieldHeight = 20;

char wallChar = '|';
char fruitChar = 'F';
char snakeChar = '0';

int tailX[100], tailY[100], nTail;

int x, y, fruitX, fruitY, score;

eDirection direction;

void Screen(const char *string);

void positionFruit() {
  fruitX = rand() % fieldWidth;
  fruitY = rand() % fieldHeight;
}

void Setup() {
  HWND console = GetConsoleWindow();
  RECT ConsoleRect;
  GetWindowRect(console, &ConsoleRect);

  MoveWindow(
          console,
          ConsoleRect.left,
          ConsoleRect.top,
          500,
          500,
          TRUE
  );


  loop = true;
  gameOver = false;
  menuPause = true;
  gameStarted = false;
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
      else {
        bool print = false;
        for (int k = 0; k < nTail; k++) {
          if (tailX[k] == j && tailY[k] == i) {
            print = true;
            std::cout << 'o';
          }
        }
        if (!print)
          std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < fieldWidth + 1; i++)
    std::cout << wallChar;

  std::cout << std::endl << std::endl;

  std::cout << "Score: " << score << std::endl;
}

void gameOverAction() {
  gameOver = true;
  menuPause = false;
  gameStarted = false;
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
  int prevX = tailX[0];
  int prevY = tailY[0];

  int prev2X, prev2Y;

  tailX[0] = x;
  tailY[0] = y;

  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];

    tailX[i] = prevX;
    tailY[i] = prevY;

    prevX = prev2X;
    prevY = prev2Y;
  }

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

  if (x >= fieldWidth - 1)
    x = 0;
  else if (x < 0)
    x = fieldWidth - 2;

  if (y >= fieldHeight - 1)
    y = 0;
  else if (y < 0)
    y = fieldHeight - 2;

  for (int i = 0; i < nTail; i++) {
    if (tailX[i] == x && tailY[i] == y) {
      gameOverAction();
    }
  }

  if (x == fruitX && y == fruitY) {
    score += rand();
    positionFruit();

    nTail = nTail + 1;
  }
}

void Screen(const char *screenName) {
  if (!gameStarted) {
    system("cls");
  }

  switch (*screenName) {
    case *"Game": {
      Draw();
      Input();
      Logic();

      break;
    }

    case *"gameOver": {
      std::cout << "GAME OVER!" << std::endl;
      std::cout << "YOUR SCORE: " << score << std::endl;
      std::cout << std::endl;
//      std::cout << "PRESS 'B' FOR GOING TO BACK 'START MENU'" << std::endl;
      std::cout << "PRESS 'Q' FOR CLOSE GAME" << std::endl;

      if (_kbhit()) {
        switch (_getch()) {
          case 'q': {
            loop = false;
            break;
          }
        }
      }

      break;
    }

    case *"StartMenu": {
      std::cout << "-------SNAKE GAME-------" << std::endl;
      std::cout << "\n\n";
      std::cout << "PRESS 'S' FOR START GAME" << std::endl;
      std::cout << "PRESS 'Q' FOR CLOSE GAME" << std::endl;
      std::cout << "\n\n";
      std::cout << "------------------------" << std::endl;
      std::cout << "install the English keyboard" << std::endl;

      if (_kbhit()) {
        switch (_getch()) {
          case 's' : {
            gameOver = false;
            menuPause = false;
            gameStarted = true;
            break;
          }

          case 'q': {
            loop = false;
            break;
          }
        }
      }

      break;
    }
  }
};

void Loop() {
  if (menuPause) {
    Screen("StartMenu");
  }

  if (gameOver) {
    Screen("gameOver");
  }

  if (gameStarted) {
    Screen("Game");
  }
}

int main() {
  Setup();

  while (loop) {
    Loop();
  }

  return 0;
}