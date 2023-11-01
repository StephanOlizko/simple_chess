
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


// Функция для генерации случайного числа от min до max
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

void resetChessboard(char chessboard[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = '.';
        }
    }
}


// Функция для отображения шахматной доски с номерами строк и столбцов
void displayChessboard(char chessboard[8][8]) {
    cout << "  0 1 2 3 4 5 6 7" << endl; // Вывод буквенных обозначений столбцов
    for (int i = 0; i < 8; i++) {
        cout << i << " "; // Вывод номера строки
        for (int j = 0; j < 8; j++) {
            cout << chessboard[i][j] << " ";
        }
        cout << i << endl; // Вывод номера строки снова
    }
    cout << "  0 1 2 3 4 5 6 7" << endl; // Вывод буквенных обозначений столбцов
}

bool isValidMove(char chessboard[8][8], int fromRow, int fromCol, int toRow, int toCol, char piece)
{
    // Проверка наличия фигуры в начальных координатах
    if (piece == '.')
    {
        //cout << "В начальных координатах нет фигуры." << endl;
        return false;
    }

    char destinationPiece = chessboard[toRow][toCol];

    // Проверка, что фигура не стоит на клетке того же цвета
    if ((isupper(piece) && isupper(destinationPiece)) || (islower(piece) && islower(destinationPiece)))
    {
        //cout << "Фигура не может занимать клетку своего цвета." << endl;
        return false;
    }

    // Проверка на правильность хода для данной фигуры
    bool validMove = false;


    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    switch (piece)
    {
    case 'P': // Пешка белых
            if (toCol == fromCol) {
                if (fromRow == 1) {
                    // Начальное положение, может двигаться на 2 клетки
                    if (toRow == fromRow + 1 || toRow == fromRow + 2) {
                        // Проверка на наличие фигуры на пути
                        if (chessboard[toRow][toCol] == '.') {
                            validMove = true;
                        }
                    }
                } else {
                    // Пешка может двигаться на 1 клетку вперед
                    if (toRow == fromRow + 1) {
                        // Проверка на наличие фигуры на целевой клетке
                        if (chessboard[toRow][toCol] == '.') {
                            validMove = true;
                        }
                    }
                }
            } else if (colDiff == 1 && toRow == fromRow + 1) {
                // Диагональное взятие фигуры
                // Проверка на наличие фигуры на целевой клетке
                if (destinationPiece != '.') {
                    validMove = true;
                }
            }
            break;
        case 'p': // Пешка черных
            if (toCol == fromCol) {
                if (fromRow == 6) {
                    // Начальное положение, может двигаться на 2 клетки
                    if (toRow == fromRow - 1 || toRow == fromRow - 2) {
                        // Проверка на наличие фигуры на пути
                        if (chessboard[toRow][toCol] == '.') {
                            validMove = true;
                        }
                    }
                } else {
                    // Пешка может двигаться на 1 клетку вперед
                    if (toRow == fromRow - 1) {
                        // Проверка на наличие фигуры на целевой клетке
                        if (chessboard[toRow][toCol] == '.') {
                            validMove = true;
                        }
                    }
                }
            } else if (colDiff == 1 && toRow == fromRow - 1) {
                // Диагональное взятие фигуры
                // Проверка на наличие фигуры на целевой клетке
                if (destinationPiece != '.') {
                    validMove = true;
                }
            }
            break;
    case 'R': // Ладья белых
    case 'r': // Ладья черных
         if (fromRow == toRow) {
                validMove = true;
                // Движение по горизонтали
                int step = (fromCol < toCol) ? 1 : -1;
                for (int col = fromCol + step; col != toCol; col += step) {
                    if (chessboard[fromRow][col] != '.') {
                        // Проверка на наличие фигур на промежуточных клетках
                        validMove = false;
                        break;
                    }
                }
                validMove = true;
            } else if (fromCol == toCol) {
                validMove = true;
                // Движение по вертикали
                int step = (fromRow < toRow) ? 1 : -1;
                for (int row = fromRow + step; row != toRow; row += step) {
                    if (chessboard[row][fromCol] != '.') {
                        // Проверка на наличие фигур на промежуточных клетках
                        validMove = false;
                        break;
                    }
                }
            }
            break;
    case 'N': // Конь белых
    case 'n': // Конь черных
        if ((abs(toRow - fromRow) == 2 && abs(toCol - fromCol) == 1) ||
            (abs(toRow - fromRow) == 1 && abs(toCol - fromCol) == 2))
        {
            validMove = true;
        }
        break;
    case 'B': // Слон белых
    case 'b': // Слон черных
        if (rowDiff == colDiff) {
                validMove = true;
                int rowStep = (toRow > fromRow) ? 1 : -1;
                int colStep = (toCol > fromCol) ? 1 : -1;
                int row = fromRow + rowStep;
                int col = fromCol + colStep;
                while (row != toRow) {
                    if (chessboard[row][col] != '.') {
                        validMove = false;
                        break;
                    }
                    row += rowStep;
                    col += colStep;
                }
            }
            break;
    case 'K': // Король белых
    case 'k': // Король черных
        if (rowDiff <= 1 && colDiff <= 1) {
            validMove = true;
        }
        break;
    }

    return validMove;
}

char **move(char chessboard[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = chessboard[fromRow][fromCol];

    // Создаем копию доски, чтобы избежать изменений в оригинальной доске
    char **newChessboard = new char *[8];
    for (int i = 0; i < 8; i++)
    {
        newChessboard[i] = new char[8];
        for (int j = 0; j < 8; j++)
        {
            newChessboard[i][j] = chessboard[i][j];
        }
    }

    if (!isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece))
    {
        cout << "Недопустимый ход для данной фигуры." << endl;
        return newChessboard;
    }

    // Если все проверки пройдены, перемещаем фигуру
    newChessboard[toRow][toCol] = piece;
    newChessboard[fromRow][fromCol] = '.';

    return newChessboard;
}



bool isValidChessboard(char chessboard[8][8]) {
    bool hasWhiteKing = false;
    bool hasBlackKing = false;
    short whiteBishopOnWhiteSquare = 0;
    short whiteBishopOnBlackSquare = 0;
    short blackBishopOnWhiteSquare = 0;
    short blackBishopOnBlackSquare = 0;

    // Проверка наличия королей и другие условия
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char piece = chessboard[i][j];

            // Проверка наличия королей
            if (piece == 'K') {
                if (hasWhiteKing) {
                   // cout << "1";
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
                    (i < 7 && j < 7 && chessboard[i + 1][j + 1] == 'k')) {
                    //cout << "2";
                    return false; // Белый король стоит вплотную к другому1 королю
                }

            } else if (piece == 'k') {
                if (hasBlackKing) {
                    //cout << "3";
                    return false; // У черных не может быть больше одного короля
                }
                hasBlackKing = true;
            }

            // Проверка что два слона одного цвета не стоят на клетках одинаковых цветов
            if (piece == 'B') {
                if ((i + j) % 2 == 0) {
                    whiteBishopOnWhiteSquare += 1;
                } else {
                    whiteBishopOnBlackSquare += 1;
                }
            } else if (piece == 'b') {
                if ((i + j) % 2 == 0) {
                    blackBishopOnWhiteSquare += 1;
                } else {
                    blackBishopOnBlackSquare += 1;
                }
            }
        }
    }
    //cout << hasBlackKing << hasWhiteKing << endl;
    if (!hasWhiteKing || !hasBlackKing) {
        //cout << "4";
        return false;
    }

    // Проверка отсутствия пешек на первом и восьмом горизонталях
    for (int j = 0; j < 8; j++) {
        if ((chessboard[0][j] == 'P' || chessboard[0][j] == 'p') || (chessboard[7][j] == 'P' || chessboard[7][j] == 'p')){
            //cout << "5";
            return false;
        }
    }

    // Проверка что два слона одного цвета не стоят на клетках одинаковых цветов
    if (whiteBishopOnWhiteSquare > 1 || whiteBishopOnBlackSquare > 1) {
        //cout << "6";
        return false; // У белых два слона на клетках разных цветов
    }
    if (blackBishopOnWhiteSquare > 1 || blackBishopOnBlackSquare > 1) {
        //cout << "7";
        return false; // У черных два слона на клетках разных цветов
    }


    //cout << "*";
    return true;
}

char** generateStartingChessboard() {
    char** chessboard = new char*[8];
    for (int i = 0; i < 8; i++) {
        chessboard[i] = new char[8];
    }

    // Расставляем белые фигуры
    chessboard[0][0] = 'R';
    chessboard[0][1] = 'N';
    chessboard[0][2] = 'B';
    chessboard[0][3] = 'Q';
    chessboard[0][4] = 'K';
    chessboard[0][5] = 'B';
    chessboard[0][6] = 'N';
    chessboard[0][7] = 'R';

    for (int i = 0; i < 8; i++) {
        chessboard[1][i] = 'P';
    }

    // Остальные клетки - пустые
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = '.';
        }
    }

    // Расставляем черные фигуры
    chessboard[7][0] = 'r';
    chessboard[7][1] = 'n';
    chessboard[7][2] = 'b';
    chessboard[7][3] = 'q';
    chessboard[7][4] = 'k';
    chessboard[7][5] = 'b';
    chessboard[7][6] = 'n';
    chessboard[7][7] = 'r';

    for (int i = 0; i < 8; i++) {
        chessboard[6][i] = 'p';
    }

    return chessboard;
}

void copyChessboard(char chessboard[8][8], char** sourceChessboard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = sourceChessboard[i][j];
        }
    }
}

void copyChessboard(char** chessboard, char sourceChessboard[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = sourceChessboard[i][j];
        }
    }
}

void copyChessboard(char chessboard[8][8], char sourceChessboard[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = sourceChessboard[i][j];
        }
    }
}


int getPieceValue(char piece) {
    switch (piece) {
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


bool isOnBoard(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}


bool canAttackSquare(char chessboard[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    char piece = chessboard[fromRow][fromCol];
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    switch (piece) {
        case 'P': // Пешка белых
            if (toRow-fromRow == 1 && colDiff == 1) {
                // Пешка атакует по диагонали
                return true;
            }
            break;
        case 'N': // Конь белых
            if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
                // Конь атакует "буквой L"
                return true;
            }
            break;
        case 'B': // Слон белых
            if (rowDiff == colDiff) {
                // Слон атакует по диагонали
                return true;
            }
            break;
        case 'R': // Ладья белых
            if (fromRow == toRow || fromCol == toCol) {
                // Ладья атакует по вертикали или горизонтали
                return true;
            }
            break;
        case 'Q': // Ферзь белых
            if (fromRow == toRow || fromCol == toCol || rowDiff == colDiff) {
                // Ферзь атакует по вертикали, горизонтали или диагонали
                return true;
            }
            break;
        case 'K': // Король белых
            if (rowDiff <= 1 && colDiff <= 1) {
                // Король атакует ближние клетки
                return true;
            }
            break;
        // Добавьте аналогичные проверки для фигур черных
        case 'p': // Пешка черных
            if (toRow-fromRow == -1 && colDiff == 1) {
                // Пешка атакует по диагонали
                return true;
            }
            break;
        case 'n': // Конь черных
            if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
                // Конь атакует "буквой L"
                return true;
            }
            break;
        case 'b': // Слон черных
            if (rowDiff == colDiff) {
                // Слон атакует по диагонали
                return true;
            }
            break;
        case 'r': // Ладья черных
            if (fromRow == toRow || fromCol == toCol) {
                // Ладья атакует по вертикали или горизонтали
                return true;
            }
            break;
        case 'q': // Ферзь черных
            if (fromRow == toRow || fromCol == toCol || rowDiff == colDiff) {
                // Ферзь атакует по вертикали, горизонтали или диагонали
                return true;
            }
            break;
        case 'k': // Король черных
            if (rowDiff <= 1 && colDiff <= 1) {
                // Король атакует ближние клетки
                return true;
            }
            break;
    }
    return false;
}


bool isKingInCheck(char chessboard[8][8], char king) {
    // Найдем позицию короля
    int kingRow = -1;
    int kingCol = -1;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (chessboard[row][col] == king) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }

    if (kingRow == -1 || kingCol == -1) {
        return false; // Король не найден (что-то не так)
    }

    // Проверка на шах по вертикали и горизонтали
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char piece = chessboard[row][col];
            if ((isupper(piece) && piece != king && king == 'k') || ((!isupper(piece) && piece != king && king == 'K'))) {
                if (canAttackSquare(chessboard, row, col, kingRow, kingCol)) {
                    return true;
                }
            }
        }
    }

    return false;
}


bool hasLegalMoves(char chessboard[8][8], char piece) {
    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            if (chessboard[fromRow][fromCol] == piece) {
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        char piece = chessboard[fromRow][fromCol];
                        if (isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}




int evaluatePosition(char chessboard[8][8]) {
    int whiteScore = 0;
    int blackScore = 0;

    bool whiteInCheck = isKingInCheck(chessboard, 'K');
    bool blackInCheck = isKingInCheck(chessboard, 'k');

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char piece = chessboard[row][col];
            if (isupper(piece)) {
                // Фигура принадлежит белым
                whiteScore += getPieceValue(piece);
            } else if (islower(piece)) {
                // Фигура принадлежит черным
                blackScore += getPieceValue(piece);
            }
        }
    }

    // Бонус за шах
    if (whiteInCheck) {
        blackScore += 15; // Шах белому королю
    }
    if (blackInCheck) {
        whiteScore += 15; // Шах черному королю
    }

    // Проверка на мат черного короля
    if (blackInCheck && !hasLegalMoves(chessboard, 'k')) {
        whiteScore += 1000; // Мат черному королю
    }

    // Возвращаем разницу в оценке между белыми и черными
    return whiteScore - blackScore;
}

char** findBestMove(char chessboard[8][8]) {
    char** bestMoveChessboard = nullptr;
    int bestEvaluation = -10000; // Начальное значение для лучшей оценки

    // Создайте временную доску и инициализируйте её
    char newChessboard[8][8];
    copyChessboard(newChessboard, chessboard);

    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            char piece = chessboard[fromRow][fromCol];
            if (isupper(piece)) { // Проверяем, что это белая фигура
                for (int toRow = 0; toRow < 8; toRow++) {
                    for (int toCol = 0; toCol < 8; toCol++) {
                        if (isValidMove(chessboard, fromRow, fromCol, toRow, toCol, piece)) {
                            copyChessboard(newChessboard, chessboard);

                            // Создаем копию текущей доски
                            char** newChessboardCopy = new char*[8];
                                for (int i = 0; i < 8; i++) {
                                    newChessboardCopy[i] = new char[8];
                                }


                            copyChessboard(newChessboardCopy, newChessboard);

                            // Делаем ход на копии доски
                            newChessboardCopy = move(newChessboard, fromRow, fromCol, toRow, toCol);
                            copyChessboard(newChessboard, newChessboardCopy);


                            //displayChessboard(newChessboard);
                            //cout << evaluatePosition(newChessboard) << endl;                                


                            // Оцениваем позицию после хода
                            int evaluation = evaluatePosition(newChessboard);

                            // Если оценка лучше предыдущей, обновляем лучший ход
                            if (evaluation > bestEvaluation) {
                                bestEvaluation = evaluation;
                                if (bestMoveChessboard) {
                                    bestMoveChessboard = nullptr;
                                }
                                bestMoveChessboard = new char*[8];
                                for (int i = 0; i < 8; i++) {
                                    bestMoveChessboard[i] = new char[8];
                                    for (int j = 0; j < 8; j++) {
                                        bestMoveChessboard[i][j] = newChessboardCopy[i][j];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    

    // Освобождаем память для временной доски
    resetChessboard(newChessboard);

    return bestMoveChessboard;
}




int main() {
    srand(time(0)); // Инициализация генератора случайных чисел текущим временем
    int x = 0;
    cin >> x; 
    switch (x)
    {
    case 0:
    {
    char chessboard[8][8]; // Шахматная доска 8x8

    // Инициализация шахматной доски с пустыми клетками
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = '.';
        }
    }

    int numWhitePawns, numWhiteRooks, numWhiteBishops, numWhiteKnights, numWhiteKings = 1;
    int numBlackPawns, numBlackRooks, numBlackBishops, numBlackKnights, numBlackKings = 1;

        // Ввод количества белых фигур
    do {
        cout << "numWhitePawns: ";
        cin >> numWhitePawns;
    } while (numWhitePawns > 8); // Максимальное количество пешек - 8

    do {
        cout << "numWhiteRooks: ";
        cin >> numWhiteRooks;
    } while (numWhiteRooks > 2); // Максимальное количество ладей - 2

    do {
        cout << "numWhiteBishops: ";
        cin >> numWhiteBishops;
    } while (numWhiteBishops > 2); // Максимальное количество слонов - 2

    do {
        cout << "numWhiteKnights: ";
        cin >> numWhiteKnights;
    } while (numWhiteKnights > 2); // Максимальное количество коней - 2



    // Ввод количества черных фигур
    do {
        cout << "numBlackPawns: ";
        cin >> numBlackPawns;
    } while (numBlackPawns > 8); // Максимальное количество пешек - 8

    do {
        cout << "numBlackRooks: ";
        cin >> numBlackRooks;
    } while (numBlackRooks > 2); // Максимальное количество ладей - 2

    do {
        cout << "numBlackBishops: ";
        cin >> numBlackBishops;
    } while (numBlackBishops > 2); // Максимальное количество слонов - 2

    do {
        cout << "numBlackKnights: ";
        cin >> numBlackKnights;
    } while (numBlackKnights > 2); // Максимальное количество коней - 2


    do {
        resetChessboard(chessboard);
        // Расставляем белые фигуры случайным образом

        for (int i = 0; i < numWhiteKings; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'K';
        }

        // Пешки
        for (int i = 0; i < numWhitePawns; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'P';
        }

        // Ладьи
        for (int i = 0; i < numWhiteRooks; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'R';
        }

        // Слоны
        for (int i = 0; i < numWhiteBishops; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'B';
        }

        // Кони (любой порядок)
        for (int i = 0; i < numWhiteKnights; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'N';
        }

        // Расставляем черные фигуры случайным образом


        for (int i = 0; i < numBlackKings; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'k';
        }
        // Пешки
        for (int i = 0; i < numBlackPawns; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'p';
        }

        // Ладьи
        for (int i = 0; i < numBlackRooks; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'r';
        }

        // Слоны
        for (int i = 0; i < numBlackBishops; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'b';
        }

        // Кони (любой порядок)
        for (int i = 0; i < numBlackKnights; i++) {
            int row, col;
            do {
                row = random(0, 7);
                col = random(0, 7);
            } while (chessboard[row][col] != '.'); // Продолжаем генерацию, пока не найдем свободную клетку
            chessboard[row][col] = 'n';
        }
        //cout << isValidChessboard(chessboard);
    } while (!isValidChessboard(chessboard)); // Проверка валидности и перегенерация при необходимости
    // Отображаем шахматную доску



    cout << endl;
    displayChessboard(chessboard);
    cout << evaluatePosition(chessboard) << endl;

    char** sourceChessboard = findBestMove(chessboard);
    copyChessboard(chessboard, sourceChessboard);
    displayChessboard(chessboard);
    cout << evaluatePosition(chessboard) << endl;


    break;



    }
    case 1:
        char chessboard[8][8];
        char** sourceChessboard = generateStartingChessboard();

        // Копируем значения из sourceChessboard в chessboard
        copyChessboard(chessboard, sourceChessboard);

        // Вывод начальной доски
        displayChessboard(chessboard);


        int FromRow, FromCol, ToRow, ToCol;

        cout << "Координаты фигуры:" << endl;
        cin >> FromRow >> FromCol;
        cout << endl << chessboard[FromRow][FromCol] << endl;
        cout << "Координаты места:" << endl;
        cin >> ToRow >> ToCol;   
        cout << endl << chessboard[ToRow][ToCol] << endl;

        sourceChessboard = move(chessboard, FromRow, FromCol, ToRow, ToCol);
        //cout << endl << chessboard[1][2] << " " << chessboard[2][2] << endl; 
        
        copyChessboard(chessboard, sourceChessboard);
        displayChessboard(chessboard);


        break;
    }

    return 0;
}
