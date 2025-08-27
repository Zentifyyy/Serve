#include "raylib.h"
#include "resource_dir.h"

#include "string"

class ServeGame{
public:

	void Init() 
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

		InitWindow(m_ScreenSize.x, m_ScreenSize.y, "Serve");
		
		m_BallVelocity = { (float)GetRandomValue(1,1), (float)GetRandomValue(-1,1) };
		
		while (!WindowShouldClose())
		{
			GameLoop();
		}

		CloseWindow();
	}

private:

	void GameLoop() 
	{
		if (IsWindowResized()) {

			m_ScreenSize = { (float)GetScreenWidth(), (float)GetScreenHeight() };
			
			m_PlayerPos.x = m_ScreenSize.x - 50;
		}

		BeginDrawing();

		ClearBackground(DARKGREEN);

		DrawPlayer();

		DrawBall();

		DrawEnemy();

		score = std::to_string(m_EnemyScore) + " : " + std::to_string(m_PlayerScore);
		DrawText(score.c_str(), 150, 25, 50, WHITE);

		EndDrawing();
	}

	void DrawEnemy() {

		if (m_EnemyPos.y + (m_PlayerSize.y / 2) < m_BallPos.y ) {
			m_EnemyPos.y += m_EnemyMoveSpeed * GetFrameTime();
		}
		else if (m_EnemyPos.y + (m_PlayerSize.y / 2) > m_BallPos.y) {
			m_EnemyPos.y -= m_EnemyMoveSpeed * GetFrameTime();
		}

		DrawRectangle(m_EnemyPos.x, m_EnemyPos.y, m_PlayerSize.x, m_PlayerSize.y, WHITE);	
	}

	void DrawBall() 
	{
		m_BallPos.x += m_BallVelocity.x * m_BallMoveSpeed * GetFrameTime();
		m_BallPos.y += m_BallVelocity.y * m_BallMoveSpeed * GetFrameTime();

		if (m_BallPos.y > m_ScreenSize.y - 10 || m_BallPos.y < 0) {
			m_BallVelocity.y = -m_BallVelocity.y;
		}

		if (m_BallPos.x > m_ScreenSize.x) {
			m_EnemyScore++;
			ResetGame();
		}

		if (m_BallPos.x < 0) {
			m_PlayerScore++;
			ResetGame();
		}

		if (m_BallPos.x >= m_PlayerPos.x - (m_PlayerSize.x / 2 - 10)) {

			if (m_BallPos.y >= m_PlayerPos.y && m_BallPos.y <= (m_PlayerPos.y + m_PlayerSize.y)) {

				m_BallVelocity.x = -m_BallVelocity.x;

				if (IsKeyDown(KEY_W)) 
					m_BallVelocity.y += -0.1f;
				else if(IsKeyDown(KEY_S))
					m_BallVelocity.y += 0.1f;

				m_BallMoveSpeed *= 1.05f;
			}
		}

		if (m_BallPos.x <= m_EnemyPos.x + (m_PlayerSize.x + 10)) {

			if (m_BallPos.y >= m_EnemyPos.y && m_BallPos.y <= (m_EnemyPos.y + m_PlayerSize.y)) {

				m_BallVelocity.x = -m_BallVelocity.x;
				m_BallVelocity.y += GetRandomValue(-1, 1);

				m_BallMoveSpeed *= 1.05f;
			}
		}

		DrawCircle(m_BallPos.x, m_BallPos.y, 10, WHITE);
	}

	void DrawPlayer() 
	{
		DrawRectangle(m_PlayerPos.x, m_PlayerPos.y, m_PlayerSize.x, m_PlayerSize.y, WHITE);

		m_PlayerRect.max = { m_PlayerPos.x - (m_PlayerSize.x / 2), m_PlayerPos.x + (m_PlayerSize.y / 2),0 };
		m_PlayerRect.min = {m_PlayerPos.x + (m_PlayerSize.x / 2), m_PlayerPos.x - (m_PlayerSize.y / 2), 0};

		if (IsKeyDown(KEY_W)) {

			if (m_PlayerPos.y > 0)
				m_PlayerPos.y -= m_PlayerMoveSpeed * GetFrameTime();
			
		}
		else if (IsKeyDown(KEY_S)) {

			if (m_PlayerPos.y < m_ScreenSize.y - 75)
				m_PlayerPos.y += m_PlayerMoveSpeed * GetFrameTime();
			
		}
	}
	
	void ResetGame() 
	{
		m_PlayerPos = { m_ScreenSize.x - 50, m_ScreenSize.y / 2 };

		m_EnemyPos = { 50, m_ScreenSize.y / 2 };
		m_BallMoveSpeed = 250;

		m_BallVelocity = { (float)GetRandomValue(1,1), (float)GetRandomValue(-1,1) };
		m_BallPos = { m_ScreenSize.x / 2, m_ScreenSize.y / 2 };
	}

private:

	Vector2 m_ScreenSize{ 900,600 };

	Vector2 m_PlayerPos{ m_ScreenSize.x - 50, m_ScreenSize.y / 2 };

	Vector2 m_EnemyPos{ 50, m_ScreenSize.y / 2 };
	float m_EnemyTimer = 0;
	float m_EnemyInterval = 0.2f;
	int m_EnemyMoveSpeed = 400;

	const int m_PlayerMoveSpeed = 600;
	int m_BallMoveSpeed = 250;

	int m_PlayerScore = 0, m_EnemyScore = 0;
	std::string score = "";

	const Vector2 m_PlayerSize = { 25,75 };
	
	BoundingBox m_PlayerRect = { };

	Vector2 m_BallVelocity = {};
	Vector2 m_BallPos = {m_ScreenSize.x / 2, m_ScreenSize.y / 2 };
};