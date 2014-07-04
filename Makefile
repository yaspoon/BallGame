OBJS= Main.o BallGame.o Player.o Level.o Block.o Entity.o Timer.o VisualEntity.o
CFILES= Main.cpp BallGame.cpp PLayer.cpp Level.cpp Block.cpp Entity.cpp Timer.cpp VisualEntity.cpp
HFILES=BallGame.h PLayer.h Level.h Block.h Entity.h bgCommon.h Timer.h VisualEntity.h
EXE=
CURRDIR=$(shell pwd)
BUILDDIR=$(CURRDIR)/BUILD
OBJDIR=$(BUILDDIR)/OBJ


CC=g++

TARGETS=BallGame$(EXE)

CFLAGS = -g -Wall -pedantic `sdl-config --cflags`
LIBS = `sdl-config --libs` -lGL -lSDL_image -lm -Xlinker "-R ./libs"

$(shell [ -d "$(OBJDIR)" ] || mkdir -p $(OBJDIR))
$(shell cp -R $(CURRDIR)/images $(BUILDDIR) )

#WINDOWS FLAGS#
#CFLAGS = -g -Wall -pedantic `sdl-config --cflags`
#LIBS = `sdl-config --libs` -lopengl32 -lSDL_image -Xlinker "-R ./libs" -L/usr/include

default: ALL
Debug: ALL

BUILD: ALL

ALL: $(TARGETS)

BallGame$(EXE): $(OBJS)
	$(CC) -o $(BUILDDIR)/$(TARGETS) $(OBJDIR)/* $(CFLAGS) $(LIBS)

Main.o: Main.cpp
	$(CC) -c Main.cpp -o $(OBJDIR)/Main.o $(CFLAGS) $(LIBS)

BallGame.o: BallGame.cpp BallGame.h
	$(CC) -c BallGame.cpp -o $(OBJDIR)/BallGame.o $(CFLAGS) $(LIBS)

Player.o: Player.cpp Player.h
	$(CC) -c Player.cpp -o $(OBJDIR)/Player.o $(CFLAGS) $(LIBS)

Level.o: Level.cpp Level.h
	$(CC) -c Level.cpp -o $(OBJDIR)/Level.o $(CFLAGS) $(LIBS)

Block.o: Block.cpp Block.h
	$(CC) -c Block.cpp -o $(OBJDIR)/Block.o $(CFLAGS) $(LIBS)

Entity.o: Entity.cpp Entity.h
	$(CC) -c Entity.cpp -o $(OBJDIR)/Entity.o $(CFLAGS) $(LIBS)

VisualEntity.o: VisualEntity.cpp VisualEntity.h
	$(CC) -c VisualEntity.cpp -o $(OBJDIR)/VisualEntity.o $(CFLAGS) $(LIBS)

Timer.o: Timer.cpp Timer.h
	$(CC) -c Timer.cpp -o $(OBJDIR)/Timer.o $(CFLAGS) $(LIBS)

cleanBUILD: clean

cleanDEBUG: clean

clean:
	@echo "Cleaning"
	rm -rf $(BUILDDIR)/$(TARGETS) $(BUILDDIR)
