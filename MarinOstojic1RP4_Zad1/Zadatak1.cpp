#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

const int redovi = 20;
const int stupci = 40;
const char trenutniZnak = '@';
const char pocetakZnak = 'A';
const char krajZnak = 'B';
const char praznoZnak = '.';

vector<pair<int, int>> bfs(pair<int, int> pocetak, pair<int, int> kraj) {
    queue<pair<int, int>> red;
    vector<vector<pair<int, int>>> roditelj(redovi, vector<pair<int, int>>(stupci, make_pair(-1, -1)));
    vector<vector<bool>> posjeceno(redovi, vector<bool>(stupci, false));

    red.push(pocetak);
    posjeceno[pocetak.first][pocetak.second] = true;

    vector<pair<int, int>> smjerovi = { make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1) };

    while (!red.empty()) {
        int x = red.front().first;
        int y = red.front().second;
        red.pop();

        if (make_pair(x, y) == kraj) break;

        for (auto smjer : smjerovi) {
            int nx = x + smjer.first;
            int ny = y + smjer.second;
            if (nx >= 0 && nx < redovi && ny >= 0 && ny < stupci && !posjeceno[nx][ny]) {
                red.push(make_pair(nx, ny));
                posjeceno[nx][ny] = true;
                roditelj[nx][ny] = make_pair(x, y);
            }
        }
    }

    vector<pair<int, int>> put;
    for (auto at = kraj; at != make_pair(-1, -1); at = roditelj[at.first][at.second]) {
        put.push_back(at);
    }
    put.push_back(pocetak);
    reverse(put.begin(), put.end());
    return put;
}

void ispisiMrezu(pair<int, int> trenutni, pair<int, int> pocetak, pair<int, int> kraj) {
    vector<vector<char>> mreza(redovi, vector<char>(stupci, praznoZnak));

    mreza[pocetak.first][pocetak.second] = pocetakZnak;
    mreza[kraj.first][kraj.second] = krajZnak;
    mreza[trenutni.first][trenutni.second] = trenutniZnak;

    for (const auto& redak : mreza) {
        for (const auto& celija : redak) {
            cout << celija;
        }
        cout << endl;
    }
}

int main() {
    int xa, ya;
    int xb, yb;
    cout << "Upisi pocetak tocke A (x,y)";
    cin >> xa >> ya;
    cout << "Upisi kraj tocke B (x,y)";
    cin >> xb >> yb;
    pair<int, int> pocetak = { ya, xa };
    pair<int, int> kraj = { yb, xb };

    vector<pair<int, int>> put = bfs(pocetak, kraj);

    for (const auto& trenutni : put) {
        system("clear");
        ispisiMrezu(trenutni, pocetak, kraj);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
