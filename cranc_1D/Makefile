CC=g++
LDFLAGS=
# Check the operating system
ifeq ($(OS),Windows_NT)
    # For Windows
    CFLAGS=-Wall -Werror -lm -I C:\MinGW\include\eigen3 -g -O0
    SRCS=main.cpp ..\myinclude\data_writer.cpp ..\myinclude\graph.cpp ..\myinclude\init.cpp ..\myinclude\sleepMilliseconds.cpp ..\myinclude\init_m.cpp cranc1D.cpp
    clean_cmd = del $(OBJS) $(EXEC)* src\*.dat
else
    # For Linux
    CFLAGS=-Wall -Werror -lm -I/usr/include/eigen3 -g -O0
    SRCS=main.cpp ../myinclude/data_writer.cpp ../myinclude/graph.cpp ../myinclude/init.cpp ../myinclude/sleepMilliseconds.cpp ../myinclude/init_m.cpp cranc1D.cpp
	clean_cmd = rm -f $(OBJS) $(EXEC)* src/*.dat
endif
OBJS=$(SRCS:.cpp=.o)
EXEC=test
all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@$(clean_cmd)