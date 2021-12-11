#include <iostream>
#include <sstream>
#include "board.h"
#include "piece.h"
#include "textobserver.h"
#include "graphobserver.h"
using namespace std;


int main() {

    float WScore = 0;
    float BScore = 0;
    bool setup = false;

    Board b = Board("empty");
    // for both default and setup board
    char Wplayer;
    char Bplayer;

    cout << "checkerboard loading..." << endl;
    shared_ptr<TextObserver> to = make_shared<TextObserver>(&b);
    shared_ptr<GraphObserver> go = make_shared<GraphObserver>(&b);
    cout << "checkerboard loading completed." << endl;
    cout << "Please use command 'game' to start a game or use 'setup' to enter the set up mode.." << endl;

    while (true) {


        //before starting the first game
        string input;
        getline(cin, input);
        stringstream ss(input);
        string command;
        ss >> command;
        if (command == "game") {
            ss >> command;
            if (command == "human") {
                Wplayer = 'h';
            } else if (command == "computer1") {
                Wplayer = '1';
            } else if (command == "computer2") {
                Wplayer = '2';
            } else if (command == "computer3") {
                Wplayer = '3';
            } else {
                cout << "Invalid command";
                continue;
            }

            ss >> command;
            if (command == "human") {
                Bplayer = 'h';
            } else if (command == "computer1") {
                Bplayer = '1';
            } else if (command == "computer2") {
                Bplayer = '2';
            } else if (command == "computer3") {
                Bplayer = '3';
            } else {
                cout << "Invalid command";
                continue;
            }
            if (!setup) {
                b.clear();
                b.setInit(true);
                b.default_init();
                b.PlayersInit(Wplayer, Bplayer);
            } else {
                b.PlayersInit(Wplayer, Bplayer);
            }
            cout << "Game Starts!" << endl;
            b.print();
            while (true) {
                //while game is running
                if (b.ischeckmate()) {
                    if (b.getCurrentPlayer() == 'W') {
                        BScore++;
                    } else {
                        WScore++;
                    }
                    b.clearCheckStaleMate();
                    cout << "Please use command game or setup to start a new game" << endl;
                    setup = false;
                    break;
                }

                if (b.isstalemate()) {
                    BScore += 0.5;
                    WScore += 0.5;
                    b.clearCheckStaleMate();
                    cout << "Please use command game or setup to start a new game" << endl;
                    setup = false;
                    break;
                }
                string input3;
                getline(cin, input3);
                stringstream ss3(input3);
                string command3;
                ss3 >> command3;
                if (command3 == "move") {
                    b.clearCheck();
                    b.makeMove(input3);
                } else if (command3 == "resign") { // resign ends the game
                    b.setResign();
                    b.print();
                    if (b.getCurrentPlayer() == 'W') {
                        BScore++;
                    } else {
                        WScore++;
                    }
                    b.clearCheckStaleMate();
                    setup = false;
                    cout << "Please use command game or setup to start a new game" << endl;
                    break;
                } else {
                    cout << "invalid command" << endl;
                }
            }
        } else if (command == "setup") {
            b.clear();
            //set up based on empty boards
            int WKingcount = 0;
            int BKingcount = 0;
            string input2;
            cout << "Board cleared, enters setup mode" << endl;

            while (getline(cin, input2)) {
                stringstream ss2(input2);
                string command2;
                ss2 >> command2;
                if (command2 == "+") {
                    char p;
                    ss2 >> p;
                    string coord;
                    ss2 >> coord;
                    if (b.addPiece(p, coord)) {
                        b.print();
                    } else {
                        cout << "Invalid command! But you are still in setup mode:) Use 'done' command to exit" << endl;
                        continue;
                    }
                } else if (command2 == "-") {
                    string coord;
                    ss2 >> coord;
                    if (b.remPiece(coord)) {
                        b.print();
                    } else {
                        cout << "Invalid command! But you are still in setup mode:) Use 'done' command to exit" << endl;
                    }
                } else if (command2 == "=") {
                    ss2 >> command2;
                    if (command2 == "White") {
                        b.setNextPlayer('W');
                        cout << "Next Player set to White" << endl;
                    } else if (command2 == "Black") {
                        b.setNextPlayer('B');
                        cout << "Next Player set to Black" << endl;
                    } else {
                        cout << "Invalid command! But you are still in setup mode:) Use 'done' command to exit" << endl;
                    }
                } else if (command2 == "done") {
                    for (int i = 0; i < 8; i++) { // count the number of Kings in black and white
                        for (int j = 0; j < 8; j++) {
                            char c = (*b.boardmap)[i][j]->type();
                            if (c == 'K') WKingcount++;
                            if (c == 'k') BKingcount++;
                        }
                    }
                    if (BKingcount == 1 && WKingcount == 1) {

                        int checkcol;
                        int checkrow;
                        pair<pair<int, int>, pair<int, int>> kingcoord = b.getKingcoord();
                        int WKR = kingcoord.first.first;
                        int WKC = kingcoord.first.second;
                        int BKR = kingcoord.second.first;
                        int BKC = kingcoord.second.second;
                        if (b.isCheck(*b.boardmap, 'W', WKR, WKC, &checkrow, &checkcol)) {
                            cout << "Cannot start when king is in check, please re-enter setup mode";
                            break;
                        } else if (b.isCheck(*b.boardmap, 'B', BKR, BKC, &checkrow, &checkcol)) {
                            cout << "Cannot start when king is in check, please re-enter setup mode";
                            break;
                        } else {
                            cout << "Setup succeed" << endl;
                            setup = true;
                            b.setInput();
                            break;
                        }
                    } else {
                        cout << "Invalid number of kings, please re-enter the setup mode or start with default board"
                             << endl;
                        break;
                    }

                } else {
                    cout << "Invalid command! But you are still in setup mode:) Use 'done' command to exit" << endl;
                }
            }
        } else if (cin.eof() || command == "quit") { // adds a command to indicate the program is end.
            cout << "Final Score:" << endl;
            cout << "White: " << WScore << endl;
            cout << "Black: " << BScore << endl;
            cout << "Thank you for playing :) Game ended." << endl;
            go->grade(WScore, BScore);
            break;
        } else {
            cout << "Please use command 'game' to start a game or use 'setup' to enter the set up mode." << endl;
        }
    }
}
