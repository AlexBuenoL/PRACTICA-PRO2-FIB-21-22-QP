/** @file Jugador.hh
    @brief Especificación de la clase Jugador */

#ifndef JUGADOR_HH
#define JUGADOR_HH

#ifndef NO_DIAGRAM 
#include <iostream>
#include <string>
#endif
using namespace std;

/** @class Jugador
    @brief Representa un jugador.
    Contiene un identificador en forma de string que representa a cada jugador
    y una serie de atributos en forma de enteros que representan las estadísticas 
    de cada jugador: posición en el ranking, puntos actuales, torneos disputados,
    partidos ganados y perdidos, sets ganados y perdidos, juegos ganados y perdidos, 
    y los puntos ganados en la edición actual o en la última edición del torneo. */
class Jugador {

private:
    
    string id;
    int pos_ranking;
    int ptos;
    int torneos_disputados;
    int partidos_ganados;
    int partidos_perdidos;
    int sets_ganados;
    int sets_perdidos;
    int juegos_ganados;
    int juegos_perdidos;
    int ptos_torneo_actual;
    
public:
    
    // Constructores
    
    /** @brief Creador por defecto
        Se genera un Jugador automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es un Jugador no inicializado
    */
    Jugador();
    
    /** @brief Creador inicializado
        Se genera un Jugador inicializado con un string como identificador 
        \pre <em>Cierto</em>
        \post El resultado es un Jugador inicializado con identificador = id_j 
        y el resto de los atributos inicializados a 0
    */
    Jugador(string& id_j);
    
    /** @brief Creador inicializado 
        Se genera un Jugador inicializado con nombre y posicion en el ranking
        \pre <em>Cierto</em>
        \post El resultado es un jugador inicializado con identificador = id_j
        y posicion en el ranking = i    */
    Jugador(string& id_j, int i);
    
    
    // Modificadores

    /** @brief Se suma al Jugador los puntos pasados 
        como parametro
        \pre Jugador inicializado
        \post Se han sumado a los puntos del Jugador 
        los puntos pasados como parametro
    */
    void sum_ptos(int x);
    
    /** @brief Se restan al jugador los puntos indicados
        \pre Jugador inicializado
        \post Se han restado a los puntos del Jugador 
        los puntos pasados como parametro
    */
    void rest(int x);
    
    /** @brief Se modifica la posicion en el ranking del Jugador 
        \pre 1 <= x <= numero de jugadores
        \post Se ha cambiado la posicion en el ranking del Jugador por x
    */
    void modificar_posicion(int x);

    /** @brief Se suman al Jugador los juegos indicados
        \pre Jugador inicializado
        \post Se han sumado a los juegos del Jugador 
        los juegos pasados como parametro
    */
    void sumar_juegos(int x);
    
    /** @brief Se restan al Jugador los juegos indicados
        \pre Jugador inicializado
        \post Se han restado a los juegos del Jugador 
        los juegos pasados como parametro
    */
    void restar_juegos(int x);
    
    /** @brief Se suma al Jugador un set ganado
        \pre Jugador inicializado
        \post Se ha sumado a los sets del Jugador 
        un set ganado
    */
    void sumar_set();
    
    /** @brief Se suma al Jugador un set perdido
        \pre Jugador inicializado
        \post Se ha sumado a los sets del Jugador 
        un set perdido
    */
    void restar_set();
    
    /** @brief Se suma al Jugador un partido ganado
        \pre Jugador inicializado
        \post Se ha sumado al Jugador un partido ganado
    */
    void sumar_partido();
    
    /** @brief Se suma al Jugador un partido pertido
        \pre Jugador inicializado
        \post Se ha sumado al Jugador un partido perdido
    */
    void restar_partido();
    

    // Consultores
    
    /** @brief Consultor del nombre del Jugador
        \pre Jugador inicializado
        \post Se ha devuelto el nombre de Jugador en forma de string
    */
    string consultar_nombre() const;
    
    /** @brief Consultor de la posicion en el ranking del Jugador
        \pre Jugador inicializado
        \post Se ha devuelto la posicion en el ranking del Jugador en forma de entero
    */
    int consultar_posicion() const;
    
    /** @brief Consultor de los puntos del Jugador en el circuito
        \pre Jugador inicializado
        \post Se han devuelto los puntos actuales del Jugador en forma de entero
    */
    int consultar_puntos() const;
    
    /** @brief Consultor de los puntos del Jugador en el torneo actual 
        o el último disputado
        \pre Jugador inicializado 
        \post Se han devuelto los puntos del Jugador en el torneo actual 
        o el último disputado
    */
    int consultar_ptos_rest() const;
    
    
    // Lectura y escritura
    
    /** @brief Se lista un Jugador con identificador
        \pre Jugador inicializado
        \post Se ha escrito a traves del canal estándar de salida su nombre, posicion 
        en el ranking, puntos, y el resto de estadisticas del Jugador en el circuito
    */
    void listar_jugador() const;
};
#endif
