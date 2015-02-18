#include <iostream>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int callbackReference = 0;

int cppfunction(lua_State *L) {
    callbackReference = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

void doubleNumber(lua_State *L, int callback, int number) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
    lua_pushvalue(L, 1);
    lua_pushnumber(L, number);
    if (lua_pcall(L, 1, 1, 0)) {
        std::cerr << "Something went wrong calling the function" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
    }
    int result = lua_tonumber(L, -1);
    lua_pop(L, 1); // The result
    lua_pop(L, 1); // The callback reference
    std::cerr << "Doubling number: " << number << " gives " << result << std::endl;
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

    std::cerr << "Callback Reference: " << callbackReference << std::endl;
    doubleNumber(L, callbackReference, 2);
    doubleNumber(L, callbackReference, 4);
    lua_close(L);
    return 0;
}
