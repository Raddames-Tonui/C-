

#include <iostream>
using namespace std;

class StringBuilder {
private:
    char* buffer;
    int size;
    int length;

public:
    StringBuilder() {
        size = 6;
        length = 0;
        buffer =new char[size];
        buffer[0] ='\0';
    }

    // Copy constructor
    StringBuilder(const StringBuilder& other) {
        size = other.size;
        length = other.length;
        buffer = new char[size];
        for (int i = 0; i < length; i++) {
            buffer[i] = other.buffer[i];
        }
        buffer[length] = '\0';
    }

    ~StringBuilder() {
        delete[] buffer;
        buffer = nullptr;
    }

    void append(const char* str) {
        int strlen = strLength(str);
        if (length + strlen + 1 > size) {
            resize((length + strlen + 1) * 2);
        }

        //copy character 1 by 1
        for (int i = 0 ; i < strlen; i++) {
            buffer[length++] = str[i];
        }

        buffer[length] = '\0';
    }

    int strLength(const char* str) {
        int count = 0;
        while (str[count] != '\0') count++;
        return count;
    }

    void resize(int newSize) {
        char* newBuffer = new char[newSize];
        for (int i = 0; i < length; i++) {
            newBuffer[i] = buffer[i];     // old data to new buffer
        }

        delete[] buffer;
        buffer = newBuffer;
        size = newSize;
    }

    // += operator for appending another string
    StringBuilder& operator+=(const char* str) {
        append(str);
        return *this;
    }

    // + operator to return a new combined StringBuilder
    StringBuilder operator+(const char* str) const {
        StringBuilder result;
        result.append(buffer);
        result.append(str);
        return result;
    }

    // ==
    bool operator==(const StringBuilder& other) const {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++) {
            if (buffer[i] != other.buffer[i]) return false;
        }
        return true;
    }

    // []
    char& operator[](int index) {
        static char dummy = '\0';
        if (index < 0 || index >= length) {
            cout << "index out of range" << endl;
            return dummy;
        }
        return buffer[index];
    }



    void print() {
        for (int i = 0; i < length; i++) {
            cout << buffer[i];
        }
            cout << "\n";
    }
};


int main() {
    // +
    StringBuilder sb;
    sb += "Hello";
    sb += " ";
    sb += "World!";
    sb.print();

    StringBuilder sb2 = sb + "This is a test";
    sb.print();
    sb2.print();

    // ==
    StringBuilder sb3;
    sb3 += "whale";
    StringBuilder sb4;
    sb4.append("whale");

    if (sb3 == sb4) {
        cout << "Equal" << endl;
    } else {
        cout << "Not equal" << endl;
    }

    // []
    cout << "index at: " << sb[0] << endl;
    cout << "index at: " << sb[1] << endl;

    return 0;
}
