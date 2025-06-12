all: main.cpp universe.o galaxy.o planet.o address.o space_ship_gallery.o model_not_found.o space_ship.o user.o driver.o trip.o passenger.o date_time.o admin.o server.o 
	clang++ main.cpp reading_file_err.o universe.o galaxy.o planet.o address.o space_ship_gallery.o model_not_found.o space_ship.o user.o driver.o trip.o passenger.o date_time.o admin.o server.o -o run.out

address.o: address.h address.cpp universe.o bad_address.h 
	clang++ -c address.cpp -o address.o

planet.o: planet.h planet.cpp
	clang++ -c planet.cpp -o planet.o

galaxy.o: galaxy.h galaxy.cpp planet.o
	clang++ -c galaxy.cpp -o galaxy.o

universe.o: universe.h universe.cpp galaxy.o reading_file_err.o
	clang++ -c universe.cpp -o universe.o

reading_file_err.o: reading_file_err.h reading_file_err.cpp
	clang++ -c reading_file_err.cpp -o reading_file_err.o

space_ship_gallery.o: space_ship_gallery.h space_ship_gallery.cpp reading_file_err.o
		clang++ -c space_ship_gallery.cpp -o space_ship_gallery.o

model_not_found.o: model_not_found.h model_not_found.cpp
	clang++ -c model_not_found.cpp -o model_not_found.o

space_ship.o: space_ship.h space_ship.cpp space_ship_gallery.o model_not_found.o
	clang++ -c space_ship.cpp -o space_ship.o

date_time.o: date_time.h date_time.cpp
	clang++ -c date_time.cpp -o date_time.o
user.o: user.h user.cpp
	clang++ -c user.cpp -o user.o

driver.o: driver.h driver.cpp space_ship.o address.o user.o space_ship.o
	clang++ -c driver.cpp -o driver.o

trip.o: trip.h trip.cpp driver.o address.o passenger.o date_time.o
	clang++ -c trip.cpp -o trip.o

passenger.o: passenger.h passenger.cpp user.o date_time.o
	clang++ -c passenger.cpp -o passenger.o

server.o: server.h server.cpp date_time.o passenger.o driver.o date_time.o
	clang++ -c server.cpp -o server.o
admin.o: admin.h admin.cpp user.o
	clang++ -c admin.cpp -o admin.o
clean:
	rm -f  *o run.out