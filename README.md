# Chess_project

This project implements a simple chess AI that makes three optimal moves for white pieces.

## Overview

The project consists of the following components:

1. **Chessboard Representation:** The chessboard is represented using a 2D vector of characters in C++. The pieces are denoted by characters ('P' for pawn, 'R' for rook, etc.).

2. **Move Validation:** The program checks the validity of chess moves based on the rules of each piece. The `isValidMove` function is used for this purpose.

3. **AI Logic:** The AI evaluates possible moves and selects the optimal ones based on a simple scoring system. The `findBestMoves` function returns a vector of chessboards representing the optimal moves.

4. **Evaluation Function:** The `evaluatePosition` function assigns scores to different chessboard configurations based on piece values, check status, and checkmate conditions.

## Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/chess-ai.git
   ```

2. Build and run the program using your preferred C++ compiler.

   ```bash
   g++ main.cpp -o chess_ai
   ./chess_ai
   ```

3. Follow the instructions to make three optimal moves for white pieces.

