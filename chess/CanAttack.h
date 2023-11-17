#include <vector>

bool canAttackSquare(const std::vector<std::vector<char>> &chessboard, int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = chessboard[fromRow][fromCol];
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    switch (piece)
    {
    case 'P': // Пешка белых
        if (toRow - fromRow == 1 && colDiff == 1)
        {
            // Пешка атакует по диагонали
            return true;
        }
        break;
    case 'N': // Конь белых
        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
        {
            // Конь атакует "буквой L"
            return true;
        }
        break;
    case 'B': // Слон белых
        if (rowDiff == colDiff)
        {
            // Слон атакует по диагонали
            return true;
        }
        break;
    case 'R': // Ладья белых
        if (fromRow == toRow || fromCol == toCol)
        {
            // Ладья атакует по вертикали или горизонтали
            return true;
        }
        break;
    case 'Q': // Ферзь белых
        if (fromRow == toRow || fromCol == toCol || rowDiff == colDiff)
        {
            // Ферзь атакует по вертикали, горизонтали или диагонали
            return true;
        }
        break;
    case 'K': // Король белых
        if (rowDiff <= 1 && colDiff <= 1)
        {
            // Король атакует ближние клетки
            return true;
        }
        break;
    // Добавьте аналогичные проверки для фигур черных
    case 'p': // Пешка черных
        if (toRow - fromRow == -1 && colDiff == 1)
        {
            // Пешка атакует по диагонали
            return true;
        }
        break;
    case 'n': // Конь черных
        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
        {
            // Конь атакует "буквой L"
            return true;
        }
        break;
    case 'b': // Слон черных
        if (rowDiff == colDiff)
        {
            // Слон атакует по диагонали
            return true;
        }
        break;
    case 'r': // Ладья черных
        if (fromRow == toRow || fromCol == toCol)
        {
            // Ладья атакует по вертикали или горизонтали
            return true;
        }
        break;
    case 'q': // Ферзь черных
        if (fromRow == toRow || fromCol == toCol || rowDiff == colDiff)
        {
            // Ферзь атакует по вертикали, горизонтали или диагонали
            return true;
        }
        break;
    case 'k': // Король черных
        if (rowDiff <= 1 && colDiff <= 1)
        {
            // Король атакует ближние клетки
            return true;
        }
        break;
    }
    return false;
}