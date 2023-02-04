/** @file Torneo.cc
    @brief Código de la clase Torneo */

#include "Torneo.hh"
#ifndef NO_DIAGRAM
#include <cmath>
#endif
using namespace std;

// Funciones privadas

vector<ParInt> Torneo::conv(const string& res) {

    vector<ParInt> v;
    int n = res.length();
    int x, y, cont = 0;

    for (int i = 0; i < n; ++i) {
        if (res[i] >= '0' and res[i] <= '7') {
            if (cont == 0) x = res[i] - '0';
            else y = res[i] - '0';
            ++cont;
        }

        if (cont == 2) {
            ParInt p(x,y);
            v.push_back(p);
            cont = 0;
        }
    }
    return v;
}

int Torneo::match(int a, int b, const string& res) {

    if (res == "1-0") return a;
    else if (res == "0-1") return b;
    else {

        // vector de sets dels resultats
        vector<ParInt> v = conv(res);
        int n = v.size();
        int x = 0, y = 0;

        for (int i = 0; i < n; ++i) {
            if (v[i].primer() > v[i].segon()) ++x;
            else ++y;
        }

        if (x > y) return a;
        else return b;
    }
}


// Funciones publicas

Torneo::Torneo() {
    id = " ";
}

Torneo::Torneo(string& id_to) {
    id = id_to;
}

Torneo::Torneo(string& id_to, Categoria& ca) {
    id = id_to;
    cat = ca;
}

void Torneo::definir_emparejamientos(BinTree<int>& arb, int h, int l, int a, int x) {

    // Si estamos en el ultimo nivel, tenemos un nodo sin hijos
    if (l == h) 
        arb = BinTree<int>(a);
    
    // Si no estamos en el ultimo nivel:
    else {

        // Si a es del nivel h-1 y a <= m-1, tenemos un nodo sin hijos
        if (l == h-1 and a <= x) 
            arb = BinTree<int>(a);  
        
        else {
            int b = pow(2, l) + 1 - a;
            BinTree<int> izq(a);
            BinTree<int> der(b);
            definir_emparejamientos(izq, h, l+1, a, x);
            definir_emparejamientos(der, h, l+1, b, x);
            arb = BinTree<int>(a,izq,der);
        } 
    }
}

void Torneo::asignar_cuadro_emp_participantes(const BinTree<int>& arb, const vector<Jugador>& r) {
    cuadro_emp = arb;
    jug_edicion_actual = r;
}

void Torneo::proc_resultados(BinTree<int>& a, const BinTree<int>& emp, const BinTree<string>& res) {

    if (emp.left().empty() and emp.right().empty()) {
        int x = emp.value();
        a = BinTree<int>(x);
    }

    else {

        BinTree<int> izq = emp.left();
        BinTree<int> der = emp.right();

        BinTree<string> izq2 = res.left();
        BinTree<string> der2 = res.right();

        BinTree<int> i;
        BinTree<int> d;

        proc_resultados(i, izq, izq2);
        proc_resultados(d, der, der2);
        
        int x = match(i.value(), d.value(), res.value());
        a = BinTree<int>(x, i, d);
    }
}

void Torneo::act_stats(int a, int b, const string& res, ConjuntoJugadores& jugadores, int nivel) {

    vector<ParInt> v = conv(res);
    int n = v.size();
    int x = 0, y = 0;
    int juegos_a = 0, juegos_b = 0;

    if (n != 1) {
        for (int i = 0; i < n; ++i) {
            juegos_a += v[i].primer();
            juegos_b += v[i].segon();

            if (v[i].primer() > v[i].segon()) {
                jugadores.sumar_restar_set(a, b, jug_edicion_actual);
                ++x;
            } else {
                jugadores.sumar_restar_set(b, a, jug_edicion_actual);
                ++y;
            }
        }

        jugadores.sumar_restar_juegos(a, b, juegos_a, juegos_b, jug_edicion_actual);
    
        if (x > y) {
            jugadores.sumar_restar_partido(a, b, jug_edicion_actual);
            jugadores.sumar_puntos(cat, nivel+1, b, jug_edicion_actual);

        } else {
            jugadores.sumar_restar_partido(b, a, jug_edicion_actual);
            jugadores.sumar_puntos(cat, nivel+1, a, jug_edicion_actual);
        }

        if (nivel == 1) {
            if (x > y) 
                jugadores.sumar_puntos(cat, 1, a, jug_edicion_actual);
            else 
                jugadores.sumar_puntos(cat, 1, b, jug_edicion_actual);
        }

    } else {

        if (v[0].primer() > v[0].segon()) {
            jugadores.sumar_restar_partido(a, b, jug_edicion_actual);
            jugadores.sumar_puntos(cat, nivel+1, b, jug_edicion_actual);
        } else {
            jugadores.sumar_restar_partido(b, a, jug_edicion_actual);
            jugadores.sumar_puntos(cat, nivel+1, a, jug_edicion_actual);
        }
        if (nivel == 1) {
            if (v[0].primer() > v[0].segon()) 
                jugadores.sumar_puntos(cat, 1, a, jug_edicion_actual);
            else 
                jugadores.sumar_puntos(cat, 1, b, jug_edicion_actual);
        }
        
    }
}

void Torneo::actualizar_estadisticas(const BinTree<int>& a, const BinTree<string>& res, int nivel, ConjuntoJugadores& jugadores) {

    if (not res.empty()) {
        act_stats(a.left().value(), a.right().value(), res.value(), jugadores, nivel);
        actualizar_estadisticas(a.left(), res.left(), nivel+1, jugadores);
        actualizar_estadisticas(a.right(), res.right(), nivel+1, jugadores);
    }
}

void Torneo::restar_puntos(ConjuntoJugadores& jugadores) {

    int n = jug_ult_edicion.size();
    if (n != 0) {
        for (int i = 0; i < n; ++i) {
            string id_p = jug_ult_edicion[i].consultar_nombre();
            int x = jug_ult_edicion[i].consultar_ptos_rest();
            jugadores.restar(id_p, x);
        }
    }
}

void Torneo::ult_jugadores(vector<Jugador>& last) {
    jug_ult_edicion = last;
}

BinTree<int> Torneo::consultar_cuadro() const{
    return cuadro_emp;
}

vector<Jugador> Torneo::consultar_participantes() const{
    return jug_edicion_actual;
}

void Torneo::leer_participantes(vector<Jugador>& r, ConjuntoJugadores& jugadores) {
    int n = r.size();
    int x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        r[i] = jugadores.consultar_jugador_rank(x);
    }
}

void Torneo::leer_resultados(BinTree<string>& a) { 

    string x;
    cin >> x;

    if (x != "0") {
        BinTree<string> izq;
        BinTree<string> der;
        leer_resultados(izq);
        leer_resultados(der); 
        a = BinTree<string>(x,izq,der);
    }
}    

void Torneo::imprimir_emparejamientos(const BinTree<int> &a, const vector<Jugador>& v) const{
    
    if (a.left().empty() and a.right().empty())
        cout << a.value() << '.' << v[a.value()-1].consultar_nombre();
    else {
        cout << '(';
        imprimir_emparejamientos(a.left(), v);
        cout << ' ';
        imprimir_emparejamientos(a.right(), v);
        cout << ')';
    }
}

void Torneo::imprimir_resultados(const BinTree<int>& a, const BinTree<string>& res) const{
    
    if (not a.left().empty() and not a.right().empty()) {
        cout << '(';
        cout << a.left().value() << '.' << jug_edicion_actual[a.left().value()-1].consultar_nombre() << " vs ";
        cout << a.right().value() << '.' << jug_edicion_actual[a.right().value()-1].consultar_nombre() << ' ' << res.value();
        imprimir_resultados(a.left(), res.left());
        imprimir_resultados(a.right(), res.right());
        cout << ')';
    } 
}

void Torneo::listar_puntos() const{

    int n = jug_edicion_actual.size();
    for (int i = 0; i < n; ++i) {
        if (jug_edicion_actual[i].consultar_ptos_rest() != 0) 
            cout  << i+1 << '.' << jug_edicion_actual[i].consultar_nombre() << ' ' << jug_edicion_actual[i].consultar_ptos_rest() << endl;
    }
}

void Torneo::listar_torneo() const{
    cout << id << ' ' << cat.consultar_nombre_categoria() << endl;
}






    
