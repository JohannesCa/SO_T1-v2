all:
	g++ *.cpp -std=c++11 -pthread -O3 -g3 -Wall -o so-t1-v2

clean:
	rm so-t1-v2
