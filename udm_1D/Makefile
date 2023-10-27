CC=g++
CFLAGS=-Wall -Werror -lm
LDFLAGS=
# Check the operating system
ifeq ($(OS),Windows_NT)
     # For Windows
    SRCS=main.cpp ..\myinclude\data_writer.cpp ..\myinclude\graph.cpp ..\myinclude\init.cpp ..\myinclude\sleepMilliseconds.cpp ..\myinclude\transf.cpp udm1D.cpp
    clean_cmd = del $(OBJS) $(EXEC)* src\*.dat
else
     # For Linux
    SRCS=main.cpp ../myinclude/data_writer.cpp ../myinclude/graph.cpp ../myinclude/init.cpp ../myinclude/sleepMilliseconds.cpp ../myinclude/transf.cpp udm1D.cpp
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