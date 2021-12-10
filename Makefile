CXX=g++
CXXFLAGS=-std=c++14 -Werror=vla -g -Wall -MMD
OBJECTS=bishop.o board.o graphobserver.o human.o king.o knight.o level1.o level2.o level3.o main.o pawn.o piece.o queen.o rook.o strategy.o subject.o textobserver.o window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=final

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}