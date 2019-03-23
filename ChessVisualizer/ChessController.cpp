#include "ChessWindow.h"
#include "ChessController.h"
#include "Board.h"
#include "Vector2.h"
#include "PlayerType.h"
#include <QPixmap>
#include <exception>
#include <memory>

#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"

QPixmap convertPieceToPixmap(const Piece* piecePtr)
{
    std::string pixmapName;
    pixmapName.assign(piecePtr->getColor() == PieceColor::White ? "_white.svg" : "_black.svg");

    if (dynamic_cast<const King*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/king");
        return QPixmap{ pixmapName.c_str() };
    }
    else if (dynamic_cast<const Queen*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/queen");
        return QPixmap{ pixmapName.c_str() };
    }
    else if (dynamic_cast<const Bishop*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/bishop");
        return QPixmap{ pixmapName.c_str() };
    }
    else if (dynamic_cast<const Rook*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/rook");
        return QPixmap{ pixmapName.c_str() };
    }
    else if (dynamic_cast<const Knight*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/knight");
        return QPixmap{ pixmapName.c_str() };
    }
    else if (dynamic_cast<const Pawn*>(piecePtr) != nullptr)
    {
        pixmapName.insert(0, ":resource/pawn");
        return QPixmap{ pixmapName.c_str() };
    }
    else
    {
        return QPixmap();
    }
}

ChessController::ChessController()
{
    // register turn changed event
    game.registerObserver(this);

    // register cell changed event
    auto& board = game.getBoard();
    board.registerObserver(this);

    for (size_t i = 0; i < boardSize; ++i)
    {
        for (size_t j = 0; j < boardSize; ++j)
        {
            auto piecePtr = board.getCell(i, j).getPiece();
            window.getLabel(i, j).setPixmap(convertPieceToPixmap(piecePtr.get()));
        }
    }
}

#include <iostream>

void ChessController::startChess()
{
    window.show();

    makeMovingFromPlayer(game.getCurrentPlayer());
}

void ChessController::makeMovingFromPlayer(Player& player)
{
    if (player.getType() == PlayerType::Human)
    {
        std::cout << "Select!" << std::endl;
        while (true)
        {
            double x = 0;
            double y = 0;
            double deltaX = 0;
            double deltaY = 0;

            std::cin >> x >> y >> deltaX >> deltaY;

            try
            {
                game.getBoard().movePiece({ x, y }, { deltaX, deltaY });
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                continue;
            }

            break;
        }
    }
}

void ChessController::notify(Player& changedPlayer)
{
    std::cout << "Changed" << std::endl;

    //makeMovingFromPlayer(changedPlayer);

    std::cout << "Out" << std::endl;
}

void ChessController::notify(const Cell& changedCell, Vector2&& location)
{
    auto pixmap = convertPieceToPixmap(changedCell.getPiece().get());
    auto normalized = normalizeToIntegerVector(location);

    window.getLabel(normalized.second, normalized.first).setPixmap(std::move(pixmap));
}

ChessController::~ChessController()
{
    game.unregisterObserver(this);
}
