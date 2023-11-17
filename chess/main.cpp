
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "isValidMove.h"
#include "isValidChessboard.h"
#include "CanAttack.h"

#pragma once;

using namespace std;

// Функция для генерации случайного числа от min до max
int random(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void resetChessboard(vector<vector<char>> &chessboard)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chessboard[i][j] = '.';
        }
    }
}

// Функция для отображения шахматной доски с номерами строк и столбцов
void displayChessboard(const vector<vector<char>> &chessboard)
{
    cout << "  h g f e d c b a" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << chessboard[i][j] << " ";
        }
        cout << i + 1 << endl;
    }
    cout << "  h g f e d c b a" << endl;
}

vector<vector<char>> move(const vector<vector<char>> &chessboard, int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = chessboard[fromRow][fromCol];

    // Create a copy of the chessboard
    vector<vector<char>> newChessboard = chessboard;

    if (!isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece))
    {
        cout << "Недопустимый ход для данной фигуры." << endl;
        return newChessboard;
    }

    // Perform the move
    newChessboard[toRow][toCol] = piece;
    newChessboard[fromRow][fromCol] = '.';

    return newChessboard;
}

vector<vector<char>> generateStartingChessboard()
{
    vector<vector<char>> chessboard(8, vector<char>(8, '.'));

    // Расставляем белые фигуры
    chessboard[0] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    chessboard[1] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};

    // Расставляем черные фигуры
    chessboard[7] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    chessboard[6] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};

    return chessboard;
}

void copyChessboard(vector<vector<char>> destination, const vector<vector<char>> source)
{
    destination = source;
}

int getPieceValue(char piece)
{
    switch (piece)
    {
    case 'P': // Пешка
    case 'p':
        return 1;
    case 'N': // Конь
    case 'n':
        return 3;
    case 'B': // Слон
    case 'b':
        return 3;
    case 'R': // Ладья
    case 'r':
        return 5;
    case 'Q': // Ферзь
    case 'q':
        return 9;
    case 'K': // Король
    case 'k':
        return 0; // Мы не учитываем королей для оценки, так как их ценность фиксирована
    default:
        return 0; // Неизвестная фигура
    }
}

bool isOnBoard(int row, int col)
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool isKingInCheck(const vector<vector<char>> &chessboard, char king)
{ // Найдем позицию короля
    int kingRow = -1;
    int kingCol = -1;
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (chessboard[row][col] == king)
            {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    if (kingRow == -1 || kingCol == -1)
    {
        return false; // Король не найден (что-то не так)
    }

    // Проверка на шах по вертикали и горизонтали
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            char piece = chessboard[row][col];
            if ((isupper(piece) && piece != king && king == 'k') || ((!isupper(piece) && piece != king && king == 'K')))
            {
                if (canAttackSquare(chessboard, row, col, kingRow, kingCol))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool hasLegalMoves(const vector<vector<char>> &chessboard, char piece)
{
    for (int fromRow = 0; fromRow < 8; fromRow++)
    {
        for (int fromCol = 0; fromCol < 8; fromCol++)
        {
            if (chessboard[fromRow][fromCol] == piece)
            {
                for (int toRow = 0; toRow < 8; toRow++)
                {
                    for (int toCol = 0; toCol < 8; toCol++)
                    {
                        char piece = chessboard[fromRow][fromCol];
                        if (isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int evaluatePosition(const vector<vector<char>> &chessboard)
{
    int whiteScore = 0;
    int blackScore = 0;

    bool whiteInCheck = isKingInCheck(chessboard, 'K');
    bool blackInCheck = isKingInCheck(chessboard, 'k');

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            char piece = chessboard[row][col];
            if (isupper(piece))
            {
                // Фигура принадлежит белым
                whiteScore += getPieceValue(piece);
            }
            else if (islower(piece))
            {
                // Фигура принадлежит черным
                blackScore += getPieceValue(piece);
            }
        }
    }

    // Бонус за шах
    if (whiteInCheck)
    {
        blackScore += 15; // Шах белому королю
    }
    if (blackInCheck)
    {
        whiteScore += 15; // Шах черному королю
    }

    // Проверка на мат черного короля
    if (blackInCheck && !hasLegalMoves(chessboard, 'k'))
    {
        whiteScore += 1000; // Мат черному королю
    }

    // Возвращаем разницу в оценке между белыми и черными
    return whiteScore - blackScore;
}

vector<vector<char>> findBestMove(const vector<vector<char>> &chessboard)
{
    vector<vector<char>> bestMoveChessboard;
    int bestEvaluation = -10000; // Начальное значение для лучшей оценки

    // Создайте временную доску и инициализируйте её
    vector<vector<char>> newChessboard;

    for (int fromRow = 0; fromRow < 8; fromRow++)
    {
        for (int fromCol = 0; fromCol < 8; fromCol++)
        {
            char piece = chessboard[fromRow][fromCol];
            if (isupper(piece))
            { // Проверяем, что это белая фигура
                for (int toRow = 0; toRow < 8; toRow++)
                {
                    for (int toCol = 0; toCol < 8; toCol++)
                    {
                        if (isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece))
                        {
                            newChessboard = chessboard;

                            // Делаем ход на копии доски
                            newChessboard = move(newChessboard, fromRow, fromCol, toRow, toCol);
                            int evaluation = evaluatePosition(newChessboard);

                            // Если оценка лучше предыдущей, обновляем лучший ход
                            if (evaluation > bestEvaluation)
                            {
                                bestEvaluation = evaluation;
                                bestMoveChessboard = newChessboard;
                            }
                        }
                    }
                }
            }
        }
    }

    return bestMoveChessboard;
}

std::vector<std::vector<vector<char>>> findBestMoves(const std::vector<std::vector<char>> &chessboard, int n)
{
    std::vector<std::vector<vector<char>>> bestMoves;
    std::vector<std::vector<char>> newChessboard;

    for (int fromRow = 0; fromRow < 8; fromRow++)
    {
        for (int fromCol = 0; fromCol < 8; fromCol++)
        {
            char piece = chessboard[fromRow][fromCol];
            if (std::isupper(piece))
            { // Check if it's a white piece
                for (int toRow = 0; toRow < 8; toRow++)
                {
                    for (int toCol = 0; toCol < 8; toCol++)
                    {
                        if (isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece))
                        {
                            newChessboard = chessboard;
                            newChessboard = move(newChessboard, fromRow, fromCol, toRow, toCol);
                            int evaluation = evaluatePosition(newChessboard);

                            if (bestMoves.size() < n)
                            {
                                bestMoves.push_back(newChessboard);
                            }
                            else
                            {
                                // Find the minimum evaluation among the best moves
                                int minEvalIndex = 0;
                                int minEval = evaluatePosition(bestMoves[0]);
                                for (int i = 1; i < n; i++)
                                {
                                    int currentEval = evaluatePosition(bestMoves[i]);
                                    if (currentEval < minEval)
                                    {
                                        minEval = currentEval;
                                        minEvalIndex = i;
                                    }
                                }

                                // Replace the move with the minimum evaluation if the current move has a higher evaluation
                                if (evaluation > minEval)
                                {
                                    bestMoves[minEvalIndex] = newChessboard;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return bestMoves;
}

string getMove(const vector<vector<char>> &chessboard_0, const vector<vector<char>> &chessboard_1)
{
    string move = "";
    string thisMove = "";
    // Поиск разницы между досками

    char startCol;
    char startRow;
    char piece;
    char endCol;
    char endRow;
    string moveType;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (chessboard_0[row][col] != chessboard_1[row][col])
            {
                char tmp = chessboard_1[row][col];
                if (tmp == '.')
                {
                    startCol = -col + 'h'; // Преобразование колонки в букву (a-h)
                    startRow = row + '1';  // Преобразование строки в цифру (1-8)
                }
                else
                {
                    piece = chessboard_1[row][col];
                    endCol = -col + 'h'; // Преобразование колонки в букву (a-h)
                    endRow = row + '1';  // Преобразование строки в цифру (1-8)

                    // Определение типа хода (тихий ход или взятие)
                    moveType = (chessboard_0[row][col] == '.') ? "-" : "x";
                }
            }
        }
    }

    thisMove += piece;
    thisMove += " ";
    thisMove += startCol;
    thisMove += startRow;
    thisMove += moveType;
    thisMove += endCol;
    thisMove += endRow;

    move += thisMove;

    return move;
}

int main()
{
    srand(time(0)); // Инициализация генератора случайных чисел текущим временем
    int x = 0;

    // cin >> x;
    cout << "Введите количество фигур" << endl;

    switch (x)
    {
    case 0:
    {

        vector<vector<char>> chessboard(8, vector<char>(8, '.')); // Шахматная доска 8x8

        int numWhitePawns, numWhiteRooks, numWhiteBishops, numWhiteKnights, numWhiteKings = 1;
        int numBlackPawns, numBlackRooks, numBlackBishops, numBlackKnights, numBlackKings = 1;

        // Ввод количества белых фигур
        do
        {
            cout << "numWhitePawns: ";
            cin >> numWhitePawns;
        } while (numWhitePawns > 8); // Максимальное количество пешек - 8

        do
        {
            cout << "numWhiteRooks: ";
            cin >> numWhiteRooks;
        } while (numWhiteRooks > 2); // Максимальное количество ладей - 2

        do
        {
            cout << "numWhiteBishops: ";
            cin >> numWhiteBishops;
        } while (numWhiteBishops > 2); // Максимальное количество слонов - 2

        do
        {
            cout << "numWhiteKnights: ";
            cin >> numWhiteKnights;
        } while (numWhiteKnights > 2); // Максимальное количество коней - 2

        // Ввод количества черных фигур
        do
        {
            cout << "numBlackPawns: ";
            cin >> numBlackPawns;
        } while (numBlackPawns > 8); // Максимальное количество пешек - 8

        do
        {
            cout << "numBlackRooks: ";
            cin >> numBlackRooks;
        } while (numBlackRooks > 2); // Максимальное количество ладей - 2

        do
        {
            cout << "numBlackBishops: ";
            cin >> numBlackBishops;
        } while (numBlackBishops > 2); // Максимальное количество слонов - 2

        do
        {
            cout << "numBlackKnights: ";
            cin >> numBlackKnights;
        } while (numBlackKnights > 2); // Максимальное количество коней - 2

        do
        {
            resetChessboard(chessboard);
            // Расставляем белые фигуры случайным образом

            for (int i = 0; i < numWhiteKings; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'K';
            }

            // Пешки
            for (int i = 0; i < numWhitePawns; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'P';
            }

            // Ладьи
            for (int i = 0; i < numWhiteRooks; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'R';
            }

            // Слоны
            for (int i = 0; i < numWhiteBishops; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'B';
            }

            // Кони (любой порядок)
            for (int i = 0; i < numWhiteKnights; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'N';
            }

            // Расставляем черные фигуры случайным образом

            for (int i = 0; i < numBlackKings; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'k';
            }
            // Пешки
            for (int i = 0; i < numBlackPawns; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'p';
            }

            // Ладьи
            for (int i = 0; i < numBlackRooks; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'r';
            }

            // Слоны
            for (int i = 0; i < numBlackBishops; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'b';
            }

            // Кони (любой порядок)
            for (int i = 0; i < numBlackKnights; i++)
            {
                int row, col;
                do
                {
                    row = random(0, 7);
                    col = random(0, 7);
                } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
                chessboard[row][col] = 'n';
            }
            // cout << isValidChessboard(chessboard);
        } while (!isValidChessboard(chessboard) || isKingInCheck(chessboard, 'k') || isKingInCheck(chessboard, 'K')); // Проверка валидности и перегенерация при необходимости
        // Отображаем шахматную доску

        //cout << "Test" << endl;

        cout << endl;
        displayChessboard(chessboard);
        cout << evaluatePosition(chessboard) << endl
             << endl;

        vector<vector<char>> baseChessboard = chessboard;
        vector<vector<vector<char>>> sourceChessboard1 = findBestMoves(chessboard, 3);
        
        for (int i = 0; i < 3; i++){
            cout << i << "-й вариант >>>" << endl;
            cout << "1й ход" << endl;
            vector<vector<char>> sourceChessboard = sourceChessboard1[i];
            chessboard = baseChessboard;

            displayChessboard(sourceChessboard);
            cout << getMove(chessboard, sourceChessboard) << endl;
            cout << evaluatePosition(sourceChessboard) << endl
                << endl;
            chessboard = sourceChessboard;
            if (isKingInCheck(chessboard, 'k')){
                cout << "King in Check" << endl;
                cout << endl;
                continue;
            }

            cout << "2й ход" << endl;
            sourceChessboard = findBestMove(chessboard);
            displayChessboard(sourceChessboard);
            cout << getMove(chessboard, sourceChessboard) << endl;
            cout << evaluatePosition(sourceChessboard) << endl
                << endl;
            chessboard = sourceChessboard;
            if (isKingInCheck(chessboard, 'k')){
                cout << "King in Check" << endl;
                cout << endl;
                continue;
            }

            cout << "3й ход" << endl;
            sourceChessboard = findBestMove(chessboard);
            displayChessboard(sourceChessboard);
            cout << getMove(chessboard, sourceChessboard) << endl;
            cout << evaluatePosition(sourceChessboard) << endl
                << endl;
            chessboard = sourceChessboard;
            if (isKingInCheck(chessboard, 'k')){
                cout << "King in Check" << endl;
                cout << endl;
                continue;
            }
            cout << endl;
        }
        
        break;
    }
    case 1:
        vector<vector<char>> chessboard = generateStartingChessboard();

        displayChessboard(chessboard);

        int FromRow, FromCol, ToRow, ToCol;

        cout << "Координаты фигуры:" << endl;
        cin >> FromRow >> FromCol;
        cout << endl
             << chessboard[FromRow][FromCol] << endl;
        cout << "Координаты места:" << endl;
        cin >> ToRow >> ToCol;
        cout << endl
             << chessboard[ToRow][ToCol] << endl;

        chessboard = move(chessboard, FromRow, FromCol, ToRow, ToCol);

        displayChessboard(chessboard);
        break;
    }

    return 0;
}
