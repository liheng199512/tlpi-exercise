SRC=./5/*.c ./include/*.c ./main.c #./4/*.c
INC=-I./include/

target:
	gcc -g -std=gnu99 $(SRC) $(INC) -o a.out

clean:
	rm a.out
