MAIN   = src/main.cpp
SRCS   = $(filter-out $(MAIN),$(wildcard src/*.cpp))
OBJS   = $(SRCS:src/%.cpp=obj/%.o)
UNITY  = test/unity.c
CFLAGS = -g -I src/
EXEC   = map-test
.PHONY: clean test all

all: $(SRCS) $(EXEC)

$(EXEC): $(OBJS) $(MAIN)
	g++ $(CFLAGS) $(OBJS) $(MAIN) -o $@

obj/%.o: src/%.cpp src/%.hpp obj
	g++ -c $(CFLAGS) $< -o $@

obj:
	mkdir -p obj

%test:
	g++ -I ../src/ ${CFLAGS} ${SRCS} ${UNITY} test/$@.cpp -o test-runner
	./test-runner

clean:
	rm -rf $(EXEC) obj test/test-runner.cpp test-runner
