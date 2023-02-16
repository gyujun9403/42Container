

TARGET = ft_container
CPP = c++
FLAGS = -std=c++98 -Wall -Wextra -Werror
DIR = ./
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDE = container

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR), $(OBJS))
	$(CPP) $(FLAGS) -o $(TARGET) -I $(INCLUDE) $^
%.o : %.cpp
	$(CPP) $(FLAGS) -o $@ -c $<
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(TARGET)
re :
	make fclean
	make all
.PHONY : all clean fclean re