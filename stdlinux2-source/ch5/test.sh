#!/bin/bash

assert() {
    expected="$1"
    input="$2"

    gcc -o cat cat.c
    # ./cat input.txt input1.txt input2.txt
    # expected="$1"
    # input="$2"

    # ./k8cc <(echo "$input") > tmp.s
    # gcc -static -o tmp tmp.s tmp2.o
    # ./tmp
    # actual="$?"

    # if [ "$actual" = "$expected" ]; then
    #   echo "$input => $actual"
    # else
    #   echo "$input => $expected, but got $actual"
    #   exit 1
    # fi
}

assert 0 input.txt
