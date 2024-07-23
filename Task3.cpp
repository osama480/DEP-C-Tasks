#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to compress using Run-Length Encoding
string compress(const string& data) {
    string compressed;
    int n = data.size();
   
    for (int i = 0; i < n; ++i) {
        int count = 1;
        while (i < n - 1 && data[i] == data[i + 1]) {
            ++i;
            ++count;
        }
        compressed += data[i];
        compressed += to_string(count);
    }
   
    return compressed;
}

// Function to decompress using Run-Length Encoding
string decompress(const string& data) {
    string decompressed;
    int n = data.size();
   
    for (int i = 0; i < n; ++i) {
        char ch = data[i];
        ++i;
        int count = 0;
        while (i < n && isdigit(data[i])) {
            count = count * 10 + (data[i] - '0');
            ++i;
        }
        --i;
        decompressed.append(count, ch);
    }
   
    return decompressed;
}

// Function to read a file into a string
string readFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        cerr << "Could not open the file!" << endl;
        exit(EXIT_FAILURE);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to write a string to a file
void writeFile(const string& filename, const string& content) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file) {
        cerr << "Could not open the file!" << endl;
        exit(EXIT_FAILURE);
    }
    file << content;
    file.close();
}

int main() {
    string inputFile, compressedFile, decompressedFile;
   
    cout << "Enter the name of the file to compress: ";
    cin >> inputFile;
    cout << "Enter the name of the file to save compressed content: ";
    cin >> compressedFile;
    cout << "Enter the name of the file to save decompressed content: ";
    cin >> decompressedFile;
   
    // Read the input file
    string data = readFile(inputFile);
   
    // Compress the data
    string compressedData = compress(data);
   
    // Write the compressed data to file
    writeFile(compressedFile, compressedData);
   
    // Decompress the data
    string decompressedData = decompress(compressedData);
   
    // Write the decompressed data to file
    writeFile(decompressedFile, decompressedData);
   
    cout << "Compression and decompression completed successfully!" << endl;
   
    return 0;
}