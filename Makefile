APP = out/slm
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,out/%.o,$(SRCS))

all: $(APP)

out:
	mkdir -p out

out/%.o: src/%.cpp | out
	clang++ -c -O2 -o $@ $<

$(APP): $(OBJS)
	clang++ -o $@ $^

clean:
	rm -f out/* 