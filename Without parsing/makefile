P = Calculator
L = c
C = gcc

ifeq ($(L), c)
	C = gcc
else ifeq ($(L), cpp)
	C = g++
endif

# Define phony target for cleaning
.PHONY: clean
.PHONY: build
.PHONY: debug
.PHONY: run
.PHONY: all

# Build target with different options based on TYPE
build-$(P): $(P).$(L)
	$(C) -o output/$(P) $(P).$(L) -Wall

build:
	$(C) -o output/$(P) $(P).$(L) -Wall

debug:
	$(C) -g -o output/$(P) $(P).$(L) -Wall

run:
	output/$(P)
clean:
	rm -rf output/*

all:
	$(C) -o output/$(P) $(P).$(L) -Wall && output/$(P) && rm -rf output/*