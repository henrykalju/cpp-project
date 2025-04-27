#include "gamestate.cpp"
#include "raylib.h"
#include <iostream>

Board board;

Color emptyColor{50, 50, 50, 255};
Color side1Color{255, 50, 50, 255};
Color side2Color{50, 50, 255, 255};

bool rectangleContainsVector(Rectangle rec, Vector2 v) {
	return rec.x <= v.x && rec.x + rec.width >= v.x && rec.y <= v.y && rec.y + rec.height >= v.y;
}

Color getPieceColor(SpacePlayer p) {
	switch (p) {
	case SpacePlayer::Empty: {
		return emptyColor;
	}
	case SpacePlayer::Player1Side1: {
		return side1Color;
	}
	case SpacePlayer::Player1Side2: {
		return side2Color;
	}
	case SpacePlayer::Player2Side1: {
		return side1Color;
	}
	case SpacePlayer::Player2Side2: {
		return side2Color;
	}
	};
	return Color(255, 255, 255, 255);
}

void drawPiece(SpacePlayer spacePlayer, Rectangle rec) {
	DrawRectangleRec(rec, getPieceColor(spacePlayer));
}

void drawBoard(float x, float y, float size) {
	float paddingPercent = 10.f;
	float pieceSizeWithPadding = size / ROW_COUNT;
	float pieceSize = pieceSizeWithPadding * (100.f - paddingPercent) / 100.f;
	Vector2 mousePos = GetMousePosition();

	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COL_COUNT; col++) {
			Rectangle rec{pieceSizeWithPadding * col + x, pieceSizeWithPadding * row + y, pieceSize,
			              pieceSize};

			drawPiece(board.spaces[row][col], rec);
			if (board.IsSpaceFlippable({row, col})) {
				DrawRectangleRec(rec, Color(255, 255, 255, 50));
			}

			if (!rectangleContainsVector(rec, mousePos)) {
				continue;
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				switch (board.Phase) {
				case TurnPhase::Place: {
					SpacePlayer p =
					    rec.x + rec.width / 2 < mousePos.x
					        ? (board.Turn == Player::Player1 ? SpacePlayer::Player1Side2
					                                         : SpacePlayer::Player2Side2)
					        : (board.Turn == Player::Player1 ? SpacePlayer::Player1Side1
					                                         : SpacePlayer::Player2Side1);
					if (board.Place({row, col}, p)) {
						drawPiece(board.spaces[row][col], rec);
					}
					break;
				}
				case TurnPhase::Flip: {
					if (!board.IsSpaceFlippable({row, col})) {
						continue;
					}
				}
				}
			}
			switch (board.Phase) {
			case TurnPhase::Place: {
				if (board.spaces[row][col] == SpacePlayer::Empty) {
					DrawRectangleRec({rec.x, rec.y, rec.width / 2, rec.height}, side1Color);
					DrawRectangleRec({rec.x + rec.width / 2, rec.y, rec.width / 2, rec.height},
					                 side2Color);
				}
				break;
			}
			case TurnPhase::Flip: {
				if (!board.IsSpaceFlippable({row, col})) {
					continue;
				}
				DrawTriangle({rec.x, rec.y}, {rec.x, rec.y + rec.height},
				             {rec.x + rec.width / 2, rec.y + rec.height / 2},
				             getPieceColor(board.spaces[row][col]));
				break;
			}
			}
		}
	}
}

int screenWidth = 600;
int screenHeight = 600;

void update() {

	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = MAROON;
}

void draw() {
	BeginDrawing();

	ClearBackground(BLACK);

	drawBoard(100.f, 50.f, 300.f);

	EndDrawing();
}
int main() {
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		update();
		draw();
	}

	CloseWindow();
	return 0;
}
