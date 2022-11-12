CXX=clang++
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec
tests: bin/tests

bin/exec: ./src/MotionPicture.cpp ./src/Recommendation.cpp ./src/driver.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@

bin/tests: ./test/test.cpp ./src/Recommendation.cpp ./src/MotionPicture.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
	rm -rf bin/*