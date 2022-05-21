all: main

main: Run_multiple_tests.o Table.o Cuckoo.o
	@echo "Combining files..."
	g++ -g Run_multiple_tests.cpp Table.cpp Cuckoo.cpp -o main -lcrypto -lssl

Run_multiple_tests.o: Run_multiple_tests.cpp
	@echo "Creating main program..."
	g++ -g -o Run_multiple_tests.o -c Run_multiple_tests.cpp

Table.o: Table.cpp
	@echo "Creating Table module..."
	g++ -g -o Table.o -c Table.cpp

Cuckoo.o: Cuckoo.cpp
	@echo "Creating Cukoo module..."
	g++ -g -o Cuckoo.o -c Cuckoo.cpp
