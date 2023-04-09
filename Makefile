NAME = DataVisual
NAME2 = main2
CXX = g++
SOURCEDIR = source
OBJDIR = obj
INCLUDEDIR = graphics/include
HEADERDIR = source/header
BINDIR = bin
FLAGS = graphics/lib -lsfml-graphics -lsfml-window -lsfml-system
# SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
LIST = main data_visualization support_function button state inputbox node triplecolor struct_ds ds_staticarray ds_dynamicarray ds_linkedlist ds_stack ds_queue arrow
LIST2 = main2 support_function node triplecolor struct_ds ds_linkedlist ds_staticarray arrow

SOURCES = $(LIST:%=$(SOURCEDIR)/%.cpp)
#   source/main.cpp source/struct.cpp source/struct_support.cpp
SOURCES2 = $(LIST2:%=$(SOURCEDIR)/%.cpp)

OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS2 = $(SOURCES2:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)

DEPS = $(OBJS:(OBJDIR)/%.o=(OBJDIR)/%.d)

all: build link run

link: ${OBJS}
	${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

build: ${OBJS}

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	${CXX} -I ${INCLUDEDIR} -I ${HEADERDIR} -c $< -o $@ -L ${SOURCEDIR}

clean:
	del obj\*.o

run:
	${NAME}.exe

test: build2 link2 run2

link2: ${OBJS2}
	${CXX} $^ -o ${NAME2}.exe -L ${FLAGS}

build2: ${OBJS2}

run2:
	$(NAME2).exe


# link2:
# 	g++.exe -LC:\SFML-2.5.1\lib -o DataVisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics -lsfml-window -lsfml-system

# link3:
# 	g++.exe -LC:\SFML-2.5.1\lib  -o Datavisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics-d -lsfml-window-d -lsfml-system-d