#!/bin/bash
# Script de compilation de la simulation d'evacuation
# Groupe Lafon Monzein

SCRIPT_PATH="$(cd "$(dirname "$0")" && pwd)"

# Main
gcc "$SCRIPT_PATH"/src/main.c "$SCRIPT_PATH"/src/positions.c "$SCRIPT_PATH"/src/utils.c "$SCRIPT_PATH"/src/thread.c -lm -lpthread -o "$SCRIPT_PATH"/bin/crowd.out

