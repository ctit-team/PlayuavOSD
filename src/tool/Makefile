EXE=osd-tool

CPPFLAGS=-Wall -std=c++14
LDLIBS=-lboost_filesystem -lboost_system -lreadline

SRC=command.cpp \
	command_argument.cpp \
	device_properties.cpp \
	exit_command.cpp \
	file_descriptor.cpp \
	file_system.cpp \
	flash_command.cpp \
	help_command.cpp \
	info_command.cpp \
	osd_bootloader_connection.cpp \
	osd_command.cpp \
	osd_connection.cpp \
	osd_info_request.cpp \
	program.cpp \
	serial_connection.cpp \
	set_command.cpp \
	string.cpp \
	variable.cpp

all: $(EXE)

clean:
	-@rm $(EXE) *.o 2> /dev/null

$(EXE): $(SRC:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LDLIBS) -o $@ $+
	cp $@ ../../
