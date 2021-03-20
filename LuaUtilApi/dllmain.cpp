// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#define e(x) int x(lua_State* L);

e(readAllText)
e(writeAllLine)
e(writeAllText)
e(post)
e(get)
e(exist)
e(mkdir)

static const luaL_Reg R[] = {
	{"readAllText",readAllText},
	{"writeAllText",writeAllText},
	{"writeAllLine",writeAllLine},
	{"Post",post},
	{"Get",get},
	{"mkdir",mkdir},
	{"exist",exist},
	{ NULL,NULL }
};

void init() {
	registerLuaModule(LModule([](lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, R, 0);
		lua_setglobal(L, "Utils");
		}));
}

extern "C" {
    _declspec(dllexport) void onPostInit() {  //Loader在装载完所有插件dll时会调用这个函数，为了安全请在这里进行初始化
        std::ios::sync_with_stdio(false); //为logger的io优化
        init();
    }
}