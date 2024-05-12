CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 

all: main
	./main

main: main.o Document.o Book.o Magazine.o Reference.o Borrow_note.o Person.o Student.o Professor.o Library.o
	$(CC) main.o Document.o Book.o Magazine.o Reference.o Borrow_note.o Person.o Student.o Professor.o Library.o $(FLAGS) -o main

main.o: main.cc Const.hpp
	$(CC) $(COMPILE_FLAGS) main.cc

Document.o: Document.cpp Document.hpp
	$(CC) $(COMPILE_FLAGS) Document.cpp

Book.o: Book.cpp Book.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Book.cpp

Magazine.o: Magazine.cpp Magazine.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Magazine.cpp

Reference.o: Reference.cpp Reference.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Reference.cpp

Borrow_note.o: Borrow_note.cpp Borrow_note.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Borrow_note.cpp

Person.o: Person.cpp Person.hpp Borrow_note.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Person.cpp

Student.o: Student.cpp Student.hpp Person.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Student.cpp

Professor.o: Professor.cpp Professor.hpp Person.hpp Document.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Professor.cpp

Library.o: Library.cpp Library.hpp Person.hpp Document.hpp Student.hpp Professor.hpp Book.hpp Magazine.hpp Reference.hpp Borrow_note.hpp Const.hpp
	$(CC) $(COMPILE_FLAGS) Library.cpp

.PHONY: clean

clean:
	rm *.o