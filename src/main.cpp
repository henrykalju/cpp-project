#include "gamestate.cpp"
#include "raylib.h"
#include <iostream>

Board board;

Color emptyColor{50, 50, 50, 255};
Color side1Color{255, 50, 50, 255};
Color side2Color{50, 50, 255, 255};

Player GetPlayerFromSpacePlayer(SpacePlayer p) {
	assert(p != SpacePlayer::Empty);

	if (p == SpacePlayer::Player1Side1 || p == SpacePlayer::Player1Side2) {
		return Player::Player1;
	}

	return Player::Player2;
};

bool rectangleContainsVector(Rectangle rec, Vector2 v) {
	return rec.x <= v.x && rec.x + rec.width >= v.x && 
		   rec.y <= v.y && rec.y + rec.height >= v.y;
}

bool triangleContainsVector(Vector2 a, Vector2 b, Vector2 c, Vector2 pt)  {
    Vector2 v0 = { c.x - a.x, c.y - a.y };
    Vector2 v1 = { b.x - a.x, b.y - a.y };
    Vector2 v2 = { pt.x - a.x, pt.y - a.y };

    float dot00 = v0.x * v0.x + v0.y * v0.y;
    float dot01 = v0.x * v1.x + v0.y * v1.y;
    float dot02 = v0.x * v2.x + v0.y * v2.y;
    float dot11 = v1.x * v1.x + v1.y * v1.y;
    float dot12 = v1.x * v2.x + v1.y * v2.y;

    float denom = dot00 * dot11 - dot01 * dot01;
    if (denom == 0.0f) return false;

    float invDenom = 1.0f / denom;
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
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

void drawPlayerSymbol(Player p, Rectangle rec) {
float scale = 0.3;
	Rectangle rec2{
		rec.x + (1-scale)/2*rec.width,
		rec.y + (1-scale)/2*rec.height,
		rec.width*scale,
		rec.height*scale
	};
	switch (p)
	{
	case Player::Player1: 
		DrawRectangleRec(rec2, BLACK);
		break;
	case Player::Player2:
		DrawCircleV({rec.x + rec.width / 2, rec.y + rec.height / 2}, 10, BLACK);
		break;
	}
	
}

void drawPiece(SpacePlayer spacePlayer, Rectangle rec) {
	DrawRectangleRec(rec, getPieceColor(spacePlayer));
	if (spacePlayer == SpacePlayer::Empty) {
		return;
	}
	drawPlayerSymbol(GetPlayerFromSpacePlayer(spacePlayer), rec);
}

void drawBoard(float x, float y, float size) {
	float paddingPercent = 10.f;
	float pieceSizeWithPadding = size / ROW_COUNT;
	float pieceSize = pieceSizeWithPadding * (100.f - paddingPercent) / 100.f;
	Vector2 mousePos = GetMousePosition();
	
	Winner winner = board.GetWinner();

	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COL_COUNT; col++) {
			Rectangle rec{pieceSizeWithPadding * col + x, pieceSizeWithPadding * row + y, pieceSize,
			              pieceSize};

			drawPiece(board.spaces[row][col], rec);
			if (winner != Winner::None) {
				continue;
			}

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

					auto sides = board.GetEmptySides({row, col});
					Vector2 midpoint, ul, ur, dl, dr;
					midpoint = {rec.x + rec.width / 2, rec.y + rec.height / 2};
					ul = {rec.x, rec.y};
					ur = {rec.x + rec.width, rec.y};
					dl = {rec.x, rec.y + rec.height};
					dr = {rec.x + rec.width, rec.y + rec.height};
					for (auto s : sides) {
						Vector2 v1, v2, v3;
						switch (s)
						{
						case Up:
							v1 = ur;
							v2 = ul;
							v3 = midpoint;
							break;
						case Down:
							v1 = dl;
							v2 = dr;
							v3 = midpoint;
							break;
						case Left:
							v1 = ul;
							v2 = dl;
							v3 = midpoint;
							break;
						case Right:
							v1 = dr;
							v2 = ur;
							v3 = midpoint;
							break;
						}
						if (triangleContainsVector(v1, v2, v3, mousePos)) {
							board.Flip({row, col}, s);
							continue;
						}
					}
				}
				}
			}
			switch (board.Phase) {
			case TurnPhase::Place: {
				if (board.spaces[row][col] != SpacePlayer::Empty) {
					continue;
				}
				DrawRectangleRec({rec.x, rec.y, rec.width / 2, rec.height}, side1Color);
				DrawRectangleRec({rec.x + rec.width / 2, rec.y, rec.width / 2, rec.height},
									side2Color);
				drawPlayerSymbol(board.Turn, rec);
				break;
			}
			case TurnPhase::Flip: {
				if (!board.IsSpaceFlippable({row, col})) {
					continue;
				}
				auto sides = board.GetEmptySides({row, col});
				Vector2 midpoint, ul, ur, dl, dr;
				midpoint = {rec.x + rec.width / 2, rec.y + rec.height / 2};
				ul = {rec.x, rec.y};
				ur = {rec.x + rec.width, rec.y};
				dl = {rec.x, rec.y + rec.height};
				dr = {rec.x + rec.width, rec.y + rec.height};
				for (auto s : sides) {
					Vector2 v1, v2, v3;
					switch (s)
					{
					case Up:
						v1 = ur;
						v2 = ul;
						v3 = midpoint;
						break;
					case Down:
						v1 = dl;
						v2 = dr;
						v3 = midpoint;
						break;
					case Left:
						v1 = ul;
						v2 = dl;
						v3 = midpoint;
						break;
					case Right:
						v1 = dr;
						v2 = ur;
						v3 = midpoint;
						break;
					}
					if (!triangleContainsVector(v1, v2, v3, mousePos)) {
						continue;
					}
					DrawTriangle(v1, v2, v3, getPieceColor(board.spaces[row][col]));
				}
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
