# Tools installieren

git
g++-Compiler - Version 5.4.0
cppcheck
make
dot (graphviz)
evince - Viewer für ps-Dateien
pkg-config

# Kompilierung

1. Neuen Ordner anlegen
2. Alle Quelltext-Dateien in den Ordner kopieren
3. Dateien kompilieren mit G++

g++ -std=c++11 -I . main.cpp feature.cpp dependency.cpp analyzer.cpp utils/log.cpp dependencies/mandatory.cpp dependencies/optional.cpp dependencies/or.cpp dependencies/xor.cpp -o main

# Ausführung

./main ausführen
