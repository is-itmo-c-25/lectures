#include <iostream>
#include <assert.h>



// 1й поток

struct Point {
    int x;      // 4
    int y;      // 4
};




struct Foo {
    int64_t b;          // 8 bytes
    uint32_t d;         // 4 byte
    char a;             // 1 byte
    uint8_t c;          // 1 buty
};


struct Key {
    char name[13];
    char code[3];
};


bool KeyCompare(const Key& k1, const Key& k2) {
    return (std::strcmp(k1.name, k2.name) == 0) && (std::strcmp(k1.code, k2.code) == 0);
}


// 24
struct Triangle {
    Point a;
    Point b;
    Point c;
};


// 24
struct Rect {
    Point left_top;
    Point right_top;
    Point left_bottom;
};


// 12
struct Circle {
    Point center;
    float r;
};


// 4
enum FigureType{
    ETriangle,
    ERect,
    ECircle,
};


struct Figure
{
    union  {
        Triangle tr;       // 24
        Circle   c;        // 24
        Rect     r;        // 12
    };


    FigureType type;   // 4
};



int foo(int) {
    return 0;
}


struct Cow {
    int weight;
    int color;
    uint64_t dots;
};


void* FindMax(void* array, size_t size, size_t size_elemnt, bool(*compare)(void*,void*)) {
    assert(array);
    assert(size > 0);


    void* result = array;

    int8_t* a = (int8_t*)array;


    for(int i = 0; i < size; ++i) {
        if(!compare(result, a + i * size_elemnt))
            result = a + i * size_elemnt;
    }

    return result;
}



bool int_less(void* a, void* b) {
    return *(int*)a < *(int*)b;
}

bool cow_less(void* a, void* b) {
    return ((Cow*)a)->weight < ((Cow*)b)->weight;
}




bool int_greater(void* a, void* b) {
    return *(int*)a > *(int*)b;
}




int main() {


    int(*funcPtr)(int) = foo;


    int array[] = {1,2,3,4,5};
    Cow cowArray[] = { {.weight = 150, .dots=10 }, {.weight = 170, .dots=8 }};

    std::cout << *(int*)FindMax(array, 5, sizeof(int), int_less) << std::endl;
    std::cout <<  *(int*)FindMax(array, 5, sizeof(int), int_greater) << std::endl;


    std::cout << ((Cow*)FindMax(cowArray, 2, sizeof(Cow), cow_less))->dots << std::endl;

    return 0;

    Key k1 = { .name = "0123456789AB", .code = "12"};
    Key k2 = { .name = "0123456789AB", .code = "10"};

    std::cout << KeyCompare(k1, k2) << std::endl;


//    std::cout << std::format("Size of Key {}\n", sizeof(Key));
    return 0;
}





















// 2й поток

/*
struct Point {
    int x;      // 4
    int y;      // 4
};


struct Foo {
    int64_t  b; // 8 bytes
    uint32_t d; // 4 byte
    char     a; // 1 byte
    uint8_t  c; // 1 byte
};


struct Key {
    char name[13];  // 13
    char code[3];   // 3
};


struct Boo {
    int32_t i1;
    int32_t i2;
    int32_t i3;
    int32_t i4;
};

bool Compare(Key* a, Key* b) {
    return (std::strcmp(a->name, b->name) == 0) && (std::strcmp(a->code, b->code) == 0);

}


bool Compare(Boo* a, Boo* b) {
    return (a->i1 == b->i1) && (a->i2 == b->i2) ; // ....

}

// 24
struct Triangle {
    Point a;
    Point b;
    Point c;
};


// 24
struct Rect {
    Point left_top;
    Point right_top;
    Point left_bottom;
};



// 12
struct Circle {
    Point center;
    float r;
};


// 4
enum FigureType{
    ETriangle,
    ERect,
    ECircle,
};



struct  Figure {
    union {
        Triangle tr;  // 24
        Rect     r;   // 24
        Circle   c ;   // 12
    };
    FigureType type ; // 4
};



void printFigure(Figure f) {
    if(f.type == ETriangle) {
        // ...
    }

}



int foo (int) {
    return 0;
}


int FindMax(int* array, size_t size, bool(*compare)(int a, int b)) {

    assert(array!= nullptr);
    assert(size > 0);
    int result = array[0];

    for(int i = 1; i < size; ++i) {
        if(!compare(result, array[i]))
            result = array[i];
    }


    return result;
}


bool less(int a, int b) {
    return a < b;
}


bool greater(int a, int b) {
    return a > b;
}






int func(int* p[]) {
    return 0;
}

int main(int argc, char** argv) {

    //char** a = {"aaa", "{bbb}"};


    int arr[2][2] = {{1,2},{1,2}};
    func(arr);

    int(*funcPtr)(int) = foo;


    int array[] = {1,2,3,4,5};


    FindMax(array, 5, less);
    FindMax(array, 5, greater);

    std::cout << sizeof(Figure) << std::endl;


    Figure figures1 = {.c = { {0,0} , 1 }, .type = ECircle};
    Figure figures2 = {.r = { {0,0} , {1, 1}, { 1, 0} } , .type = ERect};
    Figure figures3 = {.tr = { {0,0} , {1, 1}, {1, 0} }, .type = ETriangle};


    return 0;
    Key k1 = {.name = "0123456789AB", .code="10"};
    Key k2 = {.name = "0123456789AB", .code="10"};


    std::cout << Compare(&k1, &k2) << std::endl;

    // std::cout << std::format("Size of Key {}", sizeof(Key)) << std::endl;
    return 0;
}

*/