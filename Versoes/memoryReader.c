#include <stdio.h> 
#include <windows.h> 
 
int main() { 
    MEMORYSTATUSEX status; 
    status.dwLength = sizeof(status); 
 
    GlobalMemoryStatusEx(&status); 
    printf("Total RAM: %llu bytes\n", status.ullTotalPhys);

    return 0;
}