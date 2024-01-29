CC = g++
# CCFLAGS = -Wall -Wextra -std=c++2a -g -O3 -flto -fprofile-use
CCFLAGS = -Wall -Wextra -Wpedantic -pedantic-errors -Wno-unused-variable -Wno-unused-parameter -std=c++2b -g -O0 -fmax-errors=1 -Wfatal-errors -D_GLIBCXX_DEBUG -fsanitize=address -fsanitize=undefined
HH = $(wildcard *.h)
# SRC = $(wildcard *.cc)
NORM = Student.cc form.cc
CSL = Student.cc consolidator.cc
BRK = Student.cc brackets.cc
RND = Student.cc generate_rand_teams.cc
OBJ1 = $(NORM:%.cc=%.o)
OBJ2 = $(CSL:%.cc=%.o)
OBJ3 = $(BRK:%.cc=%.o)
OBJ4 = $(RND:%.cc=%.o)

form: $(OBJ1)
	$(CC) $(CCFLAGS) $^ -o form

consolidate: $(OBJ2)
	$(CC) $(CCFLAGS) $^ -o consolidate

bracket: $(OBJ3)
	$(CC) $(CCFLAGS) $^ -o bracket

generate-team: $(OBJ4)
	$(CC) $(CCFLAGS) $^ -o generate-team

%.o: %.cc $(HH)
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f form consolidate bracket generate-team *.o
