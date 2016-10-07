#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc main.c positions.c utils.c thread.c -lSDL2 -lSDL2main -lm -lpthread -o bin/crow.out

# Tests
#gcc -o bin/testUtils.out utils.c testUtils.c positions.c -lSDL2 -lSDL2main

