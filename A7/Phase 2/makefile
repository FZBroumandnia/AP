CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 

all: utaxi.out
	./utaxi.out locations.csv < 4.in

utaxi.out: main.o File_handler.o Exception_handler.o Person.o Trip.o Command_token.o Iohandler.o UTaxi.o Location.o
	$(CC) main.o File_handler.o Exception_handler.o Person.o Trip.o Command_token.o Iohandler.o UTaxi.o Location.o $(FLAGS) -o utaxi.out

main.o: main.cpp UTaxi.hpp
	$(CC) $(COMPILE_FLAGS) main.cpp

UTaxi.o: UTaxi.cpp UTaxi.hpp File_handler.hpp Location.hpp Consts.hpp Passenger_driver.hpp Exception_handler.hpp Person.hpp Trip.hpp Command_token.hpp Iohandler.hpp
	$(CC) $(COMPILE_FLAGS) UTaxi.cpp

File_handler.o: File_handler.cpp File_handler.hpp Location.hpp Consts.hpp
	$(CC) $(COMPILE_FLAGS) File_handler.cpp

Exception_handler.o: Exception_handler.cpp Exception_handler.hpp Consts.hpp
	$(CC) $(COMPILE_FLAGS) Exception_handler.cpp

Person.o: Person.cpp Person.hpp Consts.hpp
	$(CC) $(COMPILE_FLAGS) Person.cpp

Trip.o: Trip.cpp Trip.hpp Person.hpp Location.hpp Consts.hpp
	$(CC) $(COMPILE_FLAGS) Trip.cpp

Command_token.o: Command_token.cpp Command_token.hpp
	$(CC) $(COMPILE_FLAGS) Command_token.cpp

Iohandler.o: Iohandler.cpp Iohandler.hpp Command_token.hpp Consts.hpp
	$(CC) $(COMPILE_FLAGS) Iohandler.cpp

Location.o: Location.cpp Location.hpp
	$(CC) $(COMPILE_FLAGS) Location.cpp	

.PHONY: clean

clean:
	rm *.o