NAME        =   calm_spirit

SRC         =   main.cpp

OBJ_DIR     =   objs
OBJ         =   $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

PCH         =   stdafx.hpp
PCH_SUFFIX  =   .gch
PCH_DIR     =   $(OBJ_DIR)/pch
PCH_TARGET  =   $(PCH_DIR)$(PCH_SUFFIX)/pch
PCH_FLAG    =   -include $(PCH_DIR)

COMPILER    =   $(CXX)
CFLAGS      =   -Wall -Wextra -Werror -std=c++1y -O3 -c
LFLAGS      =   -o

all: $(NAME)

$(NAME): $(PCH_TARGET) $(OBJ)
	$(COMPILER) $(OBJ) $(LFLAGS) $@

$(PCH_TARGET): $(PCH)
	mkdir -p $(PCH_DIR)$(PCH_SUFFIX)
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.cpp
	$(COMPILER) $(CFLAGS) $(PCH_FLAG) $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
