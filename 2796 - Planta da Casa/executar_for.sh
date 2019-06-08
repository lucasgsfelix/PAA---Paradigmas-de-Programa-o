#!/bin/bash
for file in Gerador/Entradas/*
do
	./casa < $file
done
