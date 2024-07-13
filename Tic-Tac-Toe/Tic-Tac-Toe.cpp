#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Prototipos de funciones
void Juego();
void MostrarTablero(const vector<vector<char>>& tablero);
bool EsGanador(const vector<vector<char>>& tablero, char jugador);
bool EsEmpate(const vector<vector<char>>& tablero);
pair<int, int> Jugada();
bool EsNumero(const string& str);

int main() {
    string opcion;
    do {
        Juego();
        cout << endl;
        cout << "Si quiere seguir jugando presione Y, de lo contrario presione cualquier otra tecla: ";
        cin >> opcion;
        system("cls"); // Se limpia la consola
    } while (opcion == "Y" || opcion == "y");
}

void Juego() {
    vector<string> jugador(2);
    vector<vector<char>> tablero(3, vector<char>(3, ' '));
    char OX[2] = { 'O', 'X' };
    int turno = 0;

    for (int i = 0; i < 2; i++) {
        cout << "Nombre del jugador " << i + 1 << ": ";
        cin >> jugador[i];
        cout << endl;
    }

    while (turno < 9) {
        MostrarTablero(tablero);
        int jugadorActual = turno % 2;
        cout << "Es el turno de " << jugador[jugadorActual] << " -> | " << OX[jugadorActual] << " |" << endl;
        auto [fila, columna] = Jugada();//Asegúrate de usar un compilador de C++ que sea compatible con C++17 o una versión posterior

        if (tablero[fila][columna] != ' ') {
            cout << "Jugada inválida, esa posición ya está ocupada." << endl;
            continue;
        }

        tablero[fila][columna] = OX[jugadorActual];

        if (EsGanador(tablero, OX[jugadorActual])) {
            MostrarTablero(tablero);
            cout << "El ganador es " << jugador[jugadorActual] << endl;
            return;
        }

        if (EsEmpate(tablero)) {
            MostrarTablero(tablero);
            cout << "Es un empate." << endl;
            return;
        }

        turno++;
    }
}

void MostrarTablero(const vector<vector<char>>& tablero) {
    system("cls");
    cout << " " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << " " << endl;
    cout << "---+---+---" << endl;
    cout << " " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << " " << endl;
    cout << "---+---+---" << endl;
    cout << " " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << " " << endl;
}

bool EsGanador(const vector<vector<char>>& tablero, char jugador) {
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador)
            return true;
        if (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)
            return true;
    }
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador)
        return true;
    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)
        return true;
    return false;
}

bool EsEmpate(const vector<vector<char>>& tablero) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ')
                return false;
    return true;
}

pair<int, int> Jugada() {
    string jugada;
    int fila, columna;
    do {
        cout << "Ingrese la jugada (fila y columna, de 1 a 3): ";
        cin >> jugada;
        if (jugada.length() == 2 && EsNumero(jugada.substr(0, 1)) && EsNumero(jugada.substr(1, 1))) {
            fila = jugada[0] - '1';
            columna = jugada[1] - '1';
            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3)
                break;
        }
        cout << "Jugada inválida, ingrese números entre 1 y 3." << endl;
    } while (true);
    return { fila, columna };
}

bool EsNumero(const string& str) {
    for (char c : str)
        if (!isdigit(c))
            return false;
    return true;
}
