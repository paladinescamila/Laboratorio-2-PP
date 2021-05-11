proof:
	echo $1

compile:
	gcc -o $(FILE).out -fopenmp $(FILE).c

remove:
	rm *.out