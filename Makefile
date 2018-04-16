all:testpublish testrecv

testpublish:
	g++ --std=c++11 -o testpublish testpublish.cpp -lmosquittopp

testrecv:
	g++ --std=c++11 -o testrecv testrecv.cpp -lmosquittopp
	
clean:
	rm -rf testpublish testrecv
