CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
PROGRAMS := q1_cafeteria_order_system q2_shopping_cart q3_student_scores q4_bank_account_system
BINS     := $(addprefix build/,$(PROGRAMS))

all: $(BINS)

build/%: src/%.cpp src/input_utils.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $<

test:
	bash tests/run_tests.sh

clean:
	rm -rf build *.txt.bak

.PHONY: all test clean
