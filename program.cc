/**
@mainpage Práctica de PRO2: Circuito de torneos de tenis
Programa de simulación de la gestión deportiva y el cálculo del ranking de 
un circuito de torneos de tenis. */

/** @file program.cc
    @brief Programa principal para la práctica <em>Circuito de torneos de tenis</em> */

#include "Jugador.hh"
#include "ConjuntoJugadores.hh"
#include "Torneo.hh"
#include "ConjuntoTorneos.hh"
#include "Categoria.hh"

#ifndef NO_DIAGRAM 
#include <iostream>
#include <vector>
#include <string>
#include "BinTree.hh"
#include "ParInt.hh"
#include <map>
#include <cmath>
#endif

using namespace std;

/** @brief Programa principal para la práctica <em>Circuito de torneos de tenis</em>. */

int main() {
    
    // Se lee el numero de categorias
    int c; 
    cin >> c;
    
    // Se lee el numero maximo de niveles de los torneos
    int k;
    cin >> k;
    
    // Declaramos un map de categorias con un entero como clave
    map<int, Categoria> map_cat;
    
    // Leemos el nombre de cada una y asignamos el indentificador 
    // string y el identificador entero en cada categoria
    string id_cat;
    for (int i = 1; i <= c; ++i) {
        cin >> id_cat;
        Categoria cat(id_cat,i);
        map_cat.insert(make_pair(i, cat));
    }
    
    // Leemos los puntos pertenecientes a cada nivel de la categoria 
    // a partir del num. maximo de niveles k
    map<int, Categoria>::iterator it;
    for (it = map_cat.begin(); it != map_cat.end(); ++it)  
        it->second.asignar_puntos(k);
            
    // Declaramos y leemos un conjunto de t torneos
    int t;
    cin >> t;
    ConjuntoTorneos torneos(t);
    torneos.leer_torneos(map_cat);
    
    // Declaramos y leemos un conjunto de p jugadores
    int p;
    cin >> p;
    ConjuntoJugadores jugadores(p);
    jugadores.leer_jugadores();
    
    // Procesamiento de comandos
    string com;
    cin >> com;
    while (com != "fin") {
        
        if (com == "nuevo_jugador" or com == "nj") {

            string id_p;
            cin >> id_p;
            cout << '#' << com << ' ' << id_p << endl;
            
            // Si el jugador con identificador id_p no existe, 
            // añadimos al conjunto de jugadores un jugador 
            // con identificador id_p
            if (not jugadores.existe_jugador(id_p)) {
                jugadores.nuevo_jugador(id_p);
                cout << jugadores.numero_jugadores() << endl;
            } else 
                cout << "error: ya existe un jugador con ese nombre" << endl;
        } 
        
        else if (com == "nuevo_torneo" or com == "nt") {

            string id_to;
            int ca;
            cin >> id_to;
            cin >> ca;
            cout << '#' << com << ' ' << id_to << ' ' << ca << endl;
            
            // Si la categoria "ca" esta entre 1 y c, y no existe el torneo
            // en el conjunto de torneos, se añade un nuevo torneo con 
            // el identificador id_to y de categoria ca
            if (ca < 1 or ca > c) 
                cout << "error: la categoria no existe" << endl;
            else if (torneos.existe_torneo(id_to))
                cout << "error: ya existe un torneo con ese nombre" << endl;
            else {
                Categoria catg = map_cat[ca];
                torneos.nuevo_torneo(id_to, catg);
                cout << torneos.numero_torneos() << endl;
            }
        }
                
        else if (com == "baja_jugador" or com == "bj") {

            string id_p;
            cin >> id_p;
            cout << '#' << com << ' ' << id_p << endl;
            
            // Si existe un jugador con identificador id_p, 
            // se da de baja del conjunto de jugadores del 
            // circuito al jugador con identificador id_p
            if (jugadores.existe_jugador(id_p)) {
                jugadores.baja_jugador(id_p);
                cout << jugadores.numero_jugadores() << endl;
            } else 
                cout << "error: el jugador no existe" << endl;
        }
        
        else if (com == "baja_torneo" or com == "bt") {

            string id_to;
            cin >> id_to;
            cout << '#' << com << ' ' << id_to << endl;
            
            // Si existe un torneo con identificador id_to,
            // se da de baja al torneo con el mismo identificador
            if (torneos.existe_torneo(id_to)) {
                Torneo torn = torneos.consultar_torneo(id_to);
                torn.restar_puntos(jugadores);
                jugadores.actualizar_ranking();
                torneos.baja_torneo(id_to);                  
                cout << torneos.numero_torneos() << endl;
            } else 
                cout << "error: el torneo no existe" << endl;
        }
        
        else if (com == "iniciar_torneo" or com == "it") {

            string id_to;
            cin >> id_to;
            
            // Si existe un torneo con identificador id_to
            // se inicia el torneo con el mismo identificador
            if (torneos.existe_torneo(id_to)) {

                Torneo torn = torneos.consultar_torneo(id_to);

                // se lee 'n' que representa el num. de participantes 
                // y se leen n enteros que representan sus posiciones en el ranking
                // Los participantes se almacenan en el vector 'r'
                int n;
                cin >> n; 
                vector<Jugador> r(n); 
                torn.leer_participantes(r, jugadores);

                cout << '#' << com << ' ' << id_to << endl;

                // Se calcula 'h', la altura del arbol de emparejamientos
                int h = ceil(log2(n))+1; 

                // Se calcula 'j' que representa los jugadores (nodos) del nivel h-1 que no tendrán hijos
                // en el arbol en caso de que el ultimo nivel no este completo
                int j = pow(2, h-1) - n;

                // Declaramos un arbol de enteros con raíz 1 (ganador)
                // y a partir de este arbol construimos el arbol de emparejamientos
                BinTree<int> arb(1);
                torn.definir_emparejamientos(arb, h, 1, 1, j);

                // Asigna el cuadro de emparejamientos y el vector de participantes
                // en el torneo contenido en el conjunto de torneos
                // para poder usar dichos atributos en "finalizar_torneo"
                torneos.definir_cuadro_y_participantes(id_to,arb,r);
                
                // Se imprime el cuadro de emparejamientos
                torn.imprimir_emparejamientos(arb,r);
                cout << endl;
            }
        }
        
        else if (com == "finalizar_torneo" or com == "ft") {

            string id_to;
            cin >> id_to;

            // Si existe un torneo con identificador id_to se finaliza este torneo
            if (torneos.existe_torneo(id_to)) {

                Torneo torn = torneos.consultar_torneo(id_to);

                // Se crea arbol de strings con los resultados leidos
                BinTree<string> res;
                torn.leer_resultados(res);
                
                // "emp" es el cuadro de emparejamientos del torneo
                BinTree<int> emp = torn.consultar_cuadro();
                
                // Se construye el arbol 'a' que representa el cuadro de resultados
                // del torneo una vez disputados los partidos
                BinTree<int> a;
                torn.proc_resultados(a, emp, res);

                cout << '#' << com << ' ' << id_to << endl;
                
                // Se imprimen los resultados del torneo
                torn.imprimir_resultados(a, res);
                cout << endl;
                
                // Se restan los puntos de la edición anterior y se actualizan las estadísticas
                // de cada jugador
                torn.restar_puntos(jugadores);
                torn.actualizar_estadisticas(a, res, 1, jugadores);
                
                // Se listan los puntos que ha ganado cada jugador y se asignan los participantes del torneo,
                // y este se añade al conjunto de torneos
                torn.listar_puntos();
                torneos.definir_ult_jugadores(id_to, torn);

                jugadores.actualizar_ranking();
            }
        }
        
        else if (com == "listar_ranking" or com == "lr") {

            cout << '#' << com << endl;

            // Se lista el ranking perteneciente al conjunto de jugadores
            jugadores.listar_ranking();
        }
        
        else if (com == "listar_jugadores" or com == "lj") {

            cout << '#' << com << endl;
            
            // Se listan los jugadores del conjunto de jugadores
            jugadores.listar_jugadores();
        }
        
        else if (com == "consultar_jugador" or com == "cj") {

            string id_p;
            cin >> id_p;
            cout << '#' << com << ' ' << id_p << endl;
            
            // Si existe un jugador con identificador id_p 
            // se lista a este jugador
            if (jugadores.existe_jugador(id_p)) {
                Jugador jug = jugadores.consultar_jugador(id_p);
                jug.listar_jugador();
            } else 
                cout << "error: el jugador no existe" << endl;
        }
        
        else if (com == "listar_torneos" or com == "lt") {

            // Se listan los torneos del conjunto de torneos
            cout << '#' << com << endl;
            torneos.listar_torneos();
        }
        
        else if (com == "listar_categorias" or com == "lc") {

            cout << '#' << com << endl;
            cout << c << ' ' << k << endl;
            
            // Listamos las categorias del vector vcat inicializado al principio
            for (it = map_cat.begin(); it != map_cat.end(); ++it) 
                it->second.listar_categoria(k);
        }
        cin >> com;
    }
}
    
    
    
    
    
    
    
