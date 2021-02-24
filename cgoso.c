#include "cgoso.h"

static int l_callObject(lua_State* L) {
    int top = lua_gettop(L);
    void* ptr = lua_touserdata(L, 2);
    void* app = NULL;
    // handle first param
    lua_settop(L, 1);
    if(lua_istable(L, -1)) {
        lua_getfield(L, -1, "application");
        if (lua_isuserdata(L, -1)) {
            app = lua_touserdata(L, -1);
        }
    }
    lua_settop(L, top);
    // handle second param

    CallObject(L, app, ptr);
    return 0;
}

static int l_newObject(lua_State* L) {
    void* ptr = NULL;
    NewObject(L, &ptr);
    lua_pushlightuserdata(L, ptr);
    return 1;
}
static int l_sleep(lua_State* L) {
    int n = lua_tointeger(L, 2);
    usleep(n);
    return 0;
}
static int l_gc(lua_State* L) {
    xGC();
    return 0;
}

static const struct luaL_Reg libs [] = {
     {"new", l_newObject},
     {"call", l_callObject},
     {"sleep", l_sleep},
     {"gc", l_gc},
     {NULL, NULL}
};

void InitMod(lua_State*L, void* app) {
    lua_newtable (L);
    luaL_setfuncs (L, libs, 0);

    lua_pushstring(L, "application");
    lua_pushlightuserdata(L, app);
    lua_settable(L ,3);
}