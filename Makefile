kmp= gcc -Wall -Wextra -Werror -std=c11
all:Quest_3
Quest_3: data_io.o data_stat.o data_process.o main_executable_module.o decision.o
	mkdir -p ../../build
	$(kmp)  data_process.o decision.o main_executable_module.o data_io.o data_stat.o -o ../../build/Quest_3
main_executable_module.o: main_executable_module.c
	$(kmp) -c main_executable_module.c
decision.o: ../yet_another_decision_module/decision.c
	$(kmp) -c ../yet_another_decision_module/decision.c
data_process.o:../data_module/data_process.c 
	$(kmp) -c ../data_module/data_process.c
data_io.o: ../data_libs/data_io.c
	$(kmp) -c ../data_libs/data_io.c
data_stat.o: ../data_libs/data_stat.c
	$(kmp) -c ../data_libs/data_stat.c
clean:
	rm -rf *.o Quest_3 ../../build