/** @file ConjuntoJugadores.cc
    @brief Código de la clase ConjuntoJugadores
*/

#include "ConjuntoJugadores.hh"
#include <algorithm>
using namespace std;

// Funciones privadas

void ConjuntoJugadores::swap(vector<Jugador>& rank, int x, int y) {
    Jugador aux = rank[y];
    rank[y] = rank[x];
    rank[x] = aux;
}

bool ConjuntoJugadores::cmp(Jugador& a, Jugador& b) {
    if (a.consultar_puntos() != b.consultar_puntos()) 
        return a.consultar_puntos() > b.consultar_puntos();
    return a.consultar_posicion() < b.consultar_posicion();
}


// Funciones publicas

ConjuntoJugadores::ConjuntoJugadores() {
    njug = 0;
}

ConjuntoJugadores::ConjuntoJugadores(int p) {
    njug = p;
}

void ConjuntoJugadores::nuevo_jugador(string& id_p) {
    ++njug;
    Jugador jug(id_p, njug);
    map_jug.insert(make_pair(id_p, jug));
    rank.push_back(jug);
}

void ConjuntoJugadores::baja_jugador(string& id_p) {

    // Eliminamos al jugador del mapa y disminuimos el numero de jugadores
    --njug;
    map_jug.erase(id_p);
    
    // Buscamos el jugador que queremos eliminar en el ranking y lo intercambiamos con 
    // los jugadores posteriores subiendo la posición de estos jugadores hasta dejar 
    // al jugador eliminado ultimo y hacemos pop_back para eliminarlo
    int n = rank.size();
    int i = 0;
    bool trobat = false;
    while (i < n-1 and not trobat) {
        if (rank[i].consultar_nombre() == id_p) {
            trobat = true;
            for (int j = i; j < n-1; ++j) {
                swap(rank, j, j+1);
                string x = rank[j].consultar_nombre();
                map_jug[x].modificar_posicion(j+1);
            }
        }
        ++i;
    }
    rank.pop_back();
}

void ConjuntoJugadores::actualizar_ranking() {

    // Ordenamos el vector decrecientemente por puntos
    sort(rank.begin(), rank.end(), cmp);
    
    // En el caso de que algun jugador no tenga la posicion que indica el ranking, se modifica
    string x;
    for (int i = 0; i < njug; ++i) {
        x = rank[i].consultar_nombre();
        map_jug[x].modificar_posicion(i+1);
        rank[i].modificar_posicion(i+1);
    }
}

void ConjuntoJugadores::sumar_restar_juegos(int a, int b, int x, int y, const vector<Jugador>& part) {
    string nom = part[a-1].consultar_nombre();
    map_jug[nom].sumar_juegos(x);
    map_jug[nom].restar_juegos(y);

    nom = part[b-1].consultar_nombre();
    map_jug[nom].sumar_juegos(y);
    map_jug[nom].restar_juegos(x);
}

void ConjuntoJugadores::sumar_restar_set(int a, int b, const vector<Jugador>& part) {
    string nom = part[a-1].consultar_nombre();
    map_jug[nom].sumar_set();

    nom = part[b-1].consultar_nombre();
    map_jug[nom].restar_set();
}

void ConjuntoJugadores::sumar_restar_partido(int a, int b, const vector<Jugador>& part) {
    string nom = part[a-1].consultar_nombre();
    map_jug[nom].sumar_partido();

    nom = part[b-1].consultar_nombre();
    map_jug[nom].restar_partido();
}

void ConjuntoJugadores::sumar_puntos(Categoria& cat, int nivel, int a, vector<Jugador>& part) {
    int x = cat.consultar_puntos(nivel);
    string nom = part[a-1].consultar_nombre();
    int i = map_jug[nom].consultar_posicion();

    rank[i-1].sum_ptos(x);
    map_jug[nom].sum_ptos(x);
    part[a-1].sum_ptos(x);

}

void ConjuntoJugadores::restar(string& id_p, int pt) {

    // Si el jugador con identificador "id_p" está dentro del conjunto de jugadores, 
    // se le restan los puntos y se le restan al mismo jugador del ranking
    map<string, Jugador>::iterator it = map_jug.find(id_p);
    if (it != map_jug.end()) {
        map_jug[id_p].rest(pt);
        int i = map_jug[id_p].consultar_posicion();
        rank[i-1].rest(pt);
    }
    
}

bool ConjuntoJugadores::existe_jugador(string& id_p) {
    map<string, Jugador>::iterator it = map_jug.find(id_p);
    if (it != map_jug.end()) return true;
    else return false;
}

int ConjuntoJugadores::numero_jugadores() const{
    return njug;
}

Jugador ConjuntoJugadores::consultar_jugador(string& id_p) {
    return map_jug[id_p];
}

Jugador ConjuntoJugadores::consultar_jugador_rank(int x) const{
    return rank[x-1];
}

void ConjuntoJugadores::leer_jugadores() {
    string name;
    for (int i = 1; i <= njug; ++i) {
        cin >> name;
        Jugador jug(name,i);
        map_jug.insert(make_pair(name, jug));
        rank.push_back(jug);
    }
}

void ConjuntoJugadores::listar_ranking() const{
    for (int i = 0; i < njug; ++i) 
        cout << i+1 << ' ' << rank[i].consultar_nombre() << ' ' << rank[i].consultar_puntos() << endl;
    
}

void ConjuntoJugadores::listar_jugadores() {
    cout << njug << endl;
    map<string, Jugador>::iterator it;
    for (it = map_jug.begin(); it != map_jug.end(); ++it)  
        it->second.listar_jugador();
}

