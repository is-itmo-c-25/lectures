#include <iostream>





//1й поток


void swap(int* pa, int* pb) { // pa -> x, pb ->y, x = 1, y = 2;
    int* tmp = pa;          // tmp = pa
    pa = pb;                // pa -> y
    pb = tmp;              // pb -> x;
}


int main (int argc, char* argv[]) {




    int i = 2233234;
    int* pi = &i;

    char* c = (char*)pi;
    c++;
    c++;
    std::cout << *c << std::endl;



    int x = 1;
    int y = 2;



    std::cout << x << " " << y << std::endl;

    swap(&x, &y);

    std::cout << x << " " << y << std::endl;



    return 0;


    for(int i = 0; i < argc; ++i)
        std::cout << argv[i] << " ";

    return 0;
}






// // 2й поток
// void swap(int* pa, int* pb) { // pa -> x, pb -> y , x = 1, y = 2
//     int tmp = *pa;          // tmp = 1;
//     *pa = *pb;                // x = 2;
//     *pb = tmp;              // y = 1
// }

// int main(int argc, char** argv){


//     int j = 70;
//     int* pj = &j;


//     char* b = (char*)pj;
//     b++;

//     std::cout << *b << std::endl;

//     return 0;

//     int i = 0;
//     std::cout << "Value: " << i << " Address: " << &i << std::endl;

//     int* pi = &i;
//     std::cout << "Value: " << pi << " Address: " << &pi << std::endl;

//     int** ppi = &pi;
//     std::cout << "Value: " << ppi << " Address: " << &ppi << std::endl;

//     int*** pppi = &ppi;
//     std::cout << "Value: " << pppi << " Address: " << &pppi << std::endl;


//     std::cout << *(*ppi) << std::endl;


//     return 0;

//     int x = 1;
//     int y = 2;

//     std::cout << x << " " << y << std::endl;

//     swap(&x, &y);


//     std::cout << x << " " << y << std::endl;



//     // for(int i = 0; i < argc; ++i)
//     //     std::cout << argv[i] << " ";
// }
