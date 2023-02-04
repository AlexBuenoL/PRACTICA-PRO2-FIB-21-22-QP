/** @file Categoria.cc
    @brief Código de la clase Categoria */

#include "Categoria.hh"
using namespace std;

Categoria::Categoria() {
    id = 0;
}

Categoria::Categoria(string& id_cat) {
    id = 0;
    name = id_cat;
}

Categoria::Categoria(string& id_cat, int x) {
    name = id_cat;
    id = x;
}

void Categoria::asignar_puntos(int k) {
    int x;
    for (int i = 1; i <= k; ++i) {
        cin >> x;
        ptos_por_nivel.insert(make_pair(i, x));
    }
}

string Categoria::consultar_nombre_categoria() const{
    return name;
}

int Categoria::consultar_puntos(int nivel) {
    return ptos_por_nivel[nivel];
}

void Categoria::listar_categoria(int k) {
    cout << name << ' ';
    for (int i = 1; i < k; ++i) {
        cout << ptos_por_nivel[i] << ' ';
    }
    cout << ptos_por_nivel[k] << endl;
}


