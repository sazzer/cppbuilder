#include <iostream>
#include <algorithm>
#include <string>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int index(lua_State* L) {
    std::string key = lua_tostring(L, 2);
    std::cout << "Called __index: " << key << std::endl;

    std::transform(key.begin(), key.end(),key.begin(), ::toupper);
    lua_pushstring(L, key.c_str());
    return 1;
}

int newindex(lua_State* L) {
    std::string key = lua_tostring(L, 2);
    std::string value = lua_tostring(L, 3);
    std::cout << "Called __newindex: " << key << " = " << value << std::endl;
    return 0;
}

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);
    
    lua_newtable(L);
    lua_pushcfunction(L, index);
    lua_setfield(L, -2, "__index");

    lua_pushcfunction(L, newindex);
    lua_setfield(L, -2, "__newindex");

    lua_setmetatable(L, -2);

    lua_setglobal(L, "mt");

    if (luaL_dofile(L, "./script.lua")) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}
