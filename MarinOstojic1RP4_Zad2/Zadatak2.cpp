#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

 int redovi = 20;
 int stupci = 40;
 char trenutniZnak = '@';
 char pocetakZnak = 'A';
 char krajZnak = 'B';
 char praznoZnak = '.';
 char zidZnak = '#';
 int beskonacnost = 1e9;

struct Pozicija {
    int x, y;
    bool operator==(const Pozicija& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Pozicija& other) const {
        return !(*this == other);
    }
};

vector<Pozicija> dijkstra(Pozicija pocetak, Pozicija kraj,  vector<vector<char>>& mreza) {
    vector<vector<int>> udaljenost(redovi, vector<int>(stupci, beskonacnost));
    vector<vector<Pozicija>> roditelj(redovi, vector<Pozicija>(stupci, { -1, -1 }));
    udaljenost[pocetak.x][pocetak.y] = 0;

    auto usporedba = [&](Pozicija a, Pozicija b) {
        return udaljenost[a.x][a.y] > udaljenost[b.x][b.y];
        };

    priority_queue<Pozicija, vector<Pozicija>, decltype(usporedba)> red(usporedba);
    red.push(pocetak);

    vector<Pozicija> smjerovi = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    while (!red.empty()) {
        Pozicija trenutni = red.top();
        red.pop();

        if (trenutni == kraj) break;

        for (auto smjer : smjerovi) {
            int nx = trenutni.x + smjer.x;
            int ny = trenutni.y + smjer.y;

            if (nx >= 0 && nx < redovi && ny >= 0 && ny < stupci && mreza[nx][ny] != zidZnak) {
                int novaUdaljenost = udaljenost[trenutni.x][trenutni.y] + 1;
                if (novaUdaljenost < udaljenost[nx][ny]) {
                    udaljenost[nx][ny] = novaUdaljenost;
                    roditelj[nx][ny] = trenutni;
                    red.push({ nx, ny });
                }
            }
        }
    }

    vector<Pozicija> put;
    for (Pozicija at = kraj; at != Pozicija{ -1, -1 }; at = roditelj[at.x][at.y]) {
        if (at.x < 0 || at.x >= redovi || at.y < 0 || at.y >= stupci) {
            break;
        }
        put.push_back(at);
    }
    put.push_back(pocetak);
    reverse(put.begin(), put.end());
    return put;
}

void ispisiMrezu(Pozicija trenutni, Pozicija pocetak, Pozicija kraj,  vector<vector<char>>& mreza) {
    vector<vector<char>> mrezaKopija = mreza;

    mrezaKopija[pocetak.x][pocetak.y] = pocetakZnak;
    mrezaKopija[kraj.x][kraj.y] = krajZnak;
    mrezaKopija[trenutni.x][trenutni.y] = trenutniZnak;

    for ( auto& redak : mrezaKopija) {
        for ( auto& celija : redak) {
            cout << celija;
        }
        cout << endl;
    }
}

int main() {
    int xa, ya;
    int xb, yb;

    cout << "Upisi pocetak tocke A : ";
    cin >> xa;
    cout << "Upisi kraj tocke A : ";
    cin >> ya;
    cout << "Upisi pocetak tocke B : ";
    cin >> xb;
    cout << "Upisi kraj tocke B : ";
    cin >> yb;

    Pozicija pocetak = { ya, xa };
    Pozicija kraj = { yb, xb };
    vector<vector<char>> mreza(redovi, vector<char>(stupci, praznoZnak));

    for (int i = 0; i < 10; i++) {
        mreza[3 + i][10] = zidZnak;
    }

    vector<Pozicija> put = dijkstra(pocetak, kraj, mreza);

    for ( auto& trenutni : put) {
        system("cls");
        ispisiMrezu(trenutni, pocetak, kraj, mreza);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
