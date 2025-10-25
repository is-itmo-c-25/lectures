#include <iostream>
#include <cassert>
#include <vector>

// 1й поток


void print() {
    std::cout << std::endl;
}

void print(int x) {
    std::cout << x << std::endl;
}

void print(const char* str) {
    std::cout << str << std::endl;
}

void print(int x, int y) {
    std::cout << x << " " << y << std::endl;
}


// void print(float x) {
//     std::cout << x << std::endl;
// }


int swap(int* pi, int* pj) {


    //1
    // assert(pi != nullptr);
    // assert(pj != nullptr);


    //2
    // if(pi == nullptr || pj == nullptr)
    //     return 1;

    int temp = *pi;
    *pi = *pj;
    *pj = temp;

    return 0;
}




int foo() {
    int i = 20;
    int& res = i;
    return i;
}

int boo() {
    int i = 2;
    return i;
}


int coo() {
    int i = 100500;
    return i;
}


int& foo(int& x){
    return x;
}


void ToUpper(std::string& str) {
    for(char& ch : str)
        ch = std::toupper(ch);


}



void func(int a) {
    std::cout << "int" << std::endl;
}

void func(const char* str) {
    std::cout << "char*" << std::endl;
}


void func(int* pi) {
    std::cout << "int*" << std::endl;
}


void func(std::nullptr_t) {

}


void f(int x, int y) {

}


struct SPoint {
    int x;
    int y;

    SPoint(int a = 0, int b = 0) {
        x = a;
        y = b;
    }

};

struct SCirlce {
    SPoint p;
    float  r;
};


int l();


namespace A {
    namespace A {
        void func1() {

        }
    }
}



void func2() {
    A::A::func1();
}


namespace A {
    void func3() {
        A::func1();
    }
}

int main() {

    int i = 0;
    int ar[] = {1,2,3,4,5};
    SPoint p1 = {1,2};
    SPoint p2 {1,2};
    SPoint p3(1,2);
    int j(3);
    SPoint p4{};
    int l{};

    std::string str = {'a', 'b', 'c'};


    std::cout << l << std::endl;


    SCirlce s = {.p = {.x = 1,. y.= 2}, .r = 2};

    // int* pi = nullptr;


    // func(pi); // func(int*)

    // f(0,0);



    // func(10); // int
    // func("aa"); // char*
    // //func(NULL); // call is ambiguous
    // func(0); // func(int)
    // func(nullptr); // func(nullptr_t)
    return 0;

    std::vector<int> v = {1,2,3,4,5};
    //for(std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
    for(auto i : v)
        std::cout << i;


    // std::string str = "aaaaa!";

    // ToUpper(str);

    // std::cout << str << std::endl;


    return 0;

    int x = foo();
    int d = boo();
    coo();

    std::cout << x << std::endl;

    // std::cout << d << std::endl;
    return 0;



    // int i = 10;
    // int& j = i;
    // int& k = j;

    // //int& k; // error: ‘k’ declared as reference but not initialized
    // j = 20;



    // std::cout << i << std::endl;
    // std::cout << &i << " " << &j << std::endl;
    // std::cout << sizeof(j) << std::endl;

    // const int& r = i;
    // //r = 21; // error assignment of read-only reference ‘r’
    // i = 40;

    // std::cout << r << std::endl;
    return 0;

    // return 0;
    // int i = 10;
    // int* pi = &i;
    // int* pn = nullptr;



    // if(swap(pi, pn) != 0)
    //     std::cerr << "error";

    return 0;
}






// 2й поток

// uint64_t factorial(uint32_t n) {

//     uint64_t result = 0;

//     if(n == 0)
//         result = 1;
//     else
//         result = n * factorial(n - 1);


//     std::cout << " factorial " << n
//               << " adress of n " << &n
//               << " adress of result " << &result
//               << " adress of factorial " << (void*)&factorial
//               << std::endl;


//     return result;
// }


// void swap(int* pi, int* pj) { // pi == 0x16fd4ed58 pj = 0x0
//     int temp = *pi;
//     *pi = *pj;
//     *pj = temp;
// }



// void swap(int& i, int& j) {
//     int temp = i;
//     i = j;
//     j = temp;
// }




// int& foo(int& x) {
//     return x;
// }

// // int* foo() {
// //     int i = 20;
// //     return i;
// // }

// int boo() {
//     int i = 2;
//     return i;
// }


// void print() {
//     std::cout << std::endl;
// }

// void print(int x) {
//     std::cout << x << std::endl;
// }

// void print(const char* str) {
//     std::cout << str << std::endl;
// }

// void print(int x, int y) {
//     std::cout << x << " " << y << std::endl;
// }

// void print(float x) {
//     std::cout << x << std::endl;
// }

// int test(int i) {
//     return i;
// }

// // float test(int f) {
// //     return (float)f;
// // }


// // void func(int a) {
// //     std::cout << "int" << std::endl;
// // }

// // void func(const char* str) {
// //     std::cout << "char*" << std::endl;
// // }

// void func(const char* str) {
//     std::cout << "char*" << std::endl;
// }

// void func(int* i) {
//     std::cout << "int*" << std::endl;
// }


// void func(std::nullptr_t) {
//     std::cout << "nullptr_t" << std::endl;
// }


// struct SPoint {
//     int x = 0;
//     int y = 0;

//     SPoint(int a = 0, int b = 0) {
//         x = a;
//         y = b;
//     }
// };

// SPoint make_point(int x = 0, int y = 0) {
//     SPoint p {x,y};
//     return p;
// }




// struct SCircle {
//     SPoint p;
//     float r;
// };


// void coo(int i, SPoint p = {0,0}) {

// }

// // SPoint f() {
// //     return {};
// // }


// namespace Foo {
//     void f() {
//         std::cout << "Foo" << std::endl;
//     }
// }

// namespace Boo {
//     void f() {
//         std::cout << "Boo" << std::endl;
//     }
// }



// void func(const std::vector<int>& v) {
//     int a = 1;
//     {
//         int x = 0;
//     }
// }



// void increment() {
//     counter++;
// }


// namespace {
//     int counter;
// }



// namespace {
//     namespace {
//         int counter;
//     }

//     void increment() { counter++; }
// }

// using namespace Foo;
// int main() {

//     //f();

//     // Foo::f();
//     // Boo::f();

//     return 0;



//     SCircle s {{1,2},2};

//       int a[] = {1,2,3};

//       int i = 0;
//       ///SPoint p();
//       // int j(0);

// //    SPoint p1 = make_point(1, 1); // {1,1}
// //    SPoint p2 = make_point(1); // {1,0}
// //    SPoint p1 = make_point(); // {0,0}

//     // int* i = nullptr;
//     // func(i); // int*
//     // func("aa"); // char*
//     // func(nullptr); // call is ambigous

//     // int pi = NULL;
//     // func(10); // int
//     // func("aa"); // char*
//     // //func(NULL); // call is ambiguous
//     // func(0); // int
//     // func(nullptr); //char*


//     return 0;
//     //test(10);

//     print();
//     print(10);
//     print("Hello world!");
//     print(10, 20);
//     print((int)20.1);  // print(int)


//     return 0;

//     // int* x = foo();
//     // boo();
//     // std::cout << *x; // !OOps


//     // return 0;



//     // int a = 10;
//     // int b = 20;
//     // swap(a, b);

//     // int& c = foo(a);


//     // std::cout << a << " " << b << std::endl;

//     // return 0;

//     // int i = 10;
//     // int& j = i;
//     // //int& k; // error: ‘k’ declared as reference but not initialized

//     // j = 20;

//     // std::cout << i << std::endl;
//     // std::cout << &i << " " << &j << std::endl;

//     // const int& r = i;
//     // std::cout << &i << " " << &r << std::endl;
//     // //r = 21; // error assignment of read-only reference ‘r’
//     // i = 21;
//     // std::cout << r << std::endl;


//     // int i = 10;

//     // int* pi = &i;       // 0x16fd4ed58
//     // int* pn = nullptr;  // 0x0

//     // std::cout << pi << " " << pn << std::endl;   // 0x16fd4ed58 0x0
//     // swap(pi, pn);
//     // std::cout << pi << " " << pn << std::endl;

//     // std::cout << i << std::endl;

//     return 0;
// }
