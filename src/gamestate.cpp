#include <array>
#include <cassert>
#include <vector>

enum class SpacePlayer {
	Empty,
	Player1Side1,
	Player1Side2,
	Player2Side1,
	Player2Side2
};

enum class Player {
	Player1,
	Player2,
};

enum TurnPhase {
	Flip,
	Place,
};

enum class Winner {
	None,
	Player1,
	Player2,
	Tie,
};

enum Direction {
	Up,
	Down,
	Left,
	Right,
};

struct Coords {
	int row;
	int col;
};

const int ROW_COUNT = 4;
const int COL_COUNT = 4;

class Board {
  private:
	void AssertCoords(Coords c) {
		assert(c.row >= 0 && c.row <= 3 && c.col >= 0 && c.col <= 3);
	};

  public:
	Player Turn = Player::Player1;
	TurnPhase Phase = TurnPhase::Place;

	using SpacesType =
	    std::array<std::array<SpacePlayer, COL_COUNT>, ROW_COUNT>;
	SpacesType spaces;

	Board() {
		for (auto &row : spaces) {
			row.fill(SpacePlayer::Empty);
		}
	}

	SpacePlayer &GetSpace(Coords c) { return spaces[c.row][c.col]; };

	std::vector<Direction> GetEmptySides(Coords c) {
		AssertCoords(c);

		std::vector<Direction> r = {};

		if (c.row > 0 && spaces[c.row - 1][c.col] == SpacePlayer::Empty) {
			r.push_back(Up);
		}
		if (c.row < ROW_COUNT - 1 && spaces[c.row + 1][c.col] == SpacePlayer::Empty) {
			r.push_back(Down);
		}
		if (c.col > 0 && spaces[c.row][c.col - 1] == SpacePlayer::Empty) {
			r.push_back(Left);
		}
		if (c.col < COL_COUNT - 1 && spaces[c.row][c.col + 1] == SpacePlayer::Empty) {
			r.push_back(Right);
		}

		return r;
	};

	Winner GetWinner() {
		Winner winner = Winner::None;
		{
			for (int row = 0; row < ROW_COUNT - 2; row++) {
				for (int col = 0; col < COL_COUNT - 2; col++) {
					if (spaces[row][col] == SpacePlayer::Empty) {
						continue;
					}
					if (spaces[row][col] == spaces[row + 1][col + 1] &&
						spaces[row][col] == spaces[row + 2][col + 2]) {
						if (spaces[row][col] == SpacePlayer::Player1Side1 ||
							spaces[row][col] == SpacePlayer::Player1Side2) {
							winner =  Winner::Player1;
							goto afterLoops;
						}
						winner = Winner::Player2;
						goto afterLoops;
					}
				}
			}

			for (int row = 2; row < ROW_COUNT; row++) {
				for (int col = 0; col < COL_COUNT - 2; col++) {
					if (spaces[row][col] == SpacePlayer::Empty) {
						continue;
					}
					if (spaces[row][col] == spaces[row - 1][col + 1] &&
						spaces[row][col] == spaces[row - 2][col + 2]) {
						if (spaces[row][col] == SpacePlayer::Player1Side1 ||
							spaces[row][col] == SpacePlayer::Player1Side2) {
							winner = Winner::Player1;
							goto afterLoops;
						}
						winner = Winner::Player2;
						goto afterLoops;
					}
				}
			}

			for (int row = 0; row < ROW_COUNT; row++) {
				for (int col = 0; col < COL_COUNT - 2; col++) {
					if (spaces[row][col] == SpacePlayer::Empty) {
						continue;
					}
					if (spaces[row][col] == spaces[row][col + 1] &&
						spaces[row][col] == spaces[row][col + 2]) {
						if (spaces[row][col] == SpacePlayer::Player1Side1 ||
							spaces[row][col] == SpacePlayer::Player1Side2) {
							winner = Winner::Player1;
							goto afterLoops;
						}
						winner = Winner::Player2;
						goto afterLoops;
					}
				}
			}

			for (int row = 0; row < ROW_COUNT - 2; row++) {
				for (int col = 0; col < COL_COUNT; col++) {
					if (spaces[row][col] == SpacePlayer::Empty) {
						continue;
					}
					if (spaces[row][col] == spaces[row + 1][col] &&
						spaces[row][col] == spaces[row + 2][col]) {
						if (spaces[row][col] == SpacePlayer::Player1Side1 ||
							spaces[row][col] == SpacePlayer::Player1Side2) {
							winner = Winner::Player1;
							goto afterLoops;
						}
						winner = Winner::Player2;
						goto afterLoops;
					}
				}
			}

			int emptyCount = 0;
			for (int row = 0; row < ROW_COUNT; row++) {
				for (int col = 0; col < COL_COUNT; col++) {
					if (spaces[row][col] == SpacePlayer::Empty) {
						emptyCount++;
					}
				}
			}
			if (emptyCount == 0) {
				winner = Winner::Tie;
				goto afterLoops;
			}
			winner = Winner::None;
			goto afterLoops;
		}

		afterLoops:

		if (winner == Winner::None || winner == Winner::Tie) {
			return winner;
		}

		if (winner == Winner::Player1 && Phase == TurnPhase::Place && Turn == Player::Player2) {
			return winner;
		}

		if (winner == Winner::Player2 && Phase == TurnPhase::Place && Turn == Player::Player1) {
			return winner;
		}


		return Winner::None;
	};

	bool Flip(Coords c, Direction dir) {
		AssertCoords(c);

		bool good = false;
		for (auto d : GetEmptySides(c)) {
			if (d == dir) {
				good = true;
				break;
			}
		}

		if (!good) {
			return false;
		}

		SpacePlayer p = GetSpace(c);
		if (((p == SpacePlayer::Player1Side1 ||
		      p == SpacePlayer::Player1Side2) &&
		     Turn == Player::Player1) ||
		    ((p == SpacePlayer::Player2Side1 ||
		      p == SpacePlayer::Player2Side2) &&
		     Turn == Player::Player2)) {
			return false;
		}

		SpacePlayer target;

		switch (p) {
		case SpacePlayer::Empty:
			return false;
			break;
		case SpacePlayer::Player1Side1:
			target = SpacePlayer::Player1Side2;
			break;
		case SpacePlayer::Player1Side2:
			target = SpacePlayer::Player1Side1;
			break;
		case SpacePlayer::Player2Side1:
			target = SpacePlayer::Player2Side2;
			break;
		case SpacePlayer::Player2Side2:
			target = SpacePlayer::Player2Side1;
			break;
		default:
			break;
		}

		switch (dir) {
		case Up:
			spaces[c.row - 1][c.col] = target;
			break;
		case Down:
			spaces[c.row + 1][c.col] = target;
			break;
		case Left:
			spaces[c.row][c.col - 1] = target;
			break;
		case Right:
			spaces[c.row][c.col + 1] = target;
			break;

		default:
			break;
		}
		GetSpace(c) = SpacePlayer::Empty;

		Phase = TurnPhase::Place;
		return true;
	};

	bool Place(Coords c, SpacePlayer p) {
		AssertCoords(c);
		assert(p != SpacePlayer::Empty);

		if (Phase != TurnPhase::Place) {
			return false;
		}

		if (GetSpace(c) != SpacePlayer::Empty) {
			return false;
		}

		GetSpace(c) = p;

		Turn = Turn == Player::Player1 ? Player::Player2 : Player::Player1;
		Phase = TurnPhase::Flip;
		if (GetFlippableSpaces().empty()) {
			Phase = TurnPhase::Place;
		}
		return true;
	};

	std::vector<Coords> GetFlippableSpaces() {
		std::vector<Coords> r;
		if (Phase != TurnPhase::Flip) {
			return r;
		}

		for (int row = 0; row < ROW_COUNT; row++) {
			for (int col = 0; col < COL_COUNT; col++) {
				Coords c = {.row = row, .col = col};
				SpacePlayer p = GetSpace(c);
				if (p == SpacePlayer::Empty) {
					continue;
				}

				if (GetEmptySides(c).empty()) {
					continue;
				}

				if (((p == SpacePlayer::Player1Side1 ||
				      p == SpacePlayer::Player1Side2) &&
				     Turn == Player::Player2) ||
				    ((p == SpacePlayer::Player2Side1 ||
				      p == SpacePlayer::Player2Side2) &&
				     Turn == Player::Player1)) {
					r.push_back(c);
				}
			}
		}

		return r;
	};

	bool IsSpaceFlippable(Coords coords) {
		if (Phase != TurnPhase::Flip) {
			return false;
		}
		SpacePlayer p = GetSpace(coords);
		if (p == SpacePlayer::Empty) {
			return false;
		}

		if (GetEmptySides(coords).empty()) {
			return false;
		}

		return (((p == SpacePlayer::Player1Side1 ||
		          p == SpacePlayer::Player1Side2) &&
		         Turn == Player::Player2) ||
		        ((p == SpacePlayer::Player2Side1 ||
		          p == SpacePlayer::Player2Side2) &&
		         Turn == Player::Player1));
	}

	std::vector<Coords> GetEmptySpaces() {
		std::vector<Coords> r;

		for (int row = 0; row < ROW_COUNT; row++) {
			for (int col = 0; col < COL_COUNT; col++) {
				Coords c = {.row = row, .col = col};
				SpacePlayer p = GetSpace(c);
				if (p == SpacePlayer::Empty) {
					r.push_back(c);
				}
			}
		}

		return r;
	}
};
