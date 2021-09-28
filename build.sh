#!/bin/bash
gcc -o add_template.so add_template.c $(yed --print-cflags) $(yed --print-ldflags)

mkdir -p $(yed --print-config-dir)/templates ]
