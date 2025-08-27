#include "raylib.h"
#include "resource_dir.h"

class Game{
public:

	void Init() {

		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

		InitWindow(m_ScreenSize.x, m_ScreenSize.y, "Hello Raylib");

		m_BallVelocity = { (float)GetRandomValue(1,1), (float)GetRandomValue(-1,1)};

		//SearchAndSetResourceDir("resources");

		while (!WindowShouldClose())
		{
			GameLoop();
		}

		CloseWindow();
	}

	void GameLoop() {

		BeginDrawing();

		ClearBackground(DARKGREEN);
	
		DrawPlayer();

		DrawBall();

		//DrawEnemy();

		EndDrawing();
	}

private:

	void DrawEnemy() {

		m_EnemyPos.y = m_BallPos.y;

		DrawRectangle(m_EnemyPos.x, m_EnemyPos.y, m_PlayerSize.x, m_PlayerSize.y, WHITE);
	}

	void DrawBall() {

		m_BallPos.x += m_BallVelocity.x * m_BallMoveSpeed;
		m_BallPos.y += m_BallVelocity.y * m_BallMoveSpeed;

		if (m_BallPos.y > m_ScreenSize.y - 10 || m_BallPos.y < 0)
			m_BallVelocity.y = -m_BallVelocity.y;

		if (m_BallPos.x > m_PlayerPos.x - (m_PlayerSize.x / 2 - 10)) {
			if (m_BallPos.y > m_PlayerPos.y - (m_PlayerSize.y / 2) && m_BallPos.y < m_PlayerPos.y + (m_PlayerSize.y / 2))
				m_BallVelocity.x = -m_BallVelocity.x;
		}

		DrawCircle(m_BallPos.x, m_BallPos.y, 10, WHITE);
	}

	void DrawPlayer() {

		m_PlayerRect.max = { m_PlayerPos.x - (m_PlayerSize.x / 2), m_PlayerPos.x + (m_PlayerSize.y / 2),0 };
		m_PlayerRect.min = {m_PlayerPos.x + (m_PlayerSize.x / 2), m_PlayerPos.x - (m_PlayerSize.y / 2), 0};

		if (IsKeyDown(KEY_W)) {

			if (m_PlayerPos.y > 0)
				m_PlayerPos.y -= m_PlayerMoveSpeed;
			
		}
		else if (IsKeyDown(KEY_S)) {

			if (m_PlayerPos.y < m_ScreenSize.y - 75)
				m_PlayerPos.y += m_PlayerMoveSpeed;
			
		}
		DrawRectangle(m_PlayerPos.x, m_PlayerPos.y, m_PlayerSize.x, m_PlayerSize.y, WHITE);
	
		DrawBoundingBox(m_PlayerRect, BLUE);
	}

private:

	const Vector2 m_ScreenSize{ 900,600 };

	Vector2 m_PlayerPos{ m_ScreenSize.x - 50, m_ScreenSize.y / 2 };

	Vector2 m_EnemyPos{ 50, m_ScreenSize.y / 2 };

	const int m_PlayerMoveSpeed = 10;
	const int m_BallMoveSpeed = 2;

	const Vector2 m_PlayerSize = { 25,75 };
	
	BoundingBox m_PlayerRect = { };

	Vector2 m_BallVelocity = {};
	Vector2 m_BallPos = {m_ScreenSize.x / 2, m_ScreenSize.y / 2 };
};