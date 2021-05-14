proof:
	echo $1

compile:
	mpicc -o $(FILE) $(FILE).c

compile_pg:
	mpicc -o $(FILE) $(FILE).c -pg

compile_gprof:
	gprof $(FILE) gmon.out > analysis_$(FILE).txt

run:
	mpiexec -n $(NP) ./$(FILE)

remove:
	rm *.out analysis_*.txt