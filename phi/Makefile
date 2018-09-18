CXX = icpc
CXXFLAGS =	-std=c++11 -g -O3 -fopenmp -I$/src -I$/include -vec-

OBJS =		ECHARM_phi_plain.o

LIBS = -L/opt/intel/composerxe/lib/intel64/ -I/opt/intel/mkl/include -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -liomp5 -ldl -lpthread

TARGET =	ECHARM_phi_plain

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
