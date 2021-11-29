#include "board.h"

using namespace std;

bool Board::isCheck() {

}

bool Board::isCheckMate() {

}

bool Board::isStalemate() {

}

void Board::update(char c, int i) {

}

bool Board::isRun() {

}

Board::Board(char w, char b) {
    switch (w) {
        case 'h':
            this->WPlayer = make_shared<Human>(Human(make_shared<Board>(*this)));
        case '1':
            this->WPlayer = make_shared<Level1>(Level1(make_shared<Board>(*this)));
        case '2':
            this->WPlayer = make_shared<Level2>(Level1(make_shared<Board>(*this)));
        case '3':
            this->WPlayer = make_shared<Level2>(Level1(make_shared<Board>(*this)));
    }
    switch (b) {
        case 'h':
            this->BPlayer = make_shared<Human>(Human(make_shared<Board>(*this)));
        case '1':
            this->BPlayer = make_shared<Level1>(Level1(make_shared<Board>(*this)));
        case '2':
            this->BPlayer = make_shared<Level2>(Level1(make_shared<Board>(*this)));
        case '3':
            this->BPlayer = make_shared<Level2>(Level1(make_shared<Board>(*this)));
    }
};

void Board::resign() {

}

void Board::render() {

}
