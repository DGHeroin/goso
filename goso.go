package main

/*
#cgo windows CFLAGS: -DCGO_OS_WINDOWS=1
#cgo darwin CFLAGS: -DCGO_OS_DARWIN=1 -std=c89
#cgo linux CFLAGS: -DCGO_OS_LINUX=1
#cgo darwin LDFLAGS: -lm -ldl -fPIC -llua -L/usr/local/lib/
#include <cgoso.h>
*/
import "C"
import (
    "log"
    "runtime"
    "unsafe"
)

func main() {

}

//export luaopen_goso
func luaopen_goso(L *C.lua_State) int {
    obj := &Application{
        Name: "Application Context",
    }
    ptr := unsafe.Pointer(obj)
    C.InitMod(L, ptr)
    return 1
}

type Application struct {
    Name string
}

func (c *Application) Invoke() {
    log.Println("Invoked!", c.Name)
}

type Object struct {
    Name string
}

func (o *Object) Invoke() {
    log.Println("Invoked!", o.Name)
}

//export NewObject
func NewObject(L *C.lua_State, to *unsafe.Pointer) {
    obj := &Object{
        Name: "hello world",
    }
    *to = unsafe.Pointer(obj)
}

//export CallObject
func CallObject(L *C.lua_State, appPtr, objPtr unsafe.Pointer) {
    defer func() {
        if e := recover(); e != nil {
            log.Println("CallObject", e)
        }
    }()
    app := (*Application)(appPtr)
    obj := (*Object)(objPtr)
    app.Invoke()
    obj.Invoke()
}

//export xGC
func xGC() {
    runtime.GC()
}
