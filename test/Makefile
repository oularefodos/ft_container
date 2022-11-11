NAME= container

SRCS= main.cpp vector-test.cpp map-test.cpp
HPP= ../src/Vector/Vector.hpp ../src/Iterator/Iterator_node.hpp ../src/Iterator/Vector_iterator.hpp  ../src/Vector/Vector.hpp \
../src/Iterator/Iterator_traits.hpp  ../src/Iterator/reverse_iterator.hpp ../src/RedBlackTree/Red_black_tree.hpp \
../src/Set/set.hpp ../src/Utils/utils.hpp ../src/Iterator/RBT_iterator.hpp ../src/Map/map.hpp index.hpp 

CFLAGS= -Wall -Wextra -Werror -std=c++98

OBJS :=$(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $^ -o $@

%.o: %.cpp $(HPP)
	c++ $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all