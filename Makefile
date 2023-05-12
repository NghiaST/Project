NAME = DataVisual
CXX = g++
SOURCEDIR = source
OBJDIR = obj
INCLUDEDIR = graphics/include
HEADERDIR = source/header
BINDIR = bin
FLAGS = graphics/lib -lsfml-graphics -lsfml-window -lsfml-system
# SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
LIST = main data_visualization support_function button state inputbox node elementcolor struct_ds ds_staticarray ds_dynamicarray ds_simplylinkedlist ds_doublylinkedlist ds_circularlinkedlist ds_stack ds_queue arrow style manipulate_animation themes StateCategory settings buttonspeed buttonstep sStaticArray sDynamicArray sSinglyLinkedList sDoublyLinkedList sCircularLinkedList sStack sQueue sNode

SOURCES = $(LIST:%=$(SOURCEDIR)/%.cpp)
#   source/main.cpp source/struct.cpp source/struct_support.cpp

OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)

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