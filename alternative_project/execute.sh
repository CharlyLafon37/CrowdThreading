#!/bin/bash
# Script d'exécution de la simulation d'evacuation
# Groupe Lafon Monzein

SCRIPT_PATH="$(cd "$(dirname "$0")" && pwd)"

# Main
"$SCRIPT_PATH"/bin/crowd.out -p4 -t1 -e2 -m
