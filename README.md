# Lexical Analyzer

A lexical analyzer is the first step of the compiling process. It identifies the tokens of the language of the source file and provides it to the syntactic analyser which will be soon available.

This project was made as the first assignment of the Compilers and Computer Theory discipline ministred in the first semester of 2019 at the University of São Paulo Campus São Carlos.

This project was originally developed by:
* Augusto Ribeiro (https://github.com/GuttinRibeiro)
* Bruno Arantes (https://github.com/brunoaamello)
* Henrique Andrews (https://github.com/AndrewsHPM)
* Henry Suzukawa (https://github.com/HSuzu)
* Tiago Toledo Jr (https://github.com/TNanukem)

## Description and Objectives

The objective of this project is to develop a Lexical Analyzer capable of identifying the tokens of the LALG (also known as simplified PASCAL) languagem. It's grammar is available at the (info/LALG_Grammar.pdf). The for command is not explicit in the grammar, however it was considered into our implementation.

The original description and requisites of this project is available, in portuguese at (info/Assignment1.pdf).

This was proposed so we can apply the initial concepts we've been theoretically developing in our classes with the concepts of Compilers, Finite Automatas and Grammars.

## Running the analyzer

In order to run the analyzer, you have to compile the files. There is a Makefile available, so everything you have to do is to run make and then execute the out file.

However, if you want to manually compile the files, you should use the following sequence of instructions:

~~~~
lex analyzer.l
cc lex.yy.c src/radix_tree.c src/entry.c -ll -o out
./out
~~~~

Then, you can either assign a file to the output or insert it manually on the command line.
