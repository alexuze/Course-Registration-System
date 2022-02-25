LDFLAGS:=-lboost_system -lboost_thread -pthread

# All Targets
all: bin/BGRSclient

# Tool invocations
# Executable "BGRSclient" depends on the files BGRSclient.o connectionHandler.o echoClient.o
bin/BGRSclient: bin/BGRsclient.o bin/connectionHandler.o bin/InputReader.o bin/NetworkReader.o
	@echo 'Building target: BGRSclient'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/BGRSclient bin/BGRsclient.o bin/connectionHandler.o bin/InputReader.o bin/NetworkReader.o $(LDFLAGS)
	@echo 'Finished building target: BGRSclient'
	@echo ' '

#connectionHandler.o Depends on the source and header files src/connectionHandler.cpp include/connectionHandler.h
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/connectionHandler.o src/connectionHandler.cpp $(LDFLAGS)

#echoClient.o Depends on the source and header files src/echoClient.cpp include/echoClient.h
bin/BGRsclient.o: src/BGRsclient.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BGRsclient.o src/BGRsclient.cpp

bin/InputReader.o: src/InputReader.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/InputReader.o src/InputReader.cpp

bin/NetworkReader.o: src/NetworkReader.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/NetworkReader.o src/NetworkReader.cpp

#Clean the build directory
clean:
	rm -f bin/*