NAME        =   calm_spirit

COMPILER    =   $(CXX)
CFLAGS      =   -Wall -Wextra -Werror -std=c++1y -O3 -c
LFLAGS      =   -o

SRC         =   main.cpp

OBJ_DIR     =   objs
OBJ         =   $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $^ $(LFLAGS) $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.cpp
	$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)
	rm -df $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
