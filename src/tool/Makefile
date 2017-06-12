EXE=osd-tool

CPPFLAGS=-Wall -std=c++11

SRC=command.cpp \
	exit_command.cpp \
	help_command.cpp \
	program.cpp \
	variable.cpp

all: $(EXE)

clean:
	-@rm $(EXE) *.o 2> /dev/null

$(EXE): $(SRC:%.cpp=%.o)
	$(CC) -o $@ -lstdc++ -lreadline $+
	cp $@ ../../
