#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <vector>
#include "Board.h"
#include "Player.h"
#include "Observer.h"
#include "Observable.h"
#include "PieceColor.h"
#include "GameResult.h"

#include <memory>

class Cell;
struct Vector2;

class ChessGame : public Observable<Player&, Player&>
{
public:
    ChessGame();
    void initializeGame(std::pair<PieceColor, PieceColor> playerPieceColors);

    Board& getBoard() noexcept;
    const Board& getBoard() const noexcept;
    Player& getCurrentPlayer() noexcept;
    const Player& getCurrentPlayer() const noexcept;
    Player& getNextPlayer() noexcept;
    const Player& getNextPlayer() const noexcept;

    std::vector<std::shared_ptr<Player>> getPlayers() const;

    void movePiece(const Vector2 pieceLocation, const Vector2 deltaLocation);
    void setToNextPlayer();

    GameResult getGameResult() const noexcept;
    void setGameResult(GameResult newResult) noexcept;

    ~ChessGame() override;
private:
    std::vector<std::shared_ptr<Player>> players;
    size_t currentTurnPlayerIndex;
    Board gameBoard;

    GameResult result;
};


#endif // CHESSGAME_H
