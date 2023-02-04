/** @file ConjuntoTorneos.cc
    @brief Código de la clase ConjuntoTorneos */

#include "ConjuntoTorneos.hh"

ConjuntoTorneos::ConjuntoTorneos() {
    ntor = 0;
}

ConjuntoTorneos::ConjuntoTorneos(int t) {
    ntor = t;
}

void ConjuntoTorneos::nuevo_torneo(string& id, Categoria& cat) {
    Torneo torn(id, cat);
    map_tor.insert(make_pair(id, torn));
    ++ntor;
}

void ConjuntoTorneos::baja_torneo(string& id) {
    map_tor.erase(id);
    --ntor;
}

void ConjuntoTorneos::definir_cuadro_y_participantes(string& id_to, const BinTree<int>& arb, const vector<Jugador>& r) {

    // Se asignan al torneo del conjunto el arbol de emparejamientos y el vector de participantes
    map_tor[id_to].asignar_cuadro_emp_participantes(arb,r);
}

void ConjuntoTorneos::definir_ult_jugadores(string& id_to, Torneo& torn) {

    // Se asigna al torneo del conjunto el vector de participantes de la ultima edicion
    vector<Jugador> last = torn.consultar_participantes();
    map_tor[id_to].ult_jugadores(last);
}

bool ConjuntoTorneos::existe_torneo(string& id) {
    map<string, Torneo>::iterator it = map_tor.find(id);
    if (it != map_tor.end()) return true;
    else return false;
}

int ConjuntoTorneos::numero_torneos() const{
    return ntor;
}

Torneo ConjuntoTorneos::consultar_torneo(string& id_to) {
    return map_tor[id_to];
}

void ConjuntoTorneos::leer_torneos(map<int, Categoria>& map_cat) {
    string name;
    int cat;
    for (int i = 1; i <= ntor; ++i) {
        cin >> name;
        cin >> cat;
        Categoria ct = map_cat[cat];
        Torneo torn(name, ct);
        map_tor.insert(make_pair(name, torn));
    }
}

void ConjuntoTorneos::listar_torneos() {
    cout << ntor << endl;
    map<string, Torneo>::iterator it;
    for (it = map_tor.begin(); it != map_tor.end(); ++it) 
        it->second.listar_torneo();
}


    
  
