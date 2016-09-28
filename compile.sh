#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc main.c -lSDL2 -lSDL2main -o crow.out

# Tests
gcc -o testUtils.out utils.c testUtils.c

