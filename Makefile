OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Categoria.o Jugador.o Torneo.o ConjuntoJugadores.o ConjuntoTorneos.o ParInt.o
	g++ -o program.exe program.o Categoria.o Jugador.o Torneo.o ConjuntoJugadores.o ConjuntoTorneos.o ParInt.o
	rm *.o

program.o: program.cc Categoria.hh Jugador.hh Torneo.hh ConjuntoJugadores.hh ConjuntoTorneos.hh ParInt.hh
	g++ -c program.cc $(OPCIONS)

ConjuntoTorneos.o: ConjuntoTorneos.cc ConjuntoTorneos.hh Torneo.hh
	g++ -c ConjuntoTorneos.cc $(OPCIONS)

ConjuntoJugadores.o: ConjuntoJugadores.cc ConjuntoJugadores.hh Jugador.hh Categoria.hh
	g++ -c ConjuntoJugadores.cc $(OPCIONS)
	
Torneo.o: Torneo.cc Torneo.hh Categoria.hh Jugador.hh BinTree.hh ConjuntoJugadores.hh ParInt.hh
	g++ -c Torneo.cc $(OPCIONS)

ParInt.o: ParInt.cc ParInt.hh 
	g++ -c ParInt.cc $(OPCIONS)
        
Jugador.o: Jugador.cc Jugador.hh
	g++ -c Jugador.cc $(OPCIONS)
	
Categoria.o: Categoria.cc Categoria.hh
	g++ -c Categoria.cc $(OPCIONS)

clean:
	rm *.exe
	rm *.gch
	rm *.o
