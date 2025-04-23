#include <array>
#include <vector>
#include <cassert>

enum SpacePlayer {
    Empty,
    Player1Side1,
    Player1Side2,
    Player2Side1,
    Player2Side2
};

enum class Player {
    Player1,
    Player2
};

enum TurnPhase {
    Flip,
    Place
};

enum class Winner {
    None,
    Player1,
    Player2,
    Tie
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

Player Turn = Player::Player1;
TurnPhase Phase = TurnPhase::Flip;

const int ROW_COUNT = 4;
const int COL_COUNT = 4;

class Board {
private:
    void AssertRowCol(int row, int col) {
        assert(row >= 0 && row <= 3 && col >= 0 && col <= 3);
    };
public:
    using SpacesType = std::array<std::array<SpacePlayer, COL_COUNT>, ROW_COUNT>;
    SpacesType spaces;

    Board() {
        for (auto& row : spaces) {
            row.fill(Empty);
        }
    }

    std::vector<Direction> GetEmptySides(int row, int col) {
        AssertRowCol(row, col);

        std::vector<Direction> r = {};

        if (row > 0 && spaces[row-1][col] == Empty) {
            r.push_back(Up);
        }
        if (row < 3 && spaces[row+1][col] == Empty) {
            r.push_back(Down);
        }
        if (col > 0 && spaces[row][col-1] == Empty) {
            r.push_back(Left);
        }
        if (col < 3 && spaces[row][col+1] == Empty) {
            r.push_back(Right);
        }

        return r;
    };

    Winner GetWinner() {
        for (int row = 0; row < ROW_COUNT - 2; row++) {
            for (int col = 0; col < COL_COUNT - 2; col++) {
                if (spaces[row][col] == Empty) {
                    continue;
                }
                if (spaces[row][col] == spaces[row+1][col+1] && spaces[row][col] == spaces[row+2][col+2]) {
                    if (spaces[row][col] == Player1Side1 || spaces[row][col] == Player1Side2) {
                        return Winner::Player1;
                    }
                    return Winner::Player2;
                }
            }
        }

        for (int row = 2; row < ROW_COUNT; row++) {
            for (int col = 0; col < COL_COUNT - 2; col++) {
                if (spaces[row][col] == Empty) {
                    continue;
                }
                if (spaces[row][col] == spaces[row-1][col+1] && spaces[row][col] == spaces[row-2][col+2]) {
                    if (spaces[row][col] == Player1Side1 || spaces[row][col] == Player1Side2) {
                        return Winner::Player1;
                    }
                    return Winner::Player2;
                }
            }
        }

        for (int row = 0; row < ROW_COUNT; row++) {
            for (int col = 0; col < COL_COUNT - 2; col++) {
                if (spaces[row][col] == Empty) {
                    continue;
                }
                if (spaces[row][col] == spaces[row][col+1] && spaces[row][col] == spaces[row][col+2]) {
                    if (spaces[row][col] == Player1Side1 || spaces[row][col] == Player1Side2) {
                        return Winner::Player1;
                    }
                    return Winner::Player2;
                }
            }
        }

        for (int row = 0; row < ROW_COUNT - 2; row++) {
            for (int col = 0; col < COL_COUNT; col++) {
                if (spaces[row][col] == Empty) {
                    continue;
                }
                if (spaces[row][col] == spaces[row+1][col] && spaces[row][col] == spaces[row+2][col]) {
                    if (spaces[row][col] == Player1Side1 || spaces[row][col] == Player1Side2) {
                        return Winner::Player1;
                    }
                    return Winner::Player2;
                }
            }
        }

        int emptyCount = 0;
        for (int row = 0; row < ROW_COUNT; row++) {
            for (int col = 0; col < COL_COUNT; col++) {
                if (spaces[row][col] == Empty) {
                    emptyCount++;
                }
            }
        }
        if (emptyCount == 0) {
            return Winner::Tie;
        }
        return Winner::None;
    };

    bool Flip(int row, int col, Direction dir) {
        AssertRowCol(row, col);

        bool good = false;
        for(auto d : GetEmptySides(row, col)) {
            if (d == dir) {
                good = true;
                break;
            }
        }

        if (!good) {
            return false;
        }

        SpacePlayer target;

        switch (spaces[row][col])
        {
        case Empty:
            return false;
            break;
        case Player1Side1:
            target = Player1Side2;
            break;
        case Player1Side2:
            target = Player1Side1;
            break;
        case Player2Side1:
            target = Player2Side2;
            break;
        case Player2Side2:
            target = Player2Side1;
            break;
        default:
            break;
        }

        switch (dir)
        {
        case Up:
            spaces[row-1][col] = target;
            break;
        case Down:
            spaces[row+1][col] = target;
            break;
        case Left:
            spaces[row][col-1] = target;
            break;
        case Right:
            spaces[row][col+1] = target;
            break;
        
        default:
            break;
        }
        spaces[row][col] = Empty;

        return true;
    };

    bool Place(int row, int col, SpacePlayer p) {
        AssertRowCol(row, col);
        assert(p != Empty);

        if (spaces[row][col] != Empty) {
            return false;
        }

        spaces[row][col] = p;
        return true;
    };

    // TODO: GetTurnableSpaces
};
