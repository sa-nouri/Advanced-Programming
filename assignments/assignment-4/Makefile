all: code.cpp food.o includes.h order.o order_item.h customer.o restaurant.o
	g++ code.cpp food.o order.o restaurant.o customer.o -o run.out

food.o: food.cpp food.h includes.h 
	g++ -c food.cpp -o food.o

order.o: order.h order.cpp order_item.h 
	g++ -c order.cpp -o order.o

customer.o: customer.h customer.cpp restaurant.o order.o
	g++ -c customer.cpp -o customer.o

restaurant.o: restaurant.cpp restaurant.h food.o 
	g++ -c restaurant.cpp -o restaurant.o

