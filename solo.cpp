#define WINDOWS false
#if defined _WIN64 || defined _WIN32
#undef WINDOWS
#define WINDOWS true
# include <windows.h>
#else
# include <unistd.h>
#endif
#include <iostream>
#include <intrin.h>

using namespace std;

int getCpuHash()
{
    int cpuinfo[4] = { 0, 0, 0, 0 }; //EAX, EBX, ECX, EDX
    __cpuid(cpuinfo, 0);
    char16_t hash = 0;
    char16_t* ptr = (char16_t*)(&cpuinfo[0]);
    for (char32_t i = 0; i < 8; i++)
        hash += ptr[i];
    return(hash);
}

int main()
{
    int hach = getCpuHash();
    cout << hach << endl;
}