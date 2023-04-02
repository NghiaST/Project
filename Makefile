NAME = DataVisual
CXX = g++
SOURCEDIR = source
OBJDIR = obj
INCLUDEDIR = graphics/include
BINDIR = bin
FLAGS = graphics/lib -lsfml-graphics -lsfml-window -lsfml-system
# SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
LIST = main graphics_func struct_support structure
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
	${CXX} -I ${INCLUDEDIR} -c $< -o $@ -L ${SOURCEDIR}

clean:
	@echo sorry, I can't

run:
	${NAME}.exe



link2:
	g++.exe -LC:\SFML-2.5.1\lib -o DataVisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics -lsfml-window -lsfml-system

link3:
	g++.exe -LC:\SFML-2.5.1\lib -o Datavisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics-d -lsfml-window-d -lsfml-system-d