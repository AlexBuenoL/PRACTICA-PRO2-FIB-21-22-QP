/** @file ConjuntoJugadores.hh
    @brief Especificación de la clase ConjuntoJugadores */

#ifndef CONJUNTO_JUGADORES_HH
#define CONJUNTO_JUGADORES_HH

#include "Jugador.hh"
#include "Categoria.hh"

/** @class ConjuntoJugadores
    @brief Representa un conjunto de jugadores.
    Contiene un map que representa al conjunto de jugadores ordenados
    crecientemente por nombre. Y un vector de jugadores 
    denominado rank, representa el ranking ordenado 
    decrecientemente por puntos del jugador
*/    
class ConjuntoJugadores {
    
private:
    
    /** @brief map de <em>Jugador</em> que contiene todos los jugadores del conjunto inscritos en el circuito */
    map<string,Jugador> map_jug;

    /** @brief vector de <em>Jugador</em> que representa el ranking de los jugadores ordenado decrecientemente por puntos */
    vector<Jugador> rank;
    
    int njug;
    
    /** @brief Función privada que intercambia dos jugadores del ranking
        \pre 'x' y 'y' son dos posiciones del ranking "rank"
        \pre 'x' ha ocupado el lugar de 'y', y 'y' ha ocupado el lugar de 
        'x' en el vector "rank"
    */
    static void swap(vector<Jugador>& rank, int x, int y);

    /** @brief Función privada para ordenar el ranking con sort
        \pre 'a' y 'b' son dos jugadores pertenecientes al ranking
        \post Se ha ordenado el ranking decrecientemente por puntos
        y crecientemente por la posicion anterior en caso de empate
    */
    static bool cmp(Jugador& a, Jugador& b);
    
    
public:
    
    // Constructores
    
    /** @brief Creador por defecto
        Se genera un conjunto de jugadores automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es un conjunto de jugadores no inicializado
    */
    ConjuntoJugadores();
    
    /** @brief Creador por defecto
        Se genera un conjunto de p jugadores
        \pre <em>Cierto</em>
        \post El resultado es un conjunto de jugadores no inicializados con p elementos
    */
    ConjuntoJugadores(int p);
    
    
    // Modificadores
    
    /** @brief Se añade un nuevo jugador al conjunto de jugadores
        \pre No existe un Jugador con identificador = id_p en el conjunto de jugadores
        \post Se ha añadido un Jugador con identificador = id_p y estadísticas a 0
        al conjunto de jugadores y se ha actualizado el ranking añadiendo este Jugador
    */
    void nuevo_jugador(string& id_p);
    
    /** @brief Se elimina a un Jugador del conjunto de jugadores
        \pre Existe un Jugador con identificador = id_p en el conjunto de jugadores
        \post Se ha eliminado al Jugador con identificador = id_p del conjunto de jugadores
        y se ha actualizado el ranking eliminando al jugador del mismo
    */
    void baja_jugador(string& id_p);
    
    /** @brief Se actualiza el ranking 
        Se ordena decrecientemente por puntos del Jugador y decrecientemente
        por la posicion anterior en caso de empate a puntos
        \pre Ranking inicializado
        \post Se ha ordenado el ranking crecientemente por posición y
        decrecientemente por puntos del Jugador
    */
    void actualizar_ranking();
    
    /** @brief Se suman y se restan los juegos pertenecientes a los dos jugadores pasados como parámetro
        \pre 'a' y 'b' son dos enteros que representan dos jugadores participantes, 
        'x' y 'y' son los juegos a sumar y restar y "part" es el vector de participantes del torneo
        \post Se han sumado y restado los juegos correspondientes a los dos jugadores
    */
    void sumar_restar_juegos(int a, int b, int x, int y, const vector<Jugador>& part);
    
    /** @brief Se suman y se restan los sets a los dos jugadores pasados como parámetro
        \pre 'a' y 'b' son dos enteros que representan dos jugadores participantes
        y "part" es el vector de participantes del Torneo
        \post Se han sumado y restado los sets correspondientes a los dos jugadores
    */
    void sumar_restar_set(int a, int b, const vector<Jugador>& part);
    
    /** @brief Se suman y se restan los partidos a los dos jugadores pasados como parámetro
        \pre 'a' y 'b' son dos enteros que representan dos jugadores participantes
        y "part" es el vector de participantes del torneo
        \post Se han sumado y restado los partidos correspondientes a los dos jugadores
    */
    void sumar_restar_partido(int a, int b, const vector<Jugador>& part);
    
    /** @brief Se suman y se restan los puntos pertenecientes a los dos jugadores pasados como parámetro
        \pre 'a' es un enteros que representa un jugador participante, "cat" es la Categoria a la que pertenece el Torneo, 
        "nivel" es el nivel para sumar los puntos correspondientes y "part" es el vector de participantes del Torneo
        \post Se han sumado los puntos pertenecientes al nivel pasado como parámetro al Jugador 'a'
    */
    void sumar_puntos(Categoria& cat, int nivel, int a, vector<Jugador>& part);
    
    /** @brief Se restan los puntos pertenecientes al Jugador con identificador "id_p"
        \pre "id_p" es un string que representa el identificador del Jugador, y "pt" los puntos que se le deben restar
        \post Se han sumado los puntos pertenecientes al nivel pasado como parámetro al Jugador 'a'
    */
    void restar(string& id_p, int pt);
    
    
    // Consultores
    
    /** @brief Operacion de consulta
        \pre <em>Cierto</em>
        \post El resultado indica si existe un Jugador con id = id_p en el 
        conjunto de jugadores
    */
    bool existe_jugador(string& id_p);
    
    /** @brief Operacion de consulta del numero de jugadores del conjunto
        \pre <em>Cierto</em>
        \post El resultado es el numero de jugadores del conjunto 
    */
    int numero_jugadores() const;
    
    /** @brief Operacion de consulta de un Jugador
        \pre Existe un Jugador con identificador id_p en el circuito
        \post Se ha devuelto el Jugador con identificador id_p
    */
    Jugador consultar_jugador(string& id_p);
    
    /** @brief Se consulta cuál es el Jugador con posición x del ranking
        \pre x >= 1 y x <= num. de jugadores
        \post El resultado es un Jugador que está en la posición x del ranking
    */
    Jugador consultar_jugador_rank(int x) const;
    

    // Lectura y escritura
    
    /** @brief Operacion de lectura
        Se leen los jugadores del conjunto de jugadores y se inicializa el ranking
        \pre Conjunto de jugadores no vacío
        \post Para cada Jugador del conjunto, se ha leído un string, se ha inicializado al 
        Jugador con ese string como identificador y sus estadísticas a 0, y el ranking con cada
        Jugador en la posición en la que se ha leído
    */
    void leer_jugadores();
    
    /** @brief Operacion de escritura
        Se lista el ranking por orden creciente de posición escribiendo el nombre y los
        puntos de cada Jugador
        \pre Ranking inicializado
        \post Se ha escrito a través del canal estándar de salida el nombre y los puntos de
        cada Jugador ordenado crecientemente por su posición en el ranking
    */
    void listar_ranking() const;
    
    /** @brief Se listan todos los jugadores del conjunto de jugadores
        \pre <em>Cierto</em>
        \post Para cada jugador del conjunto y por orden creciente de nombre, 
        se ha escrito a través del canal estándar de salida su nombre, posición 
        en el ranking, puntos, y el resto de estadísticas del jugador en el circuito
    */
    void listar_jugadores();
};
#endif
