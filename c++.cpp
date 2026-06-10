#include <iostream>
#include <conio.h>
#include <windows.h>

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int dir;
bool gameOver;

void Setup() {
    gameOver = false;
    dir = 0; // 0 = STOP, 1 = LEFT, 2 = RIGHT, 3 = UP, 4 = DOWN
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) std::cout << '#';
    std::cout << '\n';

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) std::cout << '#';
            if (i == y && j == x)
                std::cout << 'O';
            else if (i == fruitY && j == fruitX)
                std::cout << 'F';
            else {
                bool printed = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << 'o';
                        printed = true;
                    }
                }
                if (!printed) std::cout << ' ';
            }
            if (j == width - 1) std::cout << '#';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < width + 2; i++) std::cout << '#';
    std::cout << "\nScore: " << score << '\n';
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': case 'A': dir = 1; break;
            case 'd': case 'D': dir = 2; break;
            case 'w': case 'W': dir = 3; break;
            case 's': case 'S': dir = 4; break;
            case 'x': case 'X': gameOver = true; break;
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

    switch (dir) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
        default: break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    std::cout << "Game over! Final score: " << score << "\n";
    return 0;
}