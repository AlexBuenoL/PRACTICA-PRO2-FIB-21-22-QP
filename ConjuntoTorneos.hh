/** @file ConjuntoTorneos.hh
    @brief Especificación de la clase ConjuntoTorneos
*/

#ifndef CONJUNTO_TORNEOS_HH
#define CONJUNTO_TORNEOS_HH

#include "Torneo.hh"

/** @class ConjuntoTorneos
    @brief Representa un conjunto de torneos.
    Conjunto de torneos ordenados crecientemente por nombre. 
    Se puede modificar añadiendo o eliminando torneos, consultar si existe 
    un determinado torneo o consultar el número de elementos del conjunto.
*/
class ConjuntoTorneos {
    
private:

    /** @brief map de <em>Torneo</em> que representa el conjunto de torneos y contiene todos los del circuito */
    map<string, Torneo> map_tor;
    
    int ntor;
    

public:
    
    // Constructores
    
    /** @brief Creador por defecto
        Se genera un conjunto de torneos automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es un conjunto de torneos no inicializado
    */
    ConjuntoTorneos();
    
    /** @brief Creador inicializado
        Se genera un conjunto de torneos inicializado con un número de torneos
        \pre <em>Cierto</em>
        \post El resultado es un conjunto de torneos con t numero de torneos
    */
    ConjuntoTorneos(int t);
    
    
    // Modificadores
    
    /** @brief Se añade un Torneo con identificador y categoría al conjunto
        \pre No existe un Torneo con identificador id
        \post El resultado es el conjunto de los torneos anteriores y el añadido 
        con identificador id y de Categoria cat
    */
    void nuevo_torneo(string& id, Categoria& cat);
    
    /** @brief Se elimina un Torneo con identificador id del conjunto de torneos
        \pre Existe un torneo con identificador id
        \post El resultado es el conjunto de torneos sin el Torneo con identificador id
    */
    void baja_torneo(string& id);
    
    /** @brief Se asigna el cuadro de emparejamientos y los participantes al <em>Torneo</em> requerido
        \pre "id_to" es un string que representa el nombre de un Torneo, "arb" es el cuadro de emparejamientos de este Torneo 
        y 'r' es el vector de participantes
        \post Se ha asignado el cuadro de emparejamientos y el vector de participantes al <em>Torneo</em> 
        con identificador "id_to"
    */
    void definir_cuadro_y_participantes(string& id_to, const BinTree<int>& arb, const vector<Jugador>& r);
    
    /** @brief Se asignan los participantes de la última edición al Torneo requerido
        \pre "id_to" es un string que representa el nombre de un torneo y "torn" contiene el vector de participantes 
        \post Se ha asignado al Torneo "torn" el vector de participantes de la última edición
    */
    void definir_ult_jugadores(string& id_to, Torneo& torn);

    
    // Consultores
    
    /** @brief Consultor que indica si existe el Torneo dentro del conjunto de torneos
        \pre <em>Cierto</em>
        \post El resultado indica si existe un Torneo con identificador id dentro 
        del conjunto de torneos
    */
    bool existe_torneo(string& id);
    
    /** @brief Consultor del número de toneos total del conjunto
        \pre <em>Cierto</em>
        \post El resultado es el número de torneos del conjunto de torneos
    */
    int numero_torneos() const;
    
    /** @brief Devuelve el Torneo con identificador id_to
        \pre Existe un Torneo en el conjunto con identificador id_to
        \post El resultado es el torneo del conjunto con identificador id_to
    */
    Torneo consultar_torneo(string& id_to);
    
    
    // Lectura y escritura
    
    /** @brief Operación de lectura de los torneos del conjunto de torneos
        \pre <em>Cierto</em>
        \post Se han leído los torneos del conjunto de torneos asignando un string 
        como identificador y un entero que representa la Categoria a la que pertenece.
    */
    void leer_torneos(map<int, Categoria>& map_cat);
    
    /** @brief Operación de escritura de los torneos del conjunto de torneos
        \pre <em>Cierto</em>
        \post Se han escrito a través del canal estándar de salida el identificador 
        y la Categoria de los torneos del conjunto crecientemente (a partir del nombre)
    */
    void listar_torneos();
};
#endif
