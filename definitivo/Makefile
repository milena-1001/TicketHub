CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

NAME = programa

SRCS = main.cpp Plataforma.cpp Usuario.cpp Localizacion.cpp Evento.cpp \
       Administrador.cpp Artista.cpp Asistente.cpp AsistenteNormal.cpp AsistenteVip.cpp

OBJ_FILES = $(SRCS:.cpp=.o)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
