#include <raylib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Player structure to track alive/dead status and visual properties
struct Player
{
	int position;
	bool dead;
	Vector2 visualPos;
	Color color;

	Player(int pos = 0)
	{
		position = pos;
		dead = false;
		color = BLUE;
	}
};

template <typename T>
class Node
{
public:
	T data;
	Node<T> *next;

	Node(const T &val)
	{
		data = val;
		next = nullptr;
	}
};

template <typename T>
class Queue
{
private:
	Node<T> *front;
	Node<T> *rear;
	int size;

public:
	Queue()
	{
		front = nullptr;
		rear = nullptr;
		size = 0;
	}

	~Queue()
	{
		while (!isEmpty())
		{
			dequeue();
		}
	}

	bool isEmpty()
	{
		return front == nullptr;
	}

	void enqueue(const T &val)
	{
		Node<T> *newNode = new Node<T>(val);
		if (isEmpty())
		{
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		size++;
	}

	T dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty!" << endl;
			return T();
		}

		Node<T> *temp = front;
		T data = front->data;
		front = front->next;

		if (front == nullptr)
		{
			rear = nullptr;
		}

		delete temp;
		size--;
		return data;
	}

	T getFront()
	{
		if (isEmpty())
		{
			cout << "Queue empty!" << endl;
			return T();
		}
		return front->data;
	}

	int getSize()
	{
		return size;
	}
};

class ModernJosephusGame
{
private:
	vector<Player> players;
	int totalPlayers;
	int currentPlayer;
	int k;
	int step;
	bool gameStarted;
	bool gameFinished;
	bool isPaused;
	int survivor;
	float gameSpeed;
	float timer;
	int screenWidth, screenHeight;
	Vector2 center;
	float radius;

	// Visual effects
	float glowAnimation;
	Color backgroundColor;
	Color accentColor;

public:
	ModernJosephusGame(int w, int h)
	{
		screenWidth = w;
		screenHeight = h;
		center = {w / 2.0f, h / 2.0f};
		radius = min(w, h) * 0.3f;

		totalPlayers = 7;
		currentPlayer = 0;
		k = 2;
		step = 1;
		gameStarted = false;
		gameFinished = false;
		isPaused = false;
		survivor = -1;
		gameSpeed = 1.0f;
		timer = 0.0f;
		glowAnimation = 0.0f;

		backgroundColor = {15, 25, 35, 255};
		accentColor = {0, 230, 118, 255};

		setupPlayers();
	}

	void setupPlayers()
	{
		players.clear();
		float angleStep = 2 * PI / totalPlayers;

		for (int i = 0; i < totalPlayers; i++)
		{
			Player p(i + 1);
			float angle = i * angleStep - PI / 2;
			p.visualPos.x = center.x + radius * cos(angle);
			p.visualPos.y = center.y + radius * sin(angle);
			p.color = {70, 130, 255, 255}; // Modern blue
			players.push_back(p);
		}
	}

	void update()
	{
		glowAnimation += GetFrameTime() * 3.0f;

		if (!gameStarted || gameFinished || isPaused)
			return;

		timer += GetFrameTime();
		if (timer < (2.0f - gameSpeed)) // Adjustable speed
			return;
		timer = 0.0f;

		// Count alive players
		int aliveCount = 0;
		for (const auto &p : players)
			if (!p.dead)
				aliveCount++;

		if (aliveCount <= 1)
		{
			// Find survivor
			for (auto &p : players)
			{
				if (!p.dead)
				{
					survivor = p.position;
					p.color = {255, 215, 0, 255}; // Gold
					break;
				}
			}
			gameFinished = true;
			return;
		}

		// Find next alive player
		int originalPlayer = currentPlayer;
		do
		{
			currentPlayer = (currentPlayer + 1) % totalPlayers;
		} while (players[currentPlayer].dead);

		// Highlight current player
		for (auto &p : players)
		{
			if (!p.dead)
			{
				if (p.position == players[currentPlayer].position)
					p.color = {0, 255, 127, 255}; // Bright green
				else
					p.color = {70, 130, 255, 255}; // Blue
			}
		}

		if (step == k)
		{
			// Eliminate current player
			players[currentPlayer].dead = true;
			players[currentPlayer].color = {255, 69, 69, 255}; // Red
			step = 1;
		}
		else
		{
			step++;
		}
	}

	void draw()
	{
		// Gradient background
		DrawRectangleGradientV(0, 0, screenWidth, screenHeight,
													 {15, 25, 35, 255}, {5, 15, 25, 255});

		// Title with glow effect
		const char *title = "JOSEPHUS ELIMINATION GAME";
		int titleSize = screenWidth / 25;
		int titleWidth = MeasureText(title, titleSize);
		Vector2 titlePos = {center.x - titleWidth / 2, 50};

		// Glow effect
		Color glowColor = {accentColor.r, accentColor.g, accentColor.b,
											 (unsigned char)(50 + 30 * sin(glowAnimation))};
		for (int i = 1; i <= 3; i++)
		{
			DrawText(title, titlePos.x - i, titlePos.y - i, titleSize, glowColor);
			DrawText(title, titlePos.x + i, titlePos.y + i, titleSize, glowColor);
		}
		DrawText(title, titlePos.x, titlePos.y, titleSize, WHITE);

		// Draw outer circle with glow
		float outerRadius = radius + 60;
		Color circleGlow = {accentColor.r, accentColor.g, accentColor.b, 30};
		DrawCircleLines(center.x, center.y, outerRadius + 5, circleGlow);
		DrawCircleLines(center.x, center.y, outerRadius, accentColor);

		// Draw players with modern styling
		for (const auto &player : players)
		{
			float playerRadius = 35;

			// Player glow effect
			if (!player.dead)
			{
				Color playerGlow = player.color;
				playerGlow.a = 50;
				DrawCircleV(player.visualPos, playerRadius + 10, playerGlow);
			}

			// Player circle
			DrawCircleV(player.visualPos, playerRadius, player.color);

			// Player border
			Color borderColor = player.dead ? (Color){100, 100, 100, 255} : WHITE;
			DrawCircleLines(player.visualPos.x, player.visualPos.y, playerRadius, borderColor);

			// Player number with better typography
			string playerText = to_string(player.position);
			int fontSize = 24;
			int textWidth = MeasureText(playerText.c_str(), fontSize);
			Vector2 textPos = {
					player.visualPos.x - textWidth / 2,
					player.visualPos.y - fontSize / 2};

			// Text shadow
			DrawText(playerText.c_str(), textPos.x + 2, textPos.y + 2, fontSize, {0, 0, 0, 100});
			DrawText(playerText.c_str(), textPos.x, textPos.y, fontSize, WHITE);
		}

		// Game info panel
		drawInfoPanel();

		// Controls panel
		drawControlsPanel();
	}

	void drawInfoPanel()
	{
		// Make panel larger and ensure it fits on screen
		int panelWidth = 400;
		int panelHeight = 220;
		Rectangle panel = {50, screenHeight - panelHeight - 50, panelWidth, panelHeight};

		// Panel background with transparency
		DrawRectangleRounded(panel, 0.1f, 10, {0, 0, 0, 180});
		DrawRectangleRoundedLines(panel, 0.1f, 10, 3, accentColor);

		float y = panel.y + 20;
		int fontSize = 22;

		DrawText("GAME STATUS", panel.x + 20, y, fontSize, accentColor);
		y += 40;

		// Game configuration info
		string playersText = "Total Players: " + to_string(totalPlayers);
		string stepText = "Step Count (k): " + to_string(k);
		string speedText = "Game Speed: " + to_string((int)(gameSpeed * 100)) + "%";

		DrawText(playersText.c_str(), panel.x + 20, y, 18, WHITE);
		y += 28;
		DrawText(stepText.c_str(), panel.x + 20, y, 18, WHITE);
		y += 28;
		DrawText(speedText.c_str(), panel.x + 20, y, 18, WHITE);
		y += 28;

		// Game state info
		if (gameStarted && !gameFinished)
		{
			int aliveCount = 0;
			for (const auto &p : players)
				if (!p.dead)
					aliveCount++;

			string aliveText = "Players Alive: " + to_string(aliveCount);
			string currentText = "Current Step: " + to_string(step);

			DrawText(aliveText.c_str(), panel.x + 20, y, 18, {0, 255, 127, 255});
			y += 28;
			DrawText(currentText.c_str(), panel.x + 20, y, 18, {0, 255, 127, 255});
		}
		else if (gameFinished)
		{
			y += 10;
			string survivorText = "🏆 WINNER: Player " + to_string(survivor) + " 🏆";
			DrawText(survivorText.c_str(), panel.x + 20, y, 20, {255, 215, 0, 255});
		}
		else
		{
			DrawText("Ready to start!", panel.x + 20, y, 18, {150, 150, 150, 255});
		}
	}

	void drawControlsPanel()
	{
		// Make panel larger and ensure it fits on screen
		int panelWidth = 420;
		int panelHeight = 280;
		Rectangle panel = {screenWidth - panelWidth - 50, screenHeight - panelHeight - 50, panelWidth, panelHeight};

		// Panel background
		DrawRectangleRounded(panel, 0.1f, 10, {0, 0, 0, 180});
		DrawRectangleRoundedLines(panel, 0.1f, 10, 3, accentColor);

		float y = panel.y + 20;
		int fontSize = 22;

		DrawText("CONTROLS", panel.x + 20, y, fontSize, accentColor);
		y += 40;

		if (!gameStarted)
		{
			DrawText("⬆⬇ Arrow Keys: Adjust Players (3-20)", panel.x + 20, y, 16, WHITE);
			y += 24;
			DrawText("⬅➡ Arrow Keys: Change Step Count (1-10)", panel.x + 20, y, 16, WHITE);
			y += 24;
			DrawText("Q / E Keys: Decrease / Increase Speed", panel.x + 20, y, 16, WHITE);
			y += 24;
			DrawText("ENTER: Start the Elimination Game", panel.x + 20, y, 18, {0, 255, 127, 255});
			y += 30;
		}
		else if (!gameFinished)
		{
			DrawText("SPACEBAR: Pause / Resume Game", panel.x + 20, y, 16, WHITE);
			y += 24;
			DrawText("Q / E Keys: Adjust Game Speed", panel.x + 20, y, 16, WHITE);
			y += 30;

			if (isPaused)
			{
				DrawText("⏸ GAME PAUSED", panel.x + 20, y, 18, {255, 255, 0, 255});
				y += 30;
			}
			else
			{
				DrawText("▶ GAME RUNNING", panel.x + 20, y, 18, {0, 255, 127, 255});
				y += 30;
			}
		}
		else
		{
			DrawText("🎉 Game Complete!", panel.x + 20, y, 18, {255, 215, 0, 255});
			y += 30;
		}

		// Always visible controls
		DrawText("R: Reset Game & Settings", panel.x + 20, y, 16, WHITE);
		y += 24;
		DrawText("F11: Toggle Fullscreen Mode", panel.x + 20, y, 16, WHITE);
		y += 24;
		DrawText("ESC: Exit Application", panel.x + 20, y, 16, WHITE);

		// Show current state at bottom
		y += 30;
		if (gameStarted && !gameFinished)
		{
			string stateText = isPaused ? "Status: PAUSED" : "Status: ACTIVE";
			Color stateColor = isPaused ? (Color){255, 255, 0, 255} : (Color){0, 255, 127, 255};
			DrawText(stateText.c_str(), panel.x + 20, y, 16, stateColor);
		}
	}

	void handleInput()
	{
		// Toggle fullscreen
		if (IsKeyPressed(KEY_F11))
		{
			if (IsWindowFullscreen())
			{
				// Going from fullscreen to windowed
				ToggleFullscreen();
				SetWindowSize(1200, 800);
				SetWindowPosition(100, 50); // Center on screen
			}
			else
			{
				// Going from windowed to fullscreen
				ToggleFullscreen();
			}

			// Update screen dimensions after toggle
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
			center = {screenWidth / 2.0f, screenHeight / 2.0f};
			radius = min(screenWidth, screenHeight) * 0.3f;
			setupPlayers(); // Reposition players
		}

		if (IsKeyPressed(KEY_R))
		{
			reset();
		}

		if (!gameStarted)
		{
			if (IsKeyPressed(KEY_UP) && totalPlayers < 20)
			{
				totalPlayers++;
				setupPlayers();
			}
			if (IsKeyPressed(KEY_DOWN) && totalPlayers > 3)
			{
				totalPlayers--;
				setupPlayers();
			}
			if (IsKeyPressed(KEY_RIGHT) && k < 10)
			{
				k++;
			}
			if (IsKeyPressed(KEY_LEFT) && k > 1)
			{
				k--;
			}
			if (IsKeyPressed(KEY_ENTER))
			{
				startGame();
			}
		}
		else if (!gameFinished)
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				isPaused = !isPaused;
			}
		}

		// Speed control
		if (IsKeyPressed(KEY_Q) && gameSpeed > 0.1f)
		{
			gameSpeed -= 0.2f;
		}
		if (IsKeyPressed(KEY_E) && gameSpeed < 1.8f)
		{
			gameSpeed += 0.2f;
		}
	}

	void startGame()
	{
		gameStarted = true;
		gameFinished = false;
		isPaused = false;
		currentPlayer = -1; // Will be incremented to 0 in first update
		step = 1;
		timer = 0.0f;
	}

	void reset()
	{
		gameStarted = false;
		gameFinished = false;
		isPaused = false;
		currentPlayer = 0;
		step = 1;
		survivor = -1;
		timer = 0.0f;
		setupPlayers();
	}
};

int main()
{
	// Initialize in windowed mode first
	int screenWidth = 1200;
	int screenHeight = 800;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Josephus Elimination Game - Modern GUI");
	SetTargetFPS(60);

	// Create the game
	ModernJosephusGame game(screenWidth, screenHeight);

	while (!WindowShouldClose())
	{
		game.handleInput();
		game.update();

		BeginDrawing();
		game.draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}