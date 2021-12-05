#include <iostream>
#include "board.h"


using namespace std;
int main() {
    Board a = Board('h', '1');
    //Test pawn check
    a.move('d', 2, 'e', 7);
}
