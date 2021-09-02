#!/bin/bash
gcc -o add_template.so add_template.c $(yed --print-cflags) $(yed --print-ldflags)

if [ ! -d ~/.yed/templates ]
then
    mkdir ~/.yed/templates
fi
