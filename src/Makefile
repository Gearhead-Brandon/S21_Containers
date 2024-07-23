#GCC = g++-11
GCC = gcc
CPPFLAGS = -std=c++20 -lstdc++ -Wall -Werror -Wextra -lm

REPORT = REPORT.html

CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS  = -fprofile-arcs -ftest-coverage
GLFLAGS    = --coverage
GTEST      = -lgtest

TEST_FLAGS = $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) $(GTEST)

YELLOW=\033[0;33m
NC=\033[0m

TEST_SOURCES=$(wildcard unit_tests/*.cpp)
#TEST_SOURCES=$(wildcard unit_tests/list_tests.cpp)
TEST_TARGETS=$(TEST_SOURCES:unit_tests/%.cpp=%)

DIRS = ./S21_Containers ./S21_ContainersPlus

EXCLUDE_FILES = "unit_tests/*" "S21_Containers/Deque/*"
EXCLUDE_REPORT = $(foreach file, $(EXCLUDE_FILES), --exclude $(file)) 

##################################__ALL

all: test

##################################__TESTS

test: $(TEST_TARGETS)
	make start_tests

%: unit_tests/%.cpp
	$(GCC) $< $(TEST_FLAGS) $(CPPFLAGS)  -o $@

start_tests:
	@for test in $(TEST_TARGETS); do \
		echo "\n$(YELLOW)$$test$(NC)\n"; \
		./$$test; \
	done
##################################__VALGRIND_TEST_CHECK

val:
	make test_valgrind

test_valgrind: $(TEST_TARGETS)
	make start_tests_valgrind

start_tests_valgrind:
	@for test in $(TEST_TARGETS); do \
		echo "\n$(YELLOW)$$test$(NC)\n"; \
		valgrind --tool=memcheck --leak-check=yes ./$$test; \
    done
	@echo "$(NC)"

##################################__GCOV REPORT

gcov_report: test
	~/.local/bin/gcovr -r . $(EXCLUDE_REPORT) --html --html-details -o $(REPORT)
	@make move_report
	@rm -rf Trash

peer: gcov_report
	@open Report/$(REPORT)

##################################__MV_REPORT

move_report:
	@rm -rf Report && mkdir Report && mv *.html *.css Report
	
##################################__CLEAN

clean:
	@find . -type f \( ! -path "./unit_tests/*" \) \( -name "*.gcno" \
	-o -name "*.gcda" -o -name "*.gcov" -o -name "*test*" \
	-o -name "*.html" -o -name "*.css" \) -exec rm -f {} \;
	rm -rf Report Trash

##################################__REBUILD

rebuild:
	make clean
	make