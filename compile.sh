#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc main.c positions.c utils.c -lSDL2 -lSDL2main -lm -o crow.out

# Tests
gcc -o testUtils.out utils.c testUtils.c -lSDL2 -lSDL2main

