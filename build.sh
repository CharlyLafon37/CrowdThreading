#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc main.c -lSDL2 -lSDL2main -o crow

# Tests
gcc -Wall -std=gnu99 -g -o testUtils utils.c testUtils.c

