.PHONY: all clean build install uninstall tests gcov_report lcov_report
SHELL  = /bin/bash
OS     = $(shell uname)
CC     = gcc
CXX    = g++ -ggdb
STD	   = -std=c++17
CFLAGS = -Wall -Werror -Wextra
GTEST_LIB = -lgtest
RM     = rm -rf

ifeq ($(OS), Linux)
	GTEST_LIB += -lpthread
endif

all: build

build:
	mkdir -p build && cd build && qmake6 .. && make

install: build
	mkdir -p ~/Applications ; cp -r build/A-Maze-ing.app ~/Applications/A-Maze-ing.app

uninstall:
	rm -rf ~/Applications/A-Maze-ing.app

dvi:
	open -a safari README.md

ARCHIVE_DIR = A-Maze-ing
ARCHIVE     = $(ARCHIVE_DIR).tar

dist: $(ARCHIVE)

$(ARCHIVE):
	mkdir -p $(ARCHIVE_DIR)
	cp -r model $(ARCHIVE_DIR)
	cp -r view $(ARCHIVE_DIR)
	cp -r controller $(ARCHIVE_DIR)
	cp -r test_sources $(ARCHIVE_DIR)
	cp -r data_samples $(ARCHIVE_DIR)
	cp -r assets $(ARCHIVE_DIR)
	cp -r Makefile $(ARCHIVE_DIR)
	cp -r Dockerfile $(ARCHIVE_DIR)
	tar cf $(ARCHIVE) $(ARCHIVE_DIR)
	rm -r $(ARCHIVE_DIR)


VPATH += test_sources/

TEST_OUT = test.out
tests: $(TEST_OUT)
	./$(TEST_OUT)

GCOV_COMPILE_FLAGS  = -fprofile-arcs -ftest-coverage
GCOV_RESULT	= *.gcda *.gcno *.gcov
GCOV 			  = gcov
# GCOV_FLAGS  = -kjr

tests.o: tests.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@

maze_reader_writer_tests.o: maze_reader_writer_tests.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/file_reader -Imodel/file_writer -Imodel/field

cave_reader_writer_tests.o: cave_reader_writer_tests.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/file_reader -Imodel/file_writer -Imodel/field

maze_tests.o: maze_tests.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/field

cave_tests.o: cave_tests.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/field

cave.o: model/field/cave.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/field

maze.o: model/field/maze.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/field

%file_reader.o: model/file_reader/%file_reader.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/file_reader -Imodel/file_writer -Imodel/field

%file_writer.o: model/file_writer/%file_writer.cc
	$(CXX) $(STD) -c $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ -o $@ -Imodel/field

$(TEST_OUT): cave.o maze.o cave_file_reader.o maze_file_reader.o cave_file_writer.o maze_file_writer.o tests.o cave_reader_writer_tests.o maze_reader_writer_tests.o maze_tests.o cave_tests.o
	$(CXX) $(STD) $(CFLAGS) $(GCOV_COMPILE_FLAGS) $^ $(GTEST_LIB) -o $@

gcov_report: clean_gcov $(TEST_OUT)
	./$(TEST_OUT)
	$(GCOV) $(GCOV_FLAGS) cave.cc maze.cc cave_file_reader.cc maze_file_reader.cc cave_file_writer.cc maze_file_writer.cc

clean_gcov:
	$(RM) $(GCOV_RESULT)

LCOV          = lcov
LCOV_FLAGS    = --no-external -c -d .
COVERAGE_INFO = coverage.info

$(COVERAGE_INFO): $(TEST_OUT)
	./$(TEST_OUT)
	$(LCOV) $(LCOV_FLAGS) -o $(COVERAGE_INFO)

LCOV_REPORT_DIR = report
GENHTML         = genhtml

$(LCOV_REPORT_DIR): $(COVERAGE_INFO)
	$(GENHTML) $^ -o $(LCOV_REPORT_DIR)

lcov_report: $(LCOV_REPORT_DIR)

clang:
	find {model,test_sources,view,controller} -name "*.cc" -o -name "*.h"\
		| xargs clang-format -n --style=Google

SUPPRESSING = --suppress=unusedStructMember

cppcheck:
	find {model,test_sources,view} -name "*.cc" -o -name "*.h"\
		| xargs cppcheck --enable=all --language=c++ $(SUPPRESSING)

clean: clean_gcov
	$(RM) build*
	$(RM) report
	$(RM) *.info
	$(RM) *.o
	$(RM) *.out