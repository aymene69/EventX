#!/bin/bash

echo "====================================="
echo "Compilation d'EventX"
echo "====================================="
mkdir qt5
cd qt5
mv ../qt5.tar .
tar xvf qt5.tar
cd ..
export PATH="$PWD/qt5/bin/CMake.app/Contents/bin/:$PWD/qt5/bin/:$PATH"

command -v cmake > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "Erreur : CMake n'est pas installé."
  exit 1
fi

mkdir -p build

cd build

cmake ..

make

rm -r EventX.app

mkdir EventX.app
mkdir EventX.app/Contents
mkdir EventX.app/Contents/MacOS
mkdir EventX.app/Contents/Resources

cp EventX EventX.app/Contents/MacOS/EventX
cp ../assets/macos/Info.plist EventX.app/Contents/Info.plist
cp ../assets/macos/EventX.icns EventX.app/Contents/Resources/EventX.icns

macdeployqt EventX.app
mv EventX.app ..
rm -r *
mv ../EventX.app .
if [ $? -ne 0 ]; then
  echo "Erreur : La compilation a échoué."
  exit 1
fi

echo "====================================="
echo "Compilation réussie, application .app dans le dossier build"
echo "====================================="

exit 0

