#!/bin/bash

rm main
g++ main.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework ForceFeedback -lz -lm -lpthread -ldl -D_DEFAULT_SOURCE -Os --std=c++17

./main
rm main
