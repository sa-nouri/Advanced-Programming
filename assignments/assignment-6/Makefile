all : main.cpp functor.o std_out.o std_in.o neg.o mul.o add.o cond.o thread.o usual.o monolithic.o recursive.o random.o roundrobin.o priority.o schaduler.o parser.o schadulers_library.h
	clang++ main.cpp functor.o std_out.o std_in.o neg.o mul.o add.o cond.o thread.o usual.o monolithic.o recursive.o schaduler.o random.o roundrobin.o priority.o parser.o -o thread.out

functor.o: functor.cpp functor.h
	clang++ -c functor.cpp -o functor.o

std_out.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c std_out.cpp -o std_out.o

std_in.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c std_in.cpp -o std_in.o

neg.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c neg.cpp -o neg.o

mul.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c mul.cpp -o mul.o

add.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c add.cpp -o add.o

cond.o: functor.cpp functor.h early_to_do_the_job.h 
	clang++ -c cond.cpp -o cond.o

thread.o: thread.cpp thread.h functor.cpp functor.h bad_priority_value.h 
	clang++ -c thread.cpp -o thread.o

usual.o: usual.h usual.cpp thread.cpp thread.h
	clang++ -c usual.cpp -o usual.o

monolithic.o: monolithic.h monolithic.cpp thread.cpp thread.h
	clang++ -c monolithic.cpp -o monolithic.o

recursive.o: recursive.h recursive.cpp thread.cpp thread.h
	clang++ -c recursive.cpp -o recursive.o

schaduler.o: schaduler.h schaduler.cpp thread.h thread.cpp
	clang++ -c schaduler.cpp -o schaduler.o

random.o: random.h random.cpp schaduler.h schaduler.cpp
	clang++ -c random.cpp -o random.o

roundrobin.o: roundrobin.h roundrobin.cpp schaduler.h schaduler.cpp
	clang++ -c roundrobin.cpp -o roundrobin.o

priority.o: priority.h priority.cpp schaduler.h schaduler.cpp
	clang++ -c priority.cpp -o priority.o

parser.o: parser.cpp parser.h unable_to_open.h functors_library.h threads_library.h
	clang++ -c parser.cpp -o parser.o
clean:
	rm *.o thread.out
