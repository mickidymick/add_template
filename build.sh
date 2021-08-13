#!/bin/bash
gcc -g -shared -fPIC -lyed add_template.c -o add_template.so

if [ ! -d ~/.yed/templates ]
then
    mkdir ~/.yed/templates
fi
