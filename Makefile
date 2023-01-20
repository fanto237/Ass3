CC		= g++
CFLAGS		= -std=c++17 -Wall -Wextra -Weffc++ -pedantic -Wfatal-errors -fPIE
C_DEBUG_FLAGS	= -g
RM		= /bin/rm -f
EXEC_NAME	= AUSGABE
SOURCES		= $(wildcard *.cpp)
OBJECTS		= $(SOURCES:.cpp=.o)

default: $(EXEC_NAME)

$(EXEC_NAME): $(OBJECTS)
	$(CC) -o $(EXEC_NAME) $(OBJECTS) && ./HowTo.sh
%.o: %.cpp
	$(CC) $(C_DEBUG_FLAGS) $(CFLAGS) -MMD -c $<

-include $(SOURCES:.cpp=.d)

clean:
	$(RM) $(EXEC_NAME) *.d *.o
