#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

# Main
gcc main.c positions.c utils.c thread.c -lm -lpthread -o crow.out

