// luatest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<lua.hpp>
using namespace std;

int main()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);
	luaL_dofile(l, "main.lua");
	lua_close(l);
	system("pause");
    return 0;
}

