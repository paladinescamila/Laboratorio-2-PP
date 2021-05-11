proof:
	echo $1

compile:
	gcc -o $(FILE).out -fopenmp $(FILE).c

compile_pg:
	gcc -o $(FILE).out -fopenmp $(FILE).c -pg

compile_gprof:
	gprof $(FILE).out gmon.out > analysis_$(FILE).txt

run:
	./$(FILE).out

remove:
	rm *.out analysis_*.txt