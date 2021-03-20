#include "pch.h"
#include <iostream>
#include <thread>
#define  CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

int get(lua_State* L) {
	auto url = lua_tostring(L, 2);
	auto path = lua_tostring(L, 3);
	httplib::Client cli(url);
	cli.set_connection_timeout(0, 300000);
	auto res = cli.Get(path);
	if (!res) {
		lua_pushnil(L);
		return 1;
	}
	lua_newtable(L);
	{
		lua_pushstring(L, "status");
		lua_pushinteger(L, res->status);
		lua_settable(L, -3);

		lua_pushstring(L, "headers");
		lua_newtable(L);
		{
			int tmp = 0;
			for (auto i : res->headers) {
				lua_pushinteger(L, ++tmp);
				lua_newtable(L);
				{
					lua_pushstring(L, i.first.c_str());
					lua_pushstring(L, i.second.c_str());
					lua_settable(L, -3);
				}
				lua_settable(L, -3);
			}
		}
		lua_settable(L, -3);

		lua_pushstring(L, "body");
		lua_pushstring(L, res->body.c_str());
		lua_settable(L, -3);
	}
	return 1;
}

int post(lua_State* L) {
	auto url = lua_tostring(L, 2);
	auto path = lua_tostring(L, 3);
	httplib::Client cli(url);
	auto res = cli.Post(path);
	if (!res) {
		lua_pushnil(L);
		return 1;
	}
	lua_newtable(L);
	{
		lua_pushstring(L, "status");
		lua_pushinteger(L, res->status);
		lua_settable(L, -3);

		lua_pushstring(L, "headers");
		lua_newtable(L);
		{
			int tmp = 0;
			for (auto i : res->headers) {
				lua_pushinteger(L, ++tmp);
				lua_newtable(L);
				{
					lua_pushstring(L, i.first.c_str());
					lua_pushstring(L, i.second.c_str());
					lua_settable(L, -3);
				}
				lua_settable(L, -3);
			}
		}
		lua_settable(L, -3);

		lua_pushstring(L, "body");
		lua_pushstring(L, res->body.c_str());
		lua_settable(L, -3);
	}
	return 1;
}
