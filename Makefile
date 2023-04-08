NAME = DataVisual
CXX = g++
SOURCEDIR = source
OBJDIR = obj
INCLUDEDIR = graphics/include
HEADERDIR = source/header
BINDIR = bin
FLAGS = graphics/lib -lsfml-graphics -lsfml-window -lsfml-system
# SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
LIST = main data_visual graphics_func struct_support staticarray button state inputbox statusbox node circlenode
SOURCES = $(LIST:%=$(SOURCEDIR)/%.cpp)
#   source/main.cpp source/struct.cpp source/struct_support.cpp
OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:(OBJDIR)/%.o=(OBJDIR)/%.d) 

all: build link run

test: run

link: ${OBJS}
	${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

build: ${OBJS}

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	${CXX} -I ${INCLUDEDIR} -I ${HEADERDIR} -c $< -o $@ -L ${SOURCEDIR}

clean:
	del obj\*.o

run:
	${NAME}.exe



link2:
	g++.exe -LC:\SFML-2.5.1\lib -o DataVisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics -lsfml-window -lsfml-system

link3:
	g++.exe -LC:\SFML-2.5.1\lib  -o Datavisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics-d -lsfml-window-d -lsfml-system-d