#include <iostream>



//2й поток


enum EDayOfWeek {
    MONDAY,
    SUNDAY,
};


int main(int, char**) {

    int monday = 1; // 0, 2
    int tusday = 2;
    int sunday = 7; // 6, 1



    int n = -2, a = 1, b = 2, z = 20;


    if (n > 0)
        if(a > b)
            z = a;
        else
            z = b;




    std::cout << z << std::endl;











    EDayOfWeek dayOfWeek = SUNDAY;


    return 0;
}


















// 1й поток
// enum EDayOfWeek : int8_t {
//     MONDAY,
//     SUNDAY
// };




// int main(int, char**){


//     int n = -2, a = 1, b = 2, z = 20;


//     if (n > 0)
//         if(a > b)
//             z = a;
//     else
//         z = b;


//     std::cout << z << std::endl;

//     const short monday = 1 ; // or 0
//     const short sunday = 6; // or 7




//     EDayOfWeek dayOfWeek = MONDAY;
