CC=c++
CFLAGS= -O3 -c -g -Wall
LIBS=-g $(shell root-config --libs)
STACK = -fno-stack-protector
ROOTCFLAGS = -I. $(shell root-config --cflags)
OPENMPFLAG = -fopenmp

ECHARMFLAGS = -I$(ECHARMSYS) -I$(ECHARMSYS)/general/src -I$(ECHARMSYS)/general/include  -I$(ECHARMSYS)/particle/src -I$(ECHARMSYS)/particle/include -I$(ECHARMSYS)/particle/database/src -I$(ECHARMSYS)/particle/database/include -I$(ECHARMSYS)/kernel/src -I$(ECHARMSYS)/kernel/include

ECHARMCRYSTALFLAGS = -I$(ECHARMSYS)/crystal/src -I$(ECHARMSYS)/crystal/include -I$(ECHARMSYS)/EC/src -I$(ECHARMSYS)/EC/include -I$(ECHARMSYS)/EC/rec/src -I$(ECHARMSYS)/EC/rec/include -I$(ECHARMSYS)/EC/rec/rec_ax/src -I$(ECHARMSYS)/EC/rec/rec_ax/include -I$(ECHARMSYS)/EC/rec/rec_pl/src -I$(ECHARMSYS)/EC/rec/rec_pl/include

ECHARMPROCESSFLAGS = -I$(ECHARMSYS)/process/defect/src -I$(ECHARMSYS)/process/defect/include -I$(ECHARMSYS)/process/scattering/src -I$(ECHARMSYS)/process/scattering/include -I$(ECHARMSYS)/process/radiation/src -I$(ECHARMSYS)/process/radiation/include -I$(ECHARMSYS)/process/displacement/src -I$(ECHARMSYS)/process/displacement/include -I$(ECHARMSYS)/process/undulator/src -I$(ECHARMSYS)/process/undulator/include -I$(ECHARMSYS)/process/bethe_bloch/src -I$(ECHARMSYS)/process/bethe_bloch/include  -I$(ECHARMSYS)/process/torsion/src -I$(ECHARMSYS)/process/torsion/include

ECHARMDATABASEFLAGS = -I$(ECHARMSYS)/database/atoms/src -I$(ECHARMSYS)/database/atoms/include -I$(ECHARMSYS)/database/beams/src -I$(ECHARMSYS)/database/beams/include -I$(ECHARMSYS)/database/crystals/src -I$(ECHARMSYS)/database/crystals/include -I$(ECHARMSYS)/database/lattices/src -I$(ECHARMSYS)/database/lattices/include -I$(ECHARMSYS)/database/miller/src -I$(ECHARMSYS)/database/miller/include -I$(ECHARMSYS)/database/strips/src -I$(ECHARMSYS)/database/strips/include


all: main

main: main.o
	$(CC) main.o -g $(STACK) $(OPENMPFLAG) $(ECHARMFLAGS) $(ECHARMCRYSTALFLAGS) $(ECHARMPROCESSFLAGS) $(ECHARMDATABASEFLAGS) -o main $(LIBS)
main.o: main.c
	$(CC) $(CFLAGS) $(ROOTCFLAGS) $(OPENMPFLAG) $(ECHARMFLAGS) $(ECHARMCRYSTALFLAGS) $(ECHARMPROCESSFLAGS) $(ECHARMDATABASEFLAGS) main.c

clean:
	rm -rf *o main
