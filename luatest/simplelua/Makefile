luatest: luatest.cpp
	${CXX} luatest.cpp -o luatest `pkg-config --cflags --libs lua5.2`

test: luatest
	./luatest

clean:
	rm -f luatest
