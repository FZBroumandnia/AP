CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utaxi.out
	./utaxi.out backend/locations.csv

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: cpp/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp backend/UTaxi.hpp backend/Exception_handler.hpp backend/Consts.hpp backend/Trip.hpp
	$(CC) $(CF) -c cpp/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: cpp/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c cpp/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: cpp/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp backend/UTaxi.hpp
	$(CC) $(CF) -c cpp/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/UTaxi.o: backend/UTaxi.cpp backend/UTaxi.hpp backend/File_handler.hpp backend/Location.hpp backend/Consts.hpp backend/Passenger_driver.hpp backend/Exception_handler.hpp backend/Person.hpp backend/Trip.hpp 
	$(CC) $(CF) -c backend/UTaxi.cpp -o $(BUILD_DIR)/UTaxi.o

$(BUILD_DIR)/Location.o: backend/Location.cpp backend/Location.hpp 
	$(CC) $(CF) -c backend/Location.cpp -o $(BUILD_DIR)/Location.o

$(BUILD_DIR)/Exception_handler.o: backend/Exception_handler.cpp backend/Exception_handler.hpp backend/Consts.hpp
	$(CC) $(CF) -c backend/Exception_handler.cpp -o $(BUILD_DIR)/Exception_handler.o

$(BUILD_DIR)/File_handler.o: backend/File_handler.cpp backend/File_handler.hpp backend/Consts.hpp backend/Location.hpp
	$(CC) $(CF) -c backend/File_handler.cpp -o $(BUILD_DIR)/File_handler.o

$(BUILD_DIR)/Person.o: backend/Person.cpp backend/Person.hpp backend/Consts.hpp
	$(CC) $(CF) -c backend/Person.cpp -o $(BUILD_DIR)/Person.o

$(BUILD_DIR)/Trip.o: backend/Trip.cpp backend/Trip.hpp backend/Consts.hpp backend/Location.hpp backend/Person.hpp
	$(CC) $(CF) -c backend/Trip.cpp -o $(BUILD_DIR)/Trip.o

utaxi.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/UTaxi.o $(BUILD_DIR)/Exception_handler.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/File_handler.o $(BUILD_DIR)/Location.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/UTaxi.o $(BUILD_DIR)/Exception_handler.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Trip.o $(BUILD_DIR)/File_handler.o $(BUILD_DIR)/Location.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o utaxi.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
