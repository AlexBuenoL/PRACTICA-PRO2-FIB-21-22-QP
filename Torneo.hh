/** @file Torneo.hh
    @brief Especificación de la clase Torneo
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "ConjuntoJugadores.hh"

#ifndef NO_DIAGRAM 
#include "BinTree.hh"
#include "ParInt.hh"
#endif

/** @class Torneo
    @brief Representa un torneo.
    Se identifica con un string y pertenece a una <em>Categoria</em>.
    Contiene un <em>BinTree</em> que representa el cuadro de emparejamientos al inicio del Torneo,
    un vector de jugadores que contiene los participantes de la edición actual del Torneo, y
    otro de la última.
*/
class Torneo {
    
private:

    string id;
    Categoria cat;
    
    /** @brief Es un <em>BinTree</em> (arbol) de enteros que representa el cuadro de 
        emparejamientos del Torneo */
    BinTree<int> cuadro_emp; 

    /** @brief Vector de <em>Jugador</em> que contiene los participantes de la edición actual del Torneo */
    vector<Jugador> jug_edicion_actual;

    /** @brief Vector de <em>Jugador</em> que contiene los participantes de la última edición del Torneo */
    vector<Jugador> jug_ult_edicion;

    /** @brief Función privada que convierte un string que representa el resultado de un partido
        en un vector de sets, donde cada set es un <em>ParInt</em> con el resultado del set 
        \pre <em>Cierto</em>
        \post El resultado es un vector de <em>ParInt</em> con los resultados de los sets
        en forma de enteros
    */
    static vector<ParInt> conv(const string& res);

    /** @brief Función privada que devuelve el ganador de un partido entre dos jugadores
        \pre 'a' y 'b' son dos enteros que representan a dos jugadores dentro del torneo, y "res" es
        un string que representa el resultado de partido
        \post El resultado es un entero que representa al jugador que resulta ganador del partido
    */
    static int match(int a, int b, const string& res);

    
public:
    
    // Constructores
    
    /** @brief Creador por defecto.
        Se genera un Torneo automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es un Torneo no inicializado
    */
    Torneo();
    
    /** @brief Creador inicializado.
        Se genera automáticamente un Torneo inicializado con su identificador
        \pre <em>Cierto</em>
        \post El resultado es un Torneo con id = id_to
    */
    Torneo(string& id_to);
    
    /** @brief Creador inicializado.
        Se genera automáticamente un Torneo inicializado con su identificador
        y perteneciente a la Categoria indicada
        \pre <em>Cierto</em>
        \post El resultado es un Torneo con id = id_to y Categoria = cat
    */
    Torneo(string& id_to, Categoria& ca);
    
    
    // Modificadores
    
    /** @brief Confecciona y define el cuadro de emparejamientos del Torneo
        \pre 'arb' es un árbol vacío, 'h' es la altura que tendrá el árbol, 
        'l' representa el nivel que en la primera llamada es 1, 'a' representa el ganador 
        y también debe ser 1. Y 'x' es el valor de los jugadores que no tendrán hijos
        en caso de que el último nivel del árbol sea incompleto
        \post Se ha definido el cuadro de emparejamientos del Torneo 
    */
    void definir_emparejamientos(BinTree<int>& arb, int h, int l, int a, int x);

    /** @brief Se asigna al parámetro implícito el cuadro de emparejamientos 
        y el vector de participantes del Torneo
        \pre "arb" es un arbol de enteros que contiene el cuadro de emparejamientos y r es
        un vector de jugadores con los participantes del Torneo
        \post Se ha asignado al Torneo el cuadro de emparejamientos y el vector de participantes
        de la edición actual
    */
    void asignar_cuadro_emp_participantes(const BinTree<int>& arb, const vector<Jugador>& r);
    
    /** @brief Se construye un árbol con los resultados del Torneo
        \pre 'a' es un árbol vacío, el cuadro de emparejamientos está definido correcamente y 'res' es un árbol de strings
        con los resultados de los partidos
        \post 'a' es ahora un árbol con los resultados del Torneo ya disputado
    */
   void proc_resultados(BinTree<int>& a, const BinTree<int>& emp, const BinTree<string>& res);
   
    /** @brief Actualiza las estadísticas de los dos jugadores 
        que disputan el partido a partir del resultado del mismo
        \pre 'a' y 'b' son dos enteros que representan a dos jugadores que se enfrentan en un partido
        y 'res' es un string con el resultado de este partido
        \post Se han actualizado las estadísticas pertenecientes a los dos jugadores que han participado en el Torneo
    */
    void act_stats(int a, int b, const string& res, ConjuntoJugadores& jugadores, int nivel);
    
    /** @brief Actualiza las estadísticas de los jugadores participantes en el Torneo
        \pre 'a' es el árbol de enteros que representa los resultados y 
        'res' el árbol de strings con los resultados de los partidos
        \post Se han actualizado las estadísticas pertenecientes a cada jugador que ha participado en el Torneo
    */
    void actualizar_estadisticas(const BinTree<int>& a, const BinTree<string>& res, int nivel, ConjuntoJugadores& jugadores);
    
    /** @brief Resta los puntos de cada jugador de la última edición del Torneo
        \pre <em>Cierto</em>
        \post Se han restado los puntos de cada jugador de la última edición del Torneo
    */
    void restar_puntos(ConjuntoJugadores& jugadores);
    
    /** @brief Se asigna al Torneo el vector con los jugadores de la última edición
        \pre "last" es el vector de los participantes de esta edición del torneo
        \post Se ha asignado/actualizado el vector de jugadores de la última edición del Torneo
    */
    void ult_jugadores(vector<Jugador>& last);
    
    
    // Consultores
    
    /** @brief Consultora del cuadro de emparejamientos del Torneo
        \pre Cuadro de emparejamientos del torneo definido correctamente
        \post Se ha devuelto un árbol de enteros que representa el cuadro de emparejamientos del Torneo
    */
    BinTree<int> consultar_cuadro() const;
    
    /** @brief Consultora de los participantes del Torneo
        \pre Vector de participantes del torneo definido correctamente
        \post Se ha devuelto el vector de participantes del Torneo
    */
    vector<Jugador> consultar_participantes() const;
    
    
    // Lectura y escritura

    /** @brief Operación de lectura
        \pre Hay preparados en el canal estándar de entrada una serie de enteros que 
        representan las posiciones del ranking de los jugadores participantes
        \post Se han leído los jugadores que participan en el Torneo y se han almacenado en el vector 'r'
    */
    void leer_participantes(vector<Jugador>& r, ConjuntoJugadores& jugadores);

    /** @brief Operación de lectura
        \pre Hay preparados en el canal estándar de entrada una serie de strings que 
        representan los resultados de los partidos del Torneo leídos en preorden
        \post 'a' es un arbol de strings con los resultados de los partidos del Torneo
    */
    static void leer_resultados(BinTree<string>& a);
    
    /** @brief Operación de escritura
        \pre 'a' cuadro de emparejamientos definido correcamente y 'v' contiene los participantes del Torneo
        \post Se ha escrito a través del canal estándar de salida el cuadro de emparejamientos
    */
    void imprimir_emparejamientos(const BinTree<int> &a, const vector<Jugador>& v) const;
    
    /** @brief Operación de escritura
        Se escribe el cuadro de resultados del Torneo
        \pre 'res' es un BinTree con los resultados del Torneo
        \post Se ha escrito el cuadro de resultados del Torneo
    */
    void imprimir_resultados(const BinTree<int>& a, const BinTree<string>& res) const;
    
    /** @brief Operación de escritura
        Se listan los puntos ganados por cada jugador en la última edición del Torneo
        \pre <em>Cierto</em>
        \post Se ha escrito a través del canal estándar de salida los puntos ganados por cada 
        jugador en la última edición del Torneo de los jugadores con una puntuación conseguida 
        diferente de 0
    */
    void listar_puntos() const;
    
    /** @brief Operación de escritura
        \pre <em>Cierto</em>
        \post Se ha escrito a través del canal estándar de salida el nombre y la categoria a la que pertenece el Torneo
    */
    void listar_torneo() const;
};
#endif

