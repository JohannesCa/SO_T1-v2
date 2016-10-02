all:
	g++ *.cpp -std=c++11 -pthread -O3 -g3 -Wall -o so-t1

clean:
	rm so-t1
