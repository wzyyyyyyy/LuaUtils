#include "pch.h"
#include <iostream>
#include <fstream>
#include <filesystem>

int readAllText(lua_State* L) {
	auto file = lua_tostring(L, 2);
	std::ifstream ifs(file);
	if (!ifs.is_open()) {
		lua_pushnil(L);
		return 1;
	}
	string v{ (std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>() };
	lua_pushstring(L, v.c_str());
	ifs.close();
	return 1;
}

int writeAllText(lua_State* L) {
	auto file = lua_tostring(L, 2);
	auto text = lua_tostring(L, 3);
	std::ofstream f(file, std::ios::out);
	f << text << std::endl;
	f.close();
	return 0;
}

int writeAllLine(lua_State* L) {
	auto file = lua_tostring(L, 2);
	std::ofstream f(file, std::ios::out);
	if (lua_type(L, 3) != LUA_TTABLE) {
		luaL_error(L, "table required");
		return 0;
	}
	lua_pushnil(L);
	while (lua_next(L, 3)) {
		auto text = lua_tostring(L, -1);
		f << text << std::endl;
		lua_pop(L, 1);
	}
	lua_settop(L, 0);
}

int exist(lua_State* L) {
	auto path = lua_tostring(L, 2);
	lua_pushboolean(L, std::filesystem::exists(path));
	return 1;
}

int mkdir(lua_State* L) {
	auto path = lua_tostring(L, 2);
	std::filesystem::create_directories(path);
	return 0;
}