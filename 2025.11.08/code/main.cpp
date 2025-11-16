#include <iostream>
#include <numeric>

// 1й


/*
Рациональное число


x/y x целой, y - натуральное


+,-,*,/
reduce
==, !=, < , >


бесконечно много


1/2 == 2/4 == 4/8н

несократимая


*/


class CRational {
public:


    explicit CRational(int32_t x=0, uint32_t y=1) {
        std::cout << "CRational(int32_t x, uint32_t y)\n";
        if(y == 0) {
            throw std::exception{};
        }

        int32_t gcd = std::gcd(x, y);

        x_ = x / gcd;
        y_ = y / gcd;
    }


    CRational(const CRational& other)
        : x_(other.x_)
        , y_(other.y_)
    {
        std::cout << "CRational(const CRational& other)\n";
    }


    CRational& operator=(const CRational& other) {
        std::cout << "CRational& operator=(const CRational& other)\n";

        x_ = other.x_;
        y_ = other.y_;


        return *this;
    }


    ~CRational() {
        std::cout << "~CRational()\n";
    }

    int32_t x() const {
        //x_++;
        return x_;
    }

    uint32_t y() const {
        return y_;
    }

private:
    int32_t x_;
    uint32_t y_;
};



bool isEqual(const CRational& lhs, const CRational& rhs) {
    return lhs.x()  == rhs.x() &&  rhs.y() == lhs.y();
}


CRational plus(const CRational& lhs, const CRational& rhs) {
    return CRational{lhs.x() * (int32_t)rhs.y() + (int32_t)lhs.y() * rhs.x(), rhs.y() * lhs.y()};

}


// CRational minus(const CRational& lhs, const CRational& rhs) {
//     return CRational{lhs.x() * rhs.y() - lhs.y() * rhs.x(), rhs.y() * lhs.y()};

// }



void PrintRational(const CRational& value) {
    std::cout << value.x() << " / " << value.y() << std::endl;
}


class GeoPoint {
public:

    GeoPoint() = default;



    GeoPoint(const CRational& lat, const CRational& lon)
        : lat_(lat)
        , lon_(lon)
    {
        std::cout << "GeoPoint(const CRational& lat, const CRational& lon)\n";
    }


    //GeoPoint(const GeoPoint&) = delete;



    // ~GeoPoint() {
    //     std::cout << "~GeoPoint()\n";
    // }



private:
    CRational lat_;
    CRational lon_;
};


class CIntArray {
public:
    CIntArray(size_t size)
        : data_(new int[size])
        , size_(size)
    {}

    CIntArray(const CIntArray& other) = delete;
    //     : data_(new int[other.size_])
    //     , size_(other.size_)
    // {
    //     std::memcpy(data_, other.data_, size_);
    // }


    CIntArray& operator=(const CIntArray& other)  = delete;
    //     if(this == &other)
    //         return *this;

    //     delete[] data_;
    //     data_ = new int[other.size_];
    //     size_ = other.size_;

    //     std::memcpy(data_, other.data_, size_);

    //     return *this;
    // }

    ~CIntArray() {
        delete[] data_;
    }

private:
    int* data_;
    size_t size_;
};


int main () {
    CIntArray r1{10};
    CIntArray r2 = r1;

    r2 = r2;


    // CRational r1{1,2};
    // CRational r2(2,4);

    // PrintRational(CRational{1});

    // std::cout << "!!!!!\n";
    // {
    //     GeoPoint g;
    //     GeoPoint g2 = g;
    // }
    // std::cout << "!!!!!\n";




    // CRational r3 = r1;
    // r3 = r2;


    // std::cout << sizeof(r1.x() * r2.y()) << std::endl;
    // std::cout << isEqual(r1, r2) << std::endl;

    // int i1 = 0;
    // int i2 = 1;
    // i1 = i2;
    // int i3 = i1;

}

























// 2й поток
// /*
// Рациональное число
// x/y x - целое, y - натуральное(без 0)

// 1/2 == 2/4 == 4/8 .....

// +,-,*,/

// */




// class CRational {
// public:




//     explicit CRational(int64_t x = 0, uint64_t y = 1)    {

//         std::cout << "CRational(int64_t x, uint64_t y)\n";

//         if(y == 0) {
//             //exit(1)
//             throw std::exception{};
//         }

//         if(x > std::numeric_limits<int32_t>::max()) {
//             // .....
//         }


//         int32_t gcd = std::gcd(x, y);

//         x_ = x / gcd;
//         y_ = y / gcd;
//     }


//     CRational(const CRational& other)
//         : x_(other.x_)
//         , y_(other.y_)
//     {
//         std::cout << "CRational(const CRational& other)\n";
//     }


//     CRational& operator=(const CRational& other) {
//         std::cout << "CRational& operator=(const CRational& other)\n";
//         x_ = other.x_;
//         y_ = other.y_;

//         return *this;
//     }

//     ~CRational() {
//         std::cout << " ~CRational()\n";
//     }

//     int32_t x() const {
//         return x_;
//     }

//     uint32_t y() const {
//         return y_;
//     }

// private:
//     int32_t x_;
//     uint32_t y_;
// };


// bool isEquel(const CRational& lhs, const CRational& rhs) {
//     return lhs.x() == rhs.x() && lhs.y() == rhs.y();
// }


// CRational plus(const CRational& lhs, const CRational& rhs) {
//     return CRational{(int64_t)lhs.x() * rhs.y() + lhs.y() * (int64_t)rhs.x(), (uint64_t)lhs.y() * rhs.y()};
// }


// CRational minus(const CRational& lhs, const CRational& rhs) {
//     return CRational{(int64_t)lhs.x() * rhs.y() - lhs.y() * (int64_t)rhs.x(), (uint64_t)lhs.y() * rhs.y()};
// }


// void PrintRational(const CRational& value) {
//     std::cout << value.x() << " / "  << value.y() << std::endl;
// }


// // class GeoPoint {
// // public:
// //     GeoPoint(const CRational& lat, const CRational& lon)
// //         // : lat_(lat)
// //         // , lon_(lon)
// //     {
// //         lat_ = lat;
// //         lon_ = lon;
// //         std::cout << "GeoPoint(const CRational& lat, const CRational& lon)\n";
// //     }

// //     GeoPoint(const GeoPoint& other)
// //         : lat_(other.lat_)
// //         , lon_(other.lon_)
// //     {
// //         std::cout << "GeoPoint(const GeoPoint& other)\n";
// //     }


// //     ~GeoPoint() {
// //             std::cout << "~GeoPoint()\n";
// //     }


// // private:
// //     CRational lat_;
// //     CRational lon_;
// // };



// // class Foo {
// // public:
// //     Foo(const GeoPoint& p)
// //         : point_(p)
// //     {
// //         std::cout << "Foo(const GeoPoint& p)\n";

// //     }


// //     ~Foo() {
// //         std::cout << "~Foo()\n";
// //     }

// // private:
// //     GeoPoint point_;
// // };



// class CIntArray {
// public:
//     CIntArray(size_t size)
//         : data_(new int[size])
//         , size_(size)
//     {
//     }

//     CIntArray(const CIntArray& other) {
//         data_ = new int[other.size_];
//         size_ = other.size_;
//         std::memcpy(data_, other.data_, size_);
//     }


//     CIntArray& operator=(const CIntArray& other) {
//         if(this == &other)
//             return *this;



//         delete[] data_;
//         data_ = new int[other.size_];
//         size_ = other.size_;
//         std::memcpy(data_, other.data_, size_);

//         return *this;
//     }

//     ~CIntArray() {
//         delete[] data_;
//     }

// private:
//     int* data_;
//     size_t size_;
// };

// int main(int, char**){
//     CIntArray i1{10};

//     CIntArray i2 {10};

//     i1 = i1;

//     // CRational r1{(1 << 31) , (1u << 30)};
//     // CRational r2{1,2};


//     // PrintRational(CRational(1));

//     // CRational r3 = r1;

//     // r3 = r1;

//     // int i = 0;
//     // int j = i;

//     // i = j;


//     // std::cout << "!!!!!\n";
//     // {
//     //     GeoPoint g{r1,r2};
//     //    // std::cout << "??????\n";
//     //    // Foo f{g};
//     // }

//     // std::cout << "!!!!!\n";







// //    std::cout << isEquel(r1,r2) << std::endl;

// }
