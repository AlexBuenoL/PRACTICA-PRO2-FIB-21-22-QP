/** @file Jugador.cc
    @brief Código de la clase Jugador
*/

#include "Jugador.hh"
using namespace std;

Jugador::Jugador() {
    id = " ";
    pos_ranking = 0;
    ptos = 0;
    torneos_disputados = 0;
    partidos_ganados = 0;
    partidos_perdidos = 0;
    sets_ganados = 0;
    sets_perdidos = 0;
    juegos_ganados = 0;
    juegos_perdidos = 0;
    ptos_torneo_actual = 0;
}

Jugador::Jugador(string& id_j) {
    id = id_j;
    pos_ranking = 0;
    ptos = 0;
    torneos_disputados = 0;
    partidos_ganados = 0;
    partidos_perdidos = 0;
    sets_ganados = 0;
    sets_perdidos = 0;
    juegos_ganados = 0;
    juegos_perdidos = 0;
    ptos_torneo_actual = 0;
}

Jugador::Jugador(string& id_j, int i) {
    id = id_j;
    pos_ranking = i;
    ptos = 0;
    torneos_disputados = 0;
    partidos_ganados = 0;
    partidos_perdidos = 0;
    sets_ganados = 0;
    sets_perdidos = 0;
    juegos_ganados = 0;
    juegos_perdidos = 0;
    ptos_torneo_actual = 0;
}

void Jugador::sum_ptos(int x) {
    ptos += x;
    ptos_torneo_actual = x;
    ++torneos_disputados;
}

void Jugador::rest(int x) {
    ptos -= x;
    if (ptos < 0) ptos = 0;
}

void Jugador::modificar_posicion(int x) {
    pos_ranking = x;
}

void Jugador::sumar_juegos(int x) {
    juegos_ganados += x;
}

void Jugador::restar_juegos(int x) {
    juegos_perdidos += x;
}

void Jugador::sumar_set() {
    ++sets_ganados;
}

void Jugador::restar_set() {
    ++sets_perdidos;
}

void Jugador::sumar_partido() {
    ++partidos_ganados;
}

void Jugador::restar_partido() {
    ++partidos_perdidos;
}

string Jugador::consultar_nombre() const {
    return id;
}

int Jugador::consultar_posicion() const{
    return pos_ranking;
}

int Jugador::consultar_puntos() const{
    return ptos;
}

int Jugador::consultar_ptos_rest() const{
    return ptos_torneo_actual;
}

void Jugador::listar_jugador() const{
    cout << id << ' ';
    cout << "Rk:" << pos_ranking << ' ';
    cout << "Ps:" << ptos << ' ';
    cout << "Ts:" << torneos_disputados << ' ';
    cout << "WM:" << partidos_ganados << ' ';
    cout << "LM:" << partidos_perdidos << ' ';
    cout << "WS:" << sets_ganados << ' ';
    cout << "LS:" << sets_perdidos << ' ';
    cout << "WG:" << juegos_ganados << ' ';
    cout << "LG:" << juegos_perdidos << endl;
}

