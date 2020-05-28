#include <iostream>
#include "../inc/SWektor.hh"

using namespace std;

void kwadrat(int x, int y) {
    cout << x-25 << " " << y-25 << " " << 180 << endl;
    cout << x+25 << " " << y-25 << " " << 180 << endl;
    cout << x+25 << " " << y+25 << " " << 180 << endl;
    cout << x-25 << " " << y+25 << " " << 180 << endl;
    cout << x-25 << " " << y-25 << " " << 180 << endl;
    cout << endl;
}

int main() {

//     for(int x = -275; x <= 275; x+=50)
//         for(int y = -275; y <= 275; y+=50)
//             kwadrat(x,y);

    SWektor<double, 3> pom;
    int counter = 0;

    while(cin >> pom) {
        pom = pom * 20;
        cout << pom;
        if(++counter % 4 == 0) {
            cout<<"#\n\n";
        }
    }
}