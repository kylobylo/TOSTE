#!/bin/sh bash

g++ -c Main.cpp tileRenderer.cpp userInterface.cpp Button.cpp -DLINUX
g++ Main.o tileRenderer.o userInterface.o Button.o -o TOSTE -lsfml-system -lsfml-graphics -lsfml-window -DLINUX
