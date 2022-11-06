all: passenger

passenger: main.cpp client_socket.o tools.o passenger_client.o
	g++ main.cpp client_socket.o tools.o passenger_client.o -o passenger
	
client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
	
passenger_client.o: passenger_client.h passenger_client.cpp
	g++ -c passenger_client.cpp

clean:
	rm *.o passenger
