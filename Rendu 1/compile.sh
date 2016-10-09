#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc src/main.c src/positions.c src/utils.c src/thread.c -lm -lpthread -o bin/crowd.out

