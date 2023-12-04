@echo off

echo =====================================
echo Compilation du projet EventX
echo =====================================

cmake --version > nul 2>&1
if %errorlevel% neq 0 (
  echo Erreur : CMake n'est pas installé ou n'est pas dans le PATH.
  exit /b 1
)

if not exist build mkdir build

cd build

cmake -G "MinGW Makefiles" ..

cmake --build .

if %errorlevel% neq 0 (
  echo Erreur : La compilation a échoué.
  exit /b 1
)

mkdir EventX
move "EventX.exe" "EventX"
cd EventX

echo =====================================
echo Compilation réussie, exécutable dans le dossier build
echo =====================================

exit /b 0