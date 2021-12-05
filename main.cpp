#include <iostream>
#include "board.h"


using namespace std;
int main() {
    Board a = Board('h', '1');
    a.print();
    cout << endl;
    a.move('d', 1, 'd', 4);
    a.print();
    a.move('d', 4, 'd', 8);
    a.print();
}
