#include <iostream>
#include <vector>
#include <algorithm>


// 1й поток

class CRational {
public:
    int numerator() const {
        return numerator_;
    }
    unsigned denominator() const {
        return denominator_;
    }

    CRational& operator++() {
        numerator_ += denominator_;
        return *this;
    }
    // postfix operator
    CRational operator++(int) {
        CRational tmp(*this);
        operator++();
        return tmp;
    }


    explicit operator float() const {
        return numerator_/denominator_;
    }



private:
    int numerator_ = 0;
    unsigned denominator_ = 1;
    int temp_ = 1;
};

std::ostream&  operator<<(std::ostream& stream, const CRational& value) {
    stream << value.numerator() << '/' << value.denominator();
    return stream;
}


class IntStack{
public:
    void push(int) {

    }

    void pop() {}

    int top() const { return 0;}

    bool empty() const { return true;}

    friend std::ostream& operator<<(std::ostream& stream, const IntStack& stack);

private:
    int* data_;
    size_t size_;
};


// [1,2,3,4]
std::ostream& operator<<(std::ostream& stream, const IntStack& stack) {

    for(int i = 0; i < stack.size_; ++i) {
        stream << stack.data_[i] << ",";
    }

    return stream;
}



// FILE* operator<<(FILE* stream, const CRational& value) {
//     //stream << value.numerator() << '/' << value.denominator();
//     //return stream;

//     std::fprintf(stream, "%d", value.numerator());

//     return stream;
// }


bool operator<(const CRational& lhs, const CRational& rhs) {
    return lhs.numerator() * rhs.denominator() < rhs.numerator() * lhs.denominator();
}


bool operator>(const CRational& lhs, const CRational& rhs) {
    return (rhs < lhs);
}

bool operator<=(const CRational& lhs, const CRational& rhs) {
    return !operator>(lhs, rhs);
}


void func(float) {

}





class CMult {
public:
    explicit CMult(int mult)
        :mult_(mult)
    {}

    int operator()(int value) {
        ++count_;
        return mult_ * value;
    }

    size_t count() const {
        return count_;
    }

private:
    int mult_;
    size_t count_ = 0;
};

int twice2(int value) {
    return value * 2;
}

int main() {


    std::vector v = {1,2,3,4,5};

    std::transform(v.begin(), v.end(), v.begin(), [](int i){ return 2 * i;});

    for(int i  :  v)
        std::cout << i << ",";


    return 0;
    CMult twice{2};

    std::cout << twice2(3) << std::endl;


    twice.count();
    return 0;

    CRational r{};
    r++;
    int i = 1;

    func(static_cast<float>(r));


    float f = (float)r;

    std::cout << i << std::endl;
    std::cout << ++i << std::endl;
    std::cout << i << std::endl;

    std::cout << std::endl;

    std::cout << i << std::endl;
    std::cout << i++ << std::endl;
    std::cout << i  << std::endl;


    ++i;
    i++;


    (std::cout << r);
    return 0;
}





















// 2й поток
// class CRational {
// public:
//     int numerator() const {
//         return numerator_;
//     }

//     unsigned denominator() const {
//         return denominator_;
//     }

//     explicit operator float() const {
//         return numerator_/denominator_;
//     }

//     //friend std::ostream& operator<<(std::ostream& stream, const CRational& value);


//     void print(std::ostream& stream) {
//         stream << numerator() << '/' << denominator() << temp_;
//     }

// private:
//     int numerator_ = 0;
//     unsigned denominator_ = 1;
//     int temp_ = 0;
// };


// std::ostream& operator<<(std::ostream& stream, const CRational& value) {

//     stream << value.numerator() << '/' << value.denominator();
//     return stream;
// }





// class CMult {
// public:
//     explicit CMult(int mult)
//         :mult_(mult)
//     {}

//     int operator()(int value) {
//         return mult_ * value;
//     }


//     int mult(int value) {
//         return mult_ * value;
//     }

// private:
//     int mult_;
// };





// int twice2(int value) {
//     return 2 * value;
// }

// int main(int, char**){
//     CMult twice{2};
//     //CMult triple{3};




//     std::vector<int> v = {1,2,3,4,5};

//     std::transform(v.begin(), v.end(), v.begin(), CMult{2});

//     for(int i : v)
//         std::cout << i << std::endl;


//     return 0;

//     std::cout << twice(3) << std::endl;
//     std::cout << twice.mult(3) << std::endl;

//     return 0;
//     CRational r{};




//     // std::cout << r;

//     int i = 1;

//     std::cout << i << std::endl;
//     std::cout << ++i << std::endl;
//     std::cout << i << std::endl;



//     std::cout << i << std::endl;
//     std::cout << i++ << std::endl;
//     std::cout << i << std::endl;

//     //func((float)r);

// }
