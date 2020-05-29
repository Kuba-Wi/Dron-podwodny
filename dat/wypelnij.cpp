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
    SWektor<double, 3> przesun;
    przesun[0] = 100;
    przesun[1] = 100;
    przesun[2] = -50;
    int counter = 0;

    while(counter < 5) {
        cin >> pom;
        pom = pom + przesun;
        cout << pom;
        // if(++counter % 4 == 0) {
        //     cout<<"#\n\n";
        // }
        if(!cin) {
            cin.clear();
            while(cin.get() != '\n');
            cout<<"#\n\n";
            counter++;
        }
    }
}