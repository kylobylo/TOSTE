#!/bin/sh bash

g++ -c Main.cpp tileRenderer.cpp userInterface.cpp Button.cpp
g++ Main.o tileRenderer.o userInterface.o Button.o -o TOSTE -lsfml-system -lsfml-graphics -lsfml-window
