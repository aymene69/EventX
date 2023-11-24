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

mkdir EventX.app
mkdir EventX.app/Contents
mkdir EventX.app/Contents/MacOS

cp EventX EventX.app/Contents/MacOS/EventX

if [ $? -ne 0 ]; then
  echo "Erreur : La compilation a échoué."
  exit 1
fi

echo "====================================="
echo "Compilation réussie, application dans le dossier build"
echo "====================================="

exit 0

