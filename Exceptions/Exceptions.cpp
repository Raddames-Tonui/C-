
#include <iostream>
#include <utility>
#include  <vector>
#include <exception>
#include <functional>
using namespace std;

// a) Custom Exception class to inherit exception
class CustomException : public exception {
public:
    // Override what() function
    const char* what() const noexcept override {
        return "Custom exception inheriting exception!";
    }
};

    // b) Inheriting children of Exception
class CustomExcept : public runtime_error {
public:
    // Using constructor for passing custom message
    explicit CustomExcept(const string& mes) : runtime_error(mes) {};

};

    // c) Creating a Non-Standard Exception
class CustomNonStdExcept {
private:
    string message;
public:
    explicit CustomNonStdExcept(string  msg) : message(std::move(msg)) {}

    const char* what() const {
        return message.c_str();
    }
};

// custom termination function
void myterminationhandler() {
    cout << "Inside new terminate handler\n";
    abort();
}

int main () {
    // 1) ------Throwing Built-in Types --------
    int x = 7;
    try {
        if (x % 2 !=0) {
            throw 1;
        }

    } catch (int e){
        std::cout <<"Exception caught: "  << e <<  endl;
    }

    // 2) ---- Throwing Standard Exceptions------
    // All the exception classes except std::exception allows programmers to pass a custom message.
    vector <int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    try {
       cout <<  v.at(115) << endl;
    }catch (const out_of_range& e) {
        cerr << "Caught: " << e.what() << endl;
    }

    try {
        int* bigArray = new int[101100000000000000];

        delete[] bigArray;
    }catch (const bad_alloc& e) {
        cerr << "Caught: "<< e.what() << endl;
    }

    int num =10;
    int den = 0;
    int res;
    try {
        if (!den) {
            // passing custom message
            throw runtime_error ("Division by zero");
        }
         res = num / den;
    }catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << endl;
    }
    // 3)-----Custom Exception Class-------
        // a) inheriting from the std::exception class
    try {

        throw CustomException();
    }catch (const CustomException& e) {
        cout << "Caught: " << e.what() << endl;
    }
        // b) Inheriting from Other Exceptions
    try {
        throw CustomExcept(
            "Custom exception inheriting runtime_error");
    }catch (const CustomExcept& e) {
        cout << "Caught: " << e.what() << endl;
    }
        //  Creating a Non-Standard Exception
    try {
        throw CustomNonStdExcept(
            "Custom non standard exception!"
        );
    }
    catch (const CustomNonStdExcept& e) {
        cout << "Caught: " << e.what() << endl;
    }

    // UNCAUGHT EXCEPTIONS calls uncaught()-> terminate() -> abort ()
    // set_terminate(terminate_handler newhandler)
    set_terminate(myterminationhandler);
    try {
        cout << "Inside try block\n";
        throw 100;  // no such exception calls uncaught() -> terminate()
    }catch (char a) {
        cout << "Caught: " << "Inside catch block\n"<< endl;
    }


    //  A lambda + scope guard (FINALLY)
    struct  Guard {
        function<void()> func;
        ~Guard() {
            func();
            cout << "Guard destructor " << endl;
        }
    };

    auto finally = [](auto func) {
        return Guard{func};
    };

    try {
        auto _= finally([] {cout << "Cleanup \n"<< endl;});

        cout << "Inside the try" << endl;
        throw runtime_error("Ooops!");

    }catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
    }
    return 0;
}
