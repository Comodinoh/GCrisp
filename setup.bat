@echo off
IF NOT EXIST .\out\ mkdir .\out\

cmake -S . -B .\out\
