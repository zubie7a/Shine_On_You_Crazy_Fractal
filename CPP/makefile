#!/bin/bash
BIN_DIR=$(CURDIR)/bin
BIN_NAME=run
SRC_DIR=$(CURDIR)/src
MAIN=main.cpp
CPP_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system


.PHONY : build clean

build : ${BIN_DIR}/${BIN_NAME}


${BIN_DIR} : 
	mkdir -p $@

${BIN_DIR}/${BIN_NAME} : ${SRC_DIR}/${MAIN} ${BIN_DIR}
	g++ $< -o $@ ${CPP_FLAGS}

clean :
	rm -fr ${BIN_DIR}
