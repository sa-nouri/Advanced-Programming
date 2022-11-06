all : main.cpp invalid_initial_value.h invalid_digit_assignment.h big_num.o fractional.o integral.o
	clang++ main.cpp big_num.o integral.o fractional.o -o run.out

big_num.o: big_num.cpp big_num.h invalid_initial_value.h fractional.o integral.o
	clang++ -c big_num.cpp -o big_num.o

fractional.o: fractional.cpp fractional.h invalid_initial_value.h invalid_digit_assignment.h
	clang++ -c fractional.cpp -o fractional.o

integral.o: integral.cpp integral.h invalid_initial_value.h invalid_digit_assignment.h
	clang++ -c integral.cpp -o integral.o
clean:
	rm *.o run.out
