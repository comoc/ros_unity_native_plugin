#include <dlfcn.h>
#include <cstdint>
#include <iostream>

#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char* argv[])
{
    void* handle = dlopen("./libunity_plugin.so", RTLD_NOW);
    cout << "dlopen: " << &handle << endl;

    intptr_t (*create)(void);
    void (*spin_some)(intptr_t);
    void (*talk)(intptr_t, int);
    void (*destroy)(intptr_t);

    create = (intptr_t (*)())dlsym(handle, "create");
    // cout << "dlsym create: " << &create << endl;

    spin_some = (void (*)(intptr_t))dlsym(handle, "spin_some");
    talk = (void (*)(intptr_t, int))dlsym(handle, "talk");
    destroy = (void (*)(intptr_t))dlsym(handle, "destroy");

    intptr_t instance = (*create)();
    // cout << "create" << endl;

    for (int i = 0; i < 10; i++)
    {
        (*talk)(instance, 0);
        (*spin_some)(instance);
        this_thread::sleep_for(chrono::seconds(1));
    }

    (*destroy)(instance);

    dlclose(handle);

    return 0;
}