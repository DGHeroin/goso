#ifndef GOSO_H
#define GOSO_H

#include <stdio.h>
#include <unistd.h>

#include <lua.h>
#include <lauxlib.h>
#include <lauxlib.h>

// C side
void InitMod(lua_State*L, void* ptr);
// Go side
void NewObject(lua_State*L, void**ptr);
void CallObject(lua_State*L, void*ctx, void*ptr);
void xGC();

#endif