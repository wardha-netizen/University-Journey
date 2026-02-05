#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

int showMenu();
string getPlayerName();
void saveScore(const string& name, int score);
void showLeaderboard();

// ---------------- Snake Body Node ----------------
struct Node {
    int x, y;
    Node* next;
    Node* prev;
    Node(int xPos, int yPos) : x(xPos), y(yPos), next(nullptr), prev(nullptr) {}
};

// ---------------- Snake Class ----------------
class Snake {
private:
    Node* head;
    Node* tail;
    int length;

public:
    Snake(int startX, int startY) {
        head = new Node(startX, startY);
        tail = head;
        length = 1;
    }

    ~Snake() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addHead(int x, int y) {
        Node* newHead = new Node(x, y);
        newHead->next = head;
        head->prev = newHead;
        head = newHead;
        length++;
    }

    void removeTail() {
        if (!tail) return;
        if (tail->prev) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            length--;
        }
    }

    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    int getLength() const { return length; }

    bool checkCollisionWithSelf(int x, int y) const {
        Node* current = head->next;
        while (current) {
            if (current->x == x && current->y == y)
                return true;
            current = current->next;
        }
        return false;
    }

    bool isBodyPart(int x, int y) const {
        Node* current = head;
        while (current) {
            if (current->x == x && current->y == y)
                return true;
            current = current->next;
        }
        return false;
    }
};

// ---------------- Game Class ----------------
class Game {
private:
    Snake* snake;
    int foodX, foodY;
    int dirX, dirY;
    bool gameOver;
    int score;

public:
    Game() {
        snake = new Snake(WIDTH / 2, HEIGHT / 2);
        dirX = 1; dirY = 0;
        gameOver = false;
        score = 0;
        srand(static_cast<unsigned int>(time(0)));
        generateFood();
    }

    ~Game() { delete snake; }

    void generateFood() {
        do {
            foodX = rand() % (WIDTH - 2) + 1;
            foodY = rand() % (HEIGHT - 2) + 1;
        } while (snake->isBodyPart(foodX, foodY));
    }

    void handleInput() {
        if (_kbhit()) {
            char key = _getch();
            if ((key == 'w' || key == 'W' || key == 72) && dirY != 1) {
                dirX = 0; dirY = -1;
            }
            else if ((key == 's' || key == 'S' || key == 80) && dirY != -1) {
                dirX = 0; dirY = 1;
            }
            else if ((key == 'a' || key == 'A' || key == 75) && dirX != 1) {
                dirX = -1; dirY = 0;
            }
            else if ((key == 'd' || key == 'D' || key == 77) && dirX != -1) {
                dirX = 1; dirY = 0;
            }
            else if (key == 27) {
                gameOver = true;
            }
        }
    }

    void update() {
        Node* head = snake->getHead();
        int newX = head->x + dirX;
        int newY = head->y + dirY;

        // Collision with wall or self
        if (newX <= 0 || newX >= WIDTH - 1 || newY <= 0 || newY >= HEIGHT - 1 ||
            snake->checkCollisionWithSelf(newX, newY)) {
            gameOver = true;
            return;
        }

        snake->addHead(newX, newY);
        if (newX == foodX && newY == foodY) {
            score += 10;
            generateFood();
        }
        else {
            snake->removeTail();
        }
    }

    void draw() {
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1)
                    cout << "#";
                else if (x == foodX && y == foodY)
                    cout << "*";
                else if (snake->isBodyPart(x, y)) {
                    if (x == snake->getHead()->x && y == snake->getHead()->y)
                        cout << "O";
                    else
                        cout << "o";
                }
                else
                    cout << " ";
            }
            cout << "\n";
        }

        cout << "Score: " << score << " | Length: " << snake->getLength() << endl;
        cout << "Controls: W/A/S/D or Arrows | ESC to quit" << endl;
    }

    void run() {
        CONSOLE_CURSOR_INFO cursorInfo;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        while (!gameOver) {
            handleInput();
            update();
            draw();
            Sleep(100);
        }

        cout << "\nGame Over! Final Score: " << score << endl;
        cout << "Press any key to continue..." << endl;
        _getch();
    }

    int getScore() const { return score; }
};

// ---------------- Helper Functions ----------------
int showMenu() {
    cout << "=== Snake Game ===\n";
    cout << "1. Play Game\n";
    cout << "2. View Leaderboard\n";
    cout << "3. Quit\n";
    cout << "Choose an option: ";
    int choice;
    cin >> choice;
    return choice;
}

string getPlayerName() {
    cout << "Enter your name: ";
    string name;
    cin >> name;
    return name;
}

void saveScore(const string& name, int score) {
    ofstream file("leaderboard.txt", ios::app);
    if (file.is_open()) {
        file << name << " " << score << endl;
        file.close();
    }
}

void showLeaderboard() {
    cout << "\n=== Leaderboard ===\n";
    ifstream file("leaderboard.txt");
    vector<pair<string, int>> scores;

    if (file.is_open()) {
        string name;
        int score;
        while (file >> name >> score) {
            scores.push_back({ name, score });
        }
        file.close();
    }

    sort(scores.begin(), scores.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    for (size_t i = 0; i < scores.size() && i < 10; ++i) {
        cout << i + 1 << ". " << scores[i].first << " - " << scores[i].second << "\n";
    }

    cout << "\nPress any key to return to menu...\n";
    _getch();
}

// ---------------- Main Function ----------------
int main() {
    while (true) {
        system("cls");
        int choice = showMenu();

        if (choice == 1) {
            string playerName = getPlayerName();
            Game game;
            game.run();
            saveScore(playerName, game.getScore());
        }
        else if (choice == 2) {
            showLeaderboard();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
            Sleep(1000);
        }
    }

    return 0;
}