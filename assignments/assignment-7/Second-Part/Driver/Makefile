all: driver

driver: main.cpp client_socket.o tools.o driver_client.o
	g++ main.cpp client_socket.o tools.o driver_client.o -o driver
	
client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
	
driver_client.o: driver_client.h driver_client.cpp
	g++ -c driver_client.cpp

clean:
	rm *.o driver
