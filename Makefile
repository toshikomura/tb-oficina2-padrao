install:
	gcc -c segmenta.c 
	gcc -c segmenta2.c
	gcc -c leitura.c
	gcc -c gera_saida.c
	gcc -o segmenta segmenta.o segmenta2.o leitura.o gera_saida.o
	cp ./segmenta ../bin/

tudo: install

limpa:
	rm -f *~*
	rm -f *.bak
	rm -f core*
	rm -f ../bin/*~*
	rm -f ../bin/*.bak
	rm -f ../bin/core*
	
faxina: limpa
	rm -f segmenta
	rm -f *.o
	rm -f ../bin/segmenta
