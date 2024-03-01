// Prototype declaration for Sleep function from kernel32.dll
extern "C" void Sleep(DWORD dwMilliseconds);

int main() {
    // Get the current time
    auto t1 = std::chrono::high_resolution_clock::now();

    // Call the Sleep function to pause execution for 2000 milliseconds (2 seconds)
    Sleep(2000);

    // Calculate the elapsed time in seconds
    auto t2 = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0;

    // Check if the elapsed time is less than 1.5 seconds
    if (elapsedTime < 1.5) {
        return 0;
    }

    return 0;
}
