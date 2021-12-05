#include <iostream>
#include "board.h"


using namespace std;
int main() {
    Board a = Board('h', '1');
    //Test rook check
    a.move('e', 2, 'a', 3);
    a.print();
    a.move('a', 8, 'e', 6);
    a.print();
}
