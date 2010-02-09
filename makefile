CC=g++
LD=g++
TARGET=a.exe
SOURCES = Delaunay.cpp dBManager.cpp dEdge.cpp dTriangle.cpp delaunayManager.cpp main.cpp alg.cpp ../../tinylog/src/tinyLog.cpp
OBJECTS := $(SOURCES:%.cpp=%.o)
INCL=-I../alg/ -I../../exception -I../../tinylog/src
LIB=-L. -ltinylog
CFLAGS=-c -g -Os -fno-rtti -Wall
LFLAGS=
APPLIBS=

all: $(TARGET)

#  Make target
$(TARGET): $(OBJECTS) $(APPLIBS)
	$(LD) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(APPLIBS) $(SYSLIBS) tinylog.a

#  Make objects
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCL)

#  Clean
.PHONY : clean
clean :
	-rm $(TARGET) $(OBJECTS)
