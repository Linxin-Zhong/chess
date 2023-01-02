# chess
## 1.0 Introduction
### Layout


https://user-images.githubusercontent.com/77327417/210188942-b6874923-ab97-4c11-a583-c70d26287352.mp4


### Background
<p>The purpose of this project is to implement a standard chess game for two players, including
human and computer players. It should support human vs. human, human vs. computer, and
computer vs. computer. Computer players operate at different difficult levels from 1 to 4,
where the difficulty increases as the level increases. The rules in the program are exactly the
same as the rules in a standard chess game. This project supports all features included in standard chess game such as "En Passant", castling, and pawn promotion.</p>

### 4 Levels of Human-Computer Game
<p> Level1: The computer moves completely random</p>
<p> Level2: Prioritize moves that can both capture and check. If a move can only capture or check, it prioritize check moves over capture moves. </p>
<p> Level3: (check + capture + avoid)  > (check + capture) / (check + avoid) > (check) > (avoid) / (capture) > all other moves </p>
<p> Note: check -> a move that can chess the other player</p>
<p>       capture -> a move that can capture one of the other player's piece</p>
<p>       avoid -> a move that save one of own pieces from the other players area of capture</p>
<p>       For moves that are in the same level, level 2 and 3 computer players choose at random</p>
<p> Level4: Choose movements based on the values we
assigned to each type of piece. The values are ordered from highest to lowest: King (100),
Bishop (3), Knight (3), Pawn (1), Queen(9), and Rook (5). When a move is made, computer level 4 will
compare the values of each available move and choose the move that has the highesr value. When a piece captures another piece, the value of
the piece being captured is added to the value of this move. When a piece avoids another
piece, the value of this move will be the value of this piece itself. When a piece checks, the
value of this move will be the value of the king.</p>

## 2.0 Program Design
![image](https://user-images.githubusercontent.com/77327417/210194909-f7bb1d4a-f1db-4ad6-a535-90aaf2abab9a.png)

### Classes
<p>Board: 
Board is the core of the game, which owns Piece, has Strategy (Strategy pattern),
and inherited from Subject (Observer pattern). It records the positions and count of the
pieces, sets up the game board, clears the board, and initializes the players. It is also
responsible for the algorithms for check, checkmate and stalemate.</p>
<p>Piece: 
The class Piece contains six different child classes corresponding to the Pawn, Knight,
Rook, Bishop, Queen and King. Each overrides a version of the function check,
legalMoves, captureMoves, avoidMoves, and checkMoves. The function
check detects if the given non-empty coordinate can be eaten by the current piece. The
corresponding move function (legalMoves, captureMoves, avoidMoves,
checkMoves) is to find all the moves (legal moves, capture moves, avoid moves, check
moves) a piece is able to do respectively.</p>
<p>Observer: 
Both the TextObserver and GraphicalObserver are the child classes of the abstract
base class observer. They render and output the chess board after each move
(notify()). This is part of the implementation of the observer pattern.</p>
<p>Strategy: 
The Strategy class contains four different levels and one human player level that override
the function generateMove, which generates the coordinate of the piece that the computer
player wants to move from and move to. And for human players, the function
generateMove takes input coordinates and determines the validity of the move
represented by the input. This is the implementation of the strategy pattern.</p>
