# Nom de l'exécutable
TARGET = cat_cat

# Compilateur
CC = gcc

# Fichiers source
SRCS = main.c event.c font.c game.c place.c player.c objects.c list.c

# Fichiers objets (automatiquement dérivés des sources)
OBJS = $(SRCS:.c=.o)

# Flags de compilation
CFLAGS = -Wall -Wextra -g `sdl2-config --cflags`

# Librairies à l’édition de liens
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm -lSDL2_ttf

# Règle par défaut
all: $(TARGET)

# Édition de liens
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
