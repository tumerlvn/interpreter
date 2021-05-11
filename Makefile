DEL_DIR       = rmdir
FLAGS	      = -c -I./include -fsanitize=address,leak
all: bin bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main 
bin:
	mkdir bin
bin/const.o: src/const.cpp
	$(CXX) $? -o $@ $(FLAGS)
bin/lexem.o: src/lexem.cpp
	$(CXX) $? -o $@ $(FLAGS)
bin/lexical.o: src/lexical.cpp
	$(CXX) $? -o $@ $(FLAGS)
bin/syntax.o: src/syntax.cpp
	$(CXX) $? -o $@ $(FLAGS)
bin/semantic.o: src/semantic.cpp
	$(CXX) $? -o $@ $(FLAGS)

bin/main: src/main.cpp bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o
	$(CXX) $? -o $@ -I./include -fsanitize=address,leak

clean:
	rm bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main
	$(DEL_DIR) bin
