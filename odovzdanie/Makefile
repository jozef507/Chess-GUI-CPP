# Makefile 
# ICP projekt 2019 - ¿achy
# Autor: Jan Holásek (xholas09)

build:
	(cd src/; qmake -o Makefile chess.pro; make)

run: 
	./src/chess

doxygen:
	(cd doc; doxygen Doxyfile)

clean:
	(cd src; make clean; rm .qmake.stash Makefile chess)
	(cd doc; rm -r html)
	rm chess.core

pack:
	zip xondri05-xholas09.zip -r src/ examples/ doc/ README.txt Makefile
