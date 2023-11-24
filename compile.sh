#!/bin/bash

echo "====================================="
echo "Compilation d'EventX"
echo "====================================="

command -v cmake > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "Erreur : CMake n'est pas installé."
  exit 1
fi

mkdir -p build

cd build

cmake ..

make

if [ $? -ne 0 ]; then
  echo "Erreur : La compilation a échoué."
  exit 1
fi

echo "====================================="
echo "Compilation réussie, exécutable dans le dossier build"
echo "====================================="

exit 0

