all: main.cpp universe.o galaxy.o planet.o address.o space_ship_gallery.o model_not_found.o space_ship.o user.o driver.o trip.o passenger.o date_time.o admin.o taxiare.o server_socket.o server.o	tools.o
	g++ main.cpp reading_file_err.o universe.o galaxy.o planet.o address.o space_ship_gallery.o model_not_found.o space_ship.o user.o driver.o trip.o passenger.o date_time.o admin.o taxiare.o server_socket.o server.o tools.o -o server

address.o: address.h address.cpp universe.o bad_address.h 
	g++ -c address.cpp -o address.o

planet.o: planet.h planet.cpp
	g++ -c planet.cpp -o planet.o

galaxy.o: galaxy.h galaxy.cpp planet.o
	g++ -c galaxy.cpp -o galaxy.o

universe.o: universe.h universe.cpp galaxy.o reading_file_err.o
	g++ -c universe.cpp -o universe.o

reading_file_err.o: reading_file_err.h reading_file_err.cpp
	g++ -c reading_file_err.cpp -o reading_file_err.o

space_ship_gallery.o: space_ship_gallery.h space_ship_gallery.cpp reading_file_err.o
		g++ -c space_ship_gallery.cpp -o space_ship_gallery.o

model_not_found.o: model_not_found.h model_not_found.cpp
	g++ -c model_not_found.cpp -o model_not_found.o

space_ship.o: space_ship.h space_ship.cpp space_ship_gallery.o model_not_found.o
	g++ -c space_ship.cpp -o space_ship.o

date_time.o: date_time.h date_time.cpp
	g++ -c date_time.cpp -o date_time.o
user.o: user.h user.cpp
	g++ -c user.cpp -o user.o

driver.o: driver.h driver.cpp space_ship.o address.o user.o space_ship.o
	g++ -c driver.cpp -o driver.o

trip.o: trip.h trip.cpp driver.o address.o passenger.o date_time.o
	g++ -c trip.cpp -o trip.o

passenger.o: passenger.h passenger.cpp user.o date_time.o
	g++ -c passenger.cpp -o passenger.o

taxiare.o: taxiare.h taxiare.cpp date_time.o passenger.o driver.o date_time.o
	g++ -c taxiare.cpp -o taxiare.o

admin.o: admin.h admin.cpp user.o
	g++ -c admin.cpp -o admin.o

server.o: server.cpp server.h
	g++ -c server.cpp
	
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp

clean:
	rm -f *.o server
