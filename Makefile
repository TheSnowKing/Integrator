CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=-g

#all: first
all: main 

#first: first.o Integral.o Particle.o util.o Derivative.o
main: main.o Derivative.o Integral.o Particle.o ParticleList.o Simulate.o util.o


clean:
	rm -f *.o
