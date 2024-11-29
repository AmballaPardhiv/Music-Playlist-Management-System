CC = gcc
CFLAGS = -Wall -std=c99

SRC = main.c songs_library.c playlists.c login.c utility.c

OBJ = $(SRC:.c=.o)

OUTPUT = music_manager

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUTPUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
