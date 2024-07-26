SRC=./6/*.c ./include/*.c ./main.c #./4/*.c ./5/*.c
INC=-I./include/

target:
	gcc -g -std=gnu99 $(SRC) $(INC) -o a.out

clean:
	rm a.out
