#include <vector>

bool isValidChessboard(const std::vector<std::vector<char>> &chessboard)
{
    bool hasWhiteKing = false;
    bool hasBlackKing = false;
    short whiteBishopOnWhiteSquare = 0;
    short whiteBishopOnBlackSquare = 0;
    short blackBishopOnWhiteSquare = 0;
    short blackBishopOnBlackSquare = 0;

    // Проверка наличия королей и другие условия
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = chessboard[i][j];

            // Проверка наличия королей
            if (piece == 'K')
            {
                if (hasWhiteKing)
                {
                    return false; // У белых не может быть больше одного короля
                }
                hasWhiteKing = true;

                if ((i > 0 && j > 0 && chessboard[i - 1][j - 1] == 'k') ||
                    (i > 0 && chessboard[i - 1][j] == 'k') ||
                    (i > 0 && j < 7 && chessboard[i - 1][j + 1] == 'k') ||
                    (j > 0 && chessboard[i][j - 1] == 'k') ||
                    (j < 7 && chessboard[i][j + 1] == 'k') ||
                    (i < 7 && j > 0 && chessboard[i + 1][j - 1] == 'k') ||
                    (i < 7 && chessboard[i + 1][j] == 'k') ||
                    (i < 7 && j < 7 && chessboard[i + 1][j + 1] == 'k'))
                {
                    return false; // Белый король стоит вплотную к другому королю
                }
            }
            else if (piece == 'k')
            {
                if (hasBlackKing)
                {
                    return false; // У черных не может быть больше одного короля
                }
                hasBlackKing = true;
            }

            // Проверка что два слона одного цвета не стоят на клетках одинаковых цветов
            if (piece == 'B')
            {
                if ((i + j) % 2 == 0)
                {
                    whiteBishopOnWhiteSquare += 1;
                }
                else
                {
                    whiteBishopOnBlackSquare += 1;
                }
            }
            else if (piece == 'b')
            {
                if ((i + j) % 2 == 0)
                {
                    blackBishopOnWhiteSquare += 1;
                }
                else
                {
                    blackBishopOnBlackSquare += 1;
                }
            }
        }
    }

    if (!hasWhiteKing || !hasBlackKing)
    {
        return false;
    }

    // Проверка отсутствия пешек на первом и восьмом горизонталях
    for (int j = 0; j < 8; j++)
    {
        if ((chessboard[0][j] == 'P' || chessboard[0][j] == 'p') || (chessboard[7][j] == 'P' || chessboard[7][j] == 'p'))
        {
            return false;
        }
    }

    // Проверка что два слона одного цвета не стоят на клетках одинаковых цветов
    if (whiteBishopOnWhiteSquare > 1 || whiteBishopOnBlackSquare > 1)
    {
        return false; // У белых два слона на клетках разных цветов
    }
    if (blackBishopOnWhiteSquare > 1 || blackBishopOnBlackSquare > 1)
    {
        return false; // У черных два слона на клетках разных цветов
    }

    return true;
}