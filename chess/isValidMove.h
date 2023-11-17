#include <vector>

bool isValidMove(const std::vector<std::vector<char>> &chessboard, int fromRow, int fromCol, int toRow, int toCol, char piece)
{
    // Проверка наличия фигуры в начальных координатах
    if (piece == '.')
    {
        return false;
    }

    char destinationPiece = chessboard[toRow][toCol];

    // Проверка, что фигура не стоит на клетке того же цвета
    if ((isupper(piece) && isupper(destinationPiece)) || (islower(piece) && islower(destinationPiece)))
    {
        return false;
    }

    // Проверка на правильность хода для данной фигуры
    bool validMove = false;

    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    switch (piece)
    {
    case 'P': // Пешка белых
        if (toCol == fromCol)
        {
            if (fromRow == 1)
            {
                if (toRow == fromRow + 1 || toRow == fromRow + 2)
                {
                    if (chessboard[toRow][toCol] == '.')
                    {
                        validMove = true;
                    }
                }
            }
            else
            {
                if (toRow == fromRow + 1)
                {
                    if (chessboard[toRow][toCol] == '.')
                    {
                        validMove = true;
                    }
                }
            }
        }
        else if (colDiff == 1 && toRow == fromRow + 1)
        {
            if (destinationPiece != '.')
            {
                validMove = true;
            }
        }
        break;
    case 'p': // Пешка черных
        if (toCol == fromCol)
        {
            if (fromRow == 6)
            {
                if (toRow == fromRow - 1 || toRow == fromRow - 2)
                {
                    if (chessboard[toRow][toCol] == '.')
                    {
                        validMove = true;
                    }
                }
            }
            else
            {
                if (toRow == fromRow - 1)
                {
                    if (chessboard[toRow][toCol] == '.')
                    {
                        validMove = true;
                    }
                }
            }
        }
        else if (colDiff == 1 && toRow == fromRow - 1)
        {
            if (destinationPiece != '.')
            {
                validMove = true;
            }
        }
        break;
    case 'R': // Ладья белых
    case 'r': // Ладья черных
        if (fromRow == toRow)
        {
            validMove = true;
            int step = (fromCol < toCol) ? 1 : -1;
            for (int col = fromCol + step; col != toCol; col += step)
            {
                if (chessboard[fromRow][col] != '.')
                {
                    validMove = false;
                    return validMove;
                    break;
                }
            }
            validMove = true;
        }
        else if (fromCol == toCol)
        {
            validMove = true;
            int step = (fromRow < toRow) ? 1 : -1;
            for (int row = fromRow + step; row != toRow; row += step)
            {
                if (chessboard[row][fromCol] != '.')
                {
                    validMove = false;
                    return validMove;
                    break;
                }
            }
        }
        break;
    case 'N': // Конь белых
    case 'n': // Конь черных
        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
        {
            validMove = true;
        }
        break;
    case 'B': // Слон белых
    case 'b': // Слон черных
        if (rowDiff == colDiff)
        {
            validMove = true;
            int rowStep = (toRow > fromRow) ? 1 : -1;
            int colStep = (toCol > fromCol) ? 1 : -1;
            int row = fromRow + rowStep;
            int col = fromCol + colStep;
            while (row != toRow)
            {
                if (chessboard[row][col] != '.')
                {
                    validMove = false;
                    return validMove;
                    break;
                }
                row += rowStep;
                col += colStep;
            }
        }
        break;
    case 'K': // Король белых
    case 'k': // Король черных
        if (rowDiff <= 1 && colDiff <= 1)
        {
            validMove = true;
        }
        break;
    }

    return validMove;
}
