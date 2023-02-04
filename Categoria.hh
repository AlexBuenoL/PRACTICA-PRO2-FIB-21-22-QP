/** @file Categoria.hh
    @brief Especificación de la clase Categoria */

#ifndef CATEGORIA_HH
#define CATEGORIA_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <string>
#include <map>
#endif
using namespace std;

/** @class Categoria
    @brief Representa una categoria del circuito.
    La categoria se puede identificar con un string (name) o con un entero entre 1 y c (id),
    donde c es el numero de categorias del circuito.
    También contiene un map con un entero como clave (nivel) y un entero que representa
    los puntos pertenecientes al nivel
*/
class Categoria {
    
private:

    int id;
    string name;

    /** @brief map con un entero como clave que representa el nivel y otro entero como valor que representa
        los puntos que corresponden a este nivel dentro de esta categoría */
    map<int,int> ptos_por_nivel;
    

public:
    
    // Constructores
    
    /** @brief Creadora por defecto
        Se genera una Categoria automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es una Categoria no inicializada
    */
    Categoria();
    
    /** @brief Creadora por defecto
        Se genera una Categoria con nombre automáticamente al declararse
        \pre <em>Cierto</em>
        \post El resultado es una Categoria inicializada con un string como nombre
    */
    Categoria(string& id_cat);
    
     /** @brief Creadora por defecto
         Se genera una Categoria automáticamente al declararse con nombre
         y identificador (numero entero)
         \pre <em>Cierto</em>
         \post El resultado es una Categoria inicializada con un string como nombre
         y un entero que representa su identificador
    */
    Categoria(string& id_cat, int x);
    
    
    // Modificador
    
    /** @brief Se asignan los puntos que pertenecen a cada nivel de la Categoria
        \pre K es el número máximo de niveles de las categorías del circuito
        \post Se ha asignado a cada nivel de un torneo de esta Categoria 
        los puntos pertenecientes
    */
    void asignar_puntos(int k);
    

    // Consultor

    /** @brief Consultor del nombre de la Categoria
        \pre Categoria inicializada
        \post Se ha devuelto un string que representa el nombre de la Categoria
    */
    string consultar_nombre_categoria() const;

    /** @brief Consultor de los puntos de la Categoría en un nivel determinado
        \pre Categoria inicializada y puntos de cada nivel leídos
        \post Se han devuelto los puntos pertenecientes al nivel de la Categoria
        pasado como parámetro
    */
    int consultar_puntos(int nivel);


    // Escritura
    
    /** @brief Se lista el nombre y la tabla de puntos por niveles de la Categoria
        \pre Categoria inicializada
        \post Se ha escrito a través del canal estandar de salida el nombre y 
        la tabla de puntos por niveles de la Categoria
    */
    void listar_categoria(int k);
};
#endif
    
