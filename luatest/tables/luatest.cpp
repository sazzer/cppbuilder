#include <iostream>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);
    
    lua_pushinteger(L, 42);
    lua_setfield(L, -2, "integer");

    lua_pushstring(L, "StringValue");
    lua_setfield(L, -2, "string");

    lua_setglobal(L, "table");


    if (luaL_dofile(L, "./script.lua")) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}
