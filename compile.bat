@echo off

echo =====================================
echo Compilation du projet NomDuProjet
echo =====================================

REM Assurez-vous que CMake est disponible dans le PATH
cmake --version > nul 2>&1
if %errorlevel% neq 0 (
  echo Erreur : CMake n'est pas installé ou n'est pas dans le PATH.
  exit /b 1
)

REM Créez un répertoire de construction (s'il n'existe pas déjà)
if not exist build mkdir build

REM Accédez au répertoire de construction
cd build

REM Configurez le projet avec CMake
cmake ..

REM Compilez le projet avec Make
make

REM Vérifiez si la compilation a réussi
if %errorlevel% neq 0 (
  echo Erreur : La compilation a échoué.
  exit /b 1
)

windeployqt --no-translations .

echo =====================================
echo Compilation réussie, exécutable dans le dossier build
echo =====================================

exit /b 0