#include <iostream>
#include <string>

using namespace std;

string encryptCaesar(const string& text) {
    string encryptedText = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            encryptedText += static_cast<char>((c - base + 3) % 26 + base);
        } else {
            encryptedText += c;
        }
    }
    return encryptedText;
}

int main() {
    string plaintext;
    cout << "Enter the text to encrypt: ";
    getline(cin, plaintext);

    string ciphertext = encryptCaesar(plaintext);
    cout << "Encrypted text: " << ciphertext << endl;

    return 0;
}
