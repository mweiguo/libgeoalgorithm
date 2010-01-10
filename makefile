CC=g++
LD=g++
TARGET=a.exe
SOURCES = Delaunay.cpp dBManager.cpp dEdge.cpp dTriangle.cpp delaunayManager.cpp main.cpp ../alg/alg.cpp ../../tinylog/src/tinyLog.cpp
#SOURCES = test.cpp
OBJECTS := $(SOURCES:%.cpp=%.o)
INCL=-I../alg/ -I../exception -I../../tinylog/src
CFLAGS=-c -Os -fno-rtti -Wall
#CFLAGS=-c $(INCL)
LFLAGS=
APPLIBS=
#SYSLIBS=-lopengl32 -lglut32 -lglu32

all: $(TARGET)

#  Make target
$(TARGET): $(OBJECTS) $(APPLIBS)
	$(LD) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(APPLIBS) $(SYSLIBS)

#  Make objects
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCL)

#  Clean
.PHONY : clean
clean :
	-rm $(TARGET) $(OBJECTS)
