EXE=osd-tool

CPPFLAGS=-Wall -std=c++11

SRC=command.cpp exit_command.cpp help_command.cpp program.cpp

all: $(EXE)

clean:
	rm $(EXE) *.o

$(EXE): $(SRC:%.cpp=%.o)
	$(CC) -o $@ -lstdc++ -lreadline $+
	cp $@ ../../
