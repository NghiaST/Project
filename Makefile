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
LIST = main data_visualization support_function button state inputbox node triplecolor struct_ds ds_staticarray ds_dynamicarray ds_linkedlist ds_stack ds_queue arrow style
LIST2 = main2 data_visualization support_function button state inputbox node triplecolor struct_ds ds_staticarray ds_dynamicarray ds_linkedlist ds_stack ds_queue arrow style

SOURCES = $(LIST:%=$(SOURCEDIR)/%.cpp)
#   source/main.cpp source/struct.cpp source/struct_support.cpp
SOURCES2 = $(LIST2:%=$(SOURCEDIR)/%.cpp)

OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS2 = $(SOURCES2:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)

OBJDEL = $(wildcard $(OBJDIR)/*.o)
DEPS = $(OBJS:(OBJDIR)/%.o=(OBJDIR)/%.d)

VERBOSE = FALSE
ifeq (${VERBOSE}, TRUE)
	HIDE = 
else
	HIDE = @
endif

all: dir build run

dir:
ifeq ($(wildcard $(OBJDIR)),)
	${HIDE} echo create folder "${OBJDIR}"
	${HIDE} mkdir ${OBJDIR}
endif

build: ${OBJS}
	${HIDE} echo linking .o file to -*_*- ${NAME}.exe
	${HIDE} ${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
# $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
# ${OBJDIR/%.o=%.cpp}
	${HIDE} echo compile $*.o
	${HIDE} ${CXX} -I ${INCLUDEDIR} -I ${HEADERDIR} -c $< -o $@ -L ${SOURCEDIR}

clean:
ifeq (${OBJDEL},)
	${HIDE} echo delete nothing
else
	${HIDE} echo delete files
	${HIDE} del obj\*.o
endif

run:
	${HIDE} echo ${NAME}.exe
	${HIDE} ${NAME}.exe

rebuild: clean all

test: dir build2 run2

build2: ${OBJS2}
	${HIDE} echo linking .o file to --- ${NAME2}.exe
	${HIDE} ${CXX} $^ -o ${NAME2}.exe -L ${FLAGS}

run2:
	${HIDE} echo ${NAME2}.exe
	${HIDE} ${NAME2}.exe



# link2:
# 	g++.exe -LC:\SFML-2.5.1\lib -o DataVisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics -lsfml-window -lsfml-system

# link3:
# 	g++.exe -LC:\SFML-2.5.1\lib  -o Datavisual.exe obj/main.o obj/graphics_func.o obj/structure.o obj/struct_support.o -lsfml-graphics-d -lsfml-window-d -lsfml-system-d