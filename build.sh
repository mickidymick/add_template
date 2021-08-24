#!/bin/bash
gcc $(yed --print-cflags) $(yed --print-ldflags) -o add_template.so -g add_template.c

if [ ! -d ~/.yed/templates ]
then
    mkdir ~/.yed/templates
fi
