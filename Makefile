NAME = DataVisual
CXX = g++
SOURCEDIR = source
OBJDIR = obj
INCLUDEDIR = graphics/include
BINDIR = bin
FLAGS = graphics/lib -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:(OBJDIR)/%.o=(OBJDIR)/%.d) 

all: build link run

test: run

link: ${OBJS}
	${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

build: ${OBJS}

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	${CXX} -I ${INCLUDEDIR} -c $< -o $@

clean:
	del *.o
	del ${OBJS}

run:
	${NAME}.exe