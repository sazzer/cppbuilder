#include <iostream>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int cppfunction(lua_State *L) {
    lua_getfield(L, -1, "integer");
    std::cerr << "Integer: " << lua_tonumber(L, -1) << std::endl;
    lua_pop(L, 1);

    lua_getfield(L, -1, "string");
    std::cerr << "String: " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1);

    return 0;
}

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "cppfunction", cppfunction);

    if (luaL_dofile(L, "./script.lua")) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}
