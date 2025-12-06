#include <iostream>
#include <chrono>
#include <fstream>




class CPerson {
public:
    CPerson(const std::string& name, unsigned yearOfBirth)
    : yearOfBirth_(yearOfBirth)
    , name_(name)
    {}

    CPerson(const CPerson& other)     {
        std::cout << "CPerson(const CPerson& other)\n";
    }

    unsigned age() const {
        const std::chrono::time_point now{std::chrono::system_clock::now()};
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
        return static_cast<int>(ymd.year()) - yearOfBirth_;
    }

    const std::string& name() const {
        return name_;
    }
protected:
    std::string name_;
    unsigned yearOfBirth_;
};



class CStudent : public CPerson {
public:
    CStudent(const std::string& name, unsigned age, const std::string& university)
            : CPerson(name, age)
            , university_(university)
    {}

    void func () {
        yearOfBirth_ = 2025;
        name();
        age();
    }
private:
    std::string university_;
};




class CBudgetStudent : public CStudent {
public:
    CBudgetStudent(const std::string& name, unsigned yearOfBirth,
                   const std::string& university, unsigned sallary)
        : CStudent(name, yearOfBirth, university)
        , sallary_(sallary)
    {}
private:
    unsigned sallary_;
};


class CEmployee : public CPerson {
public:
    CEmployee(const std::string& name, int yearOfBirth, unsigned sallary)
    : CPerson(name, yearOfBirth)
    , sallary_(sallary)
    {}
private:
    unsigned sallary_ ;
};


class CIntern : public CEmployee, public CBudgetStudent {
public:
    CIntern(
        const std::string& name,
        int yearOfBirth,
        const std::string& university,
        unsigned universSallary,
        unsigned workSallary
    )
    : CEmployee(name, yearOfBirth, workSallary)
    , CBudgetStudent(name, yearOfBirth, university, universSallary)
    {}
};


// class Rectangle {
//     Rectangle(uint32_t width, uint32_t height)
//         :width_(width)
//         , height_(height)
//     {}


// private:
//     uint32_t witdh_;
//     uint32_t heigt_;
// };


// class Square : public Rectangle{
// public:
//     Square(uint32_t v)
//         :Rectangle(v, v)
//     {}
// }



void Hello(CPerson& p) {
    std::cout << "Hello. I'm " << p.name() << std::endl;
}




class Logger {
public:
     virtual void Log(const char* message) =0 ;
};

class ConsoleLogger : public Logger {
public:
    void Log(const char* message)  override {
        std::cout << message << std::endl;
    }
};


class CFileLogger : public Logger {
public:
    CFileLogger(const char* filename)
        : stream_(filename)
    {}

    ~CFileLogger() {
        stream_.close();
    }

    CFileLogger(const CFileLogger&) = delete;
    CFileLogger& operator=(const CFileLogger&) = delete;

    void Log(const char* message) {
        stream_ << message << std::endl;
    }

private:
    std::ofstream stream_;
};


void Log(Logger& log, const char* message) {
    log.Log(message);
}

// 1й поток

int main() {

    std::cout << sizeof(Logger) << std::endl;
    ConsoleLogger log;
    CFileLogger fileLog{"temp.txt"};

    Log(log, "Hello");
    Log(fileLog, "Hello");



    return 0;

    CPerson p{"Ivan Ivanov", 2007};
    CStudent st {"Petr Petrov", 1998, "ITMO"};


    std::cout << sizeof(CPerson) << std::endl;
    std::cout << sizeof(CStudent) << std::endl;
    std::cout << sizeof(CBudgetStudent) << std::endl;
    std::cout << sizeof(CEmployee) << std::endl;
    std::cout << sizeof(CIntern) << std::endl;

    st.name();
    st.age();

    Hello(st);

    return 0;
}

// 2й поток
// class CPerson  {
// public:
//     CPerson(const std::string& name, unsigned yearOfBirth)
//         : yearOfBirth_(yearOfBirth)
//         , name_(name)
//     {}

//     unsigned age() const {
//         const std::chrono::time_point now{std::chrono::system_clock::now()};
//         const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
//         return static_cast<int>(ymd.year()) - yearOfBirth_;
//     }

//     const std::string& name() const {
//         return name_;
//     }
// protected:
//     std::string name_;
//     unsigned yearOfBirth_;
// };



// // Student is a  person
// class CStudent : public CPerson {
// public:
//     CStudent(const std::string& name, unsigned age, const std::string& university)
//         : CPerson(name, age)
//         , university_(university)
//     {}


//     void func() {
//         yearOfBirth_ = 2025;

//         age();
//         name();
//     }
// private:
//     std::string university_;
// };


// class CBudgetStudent : public CStudent {
// public:
//     CBudgetStudent(const std::string& name, unsigned yearOfBirth,
//                   const std::string& university, unsigned sallary
//     )
//     : CStudent(name, yearOfBirth, university)
//     , sallary_(sallary)
//     {}
// private:
//     unsigned sallary_;
// };



// class CEmployee : public CPerson {
// public:
//     CEmployee(const std::string& name, int yearOfBirth, unsigned sallary)
//         : CPerson(name, yearOfBirth)
//         , sallary_(sallary)
//     {}
// private:
//     unsigned sallary_ ;
// };

// class CIntern : public CEmployee, public CBudgetStudent {
// public:
//     CIntern(
//         const std::string& name,
//         int yearOfBirth,
//         const std::string& university,
//         unsigned universSallary,
//         unsigned workSallary
//     )
//         : CEmployee(name, yearOfBirth, workSallary)
//         , CBudgetStudent(name, yearOfBirth, university, universSallary)
//     {}
// };



// class Rectangle {
// public:
//     Rectangle ( uint32_t width, uint32_t height)
//         : width_(width)
//         , height_(height)
//     {}

//     void setWidth(uint32_t v) {
//         width_ = v;
//     }
// private:
//     uint32_t width_;
//     uint32_t height_;
// };


// // class Square : public Rectangle{
// // public:
// //     Square(uint32_t size)
// //         : CRectangel(size, size)
// //     {}

// // };




// class CLogger {
// public:
//      virtual void Log(const char* message) {
//     }
// };


// class CConsoleLogger : public CLogger {
// public:
//     void Log(const char* message) {
//         std::cout << message << std::endl;
//     }
// };


// class CFileLogger : public CLogger {
// public:
//     CFileLogger(const char* filename)
//         : stream_(filename)
//     {}

//     ~CFileLogger() {
//         stream_.close();
//     }

//     CFileLogger(const CFileLogger&) = delete;

//     CFileLogger& operator=(const CFileLogger&) = delete;

//     void Log(const char* message) {
//         stream_ << message << std::endl;
//     }
// private:
//     std::ofstream stream_;
// };



// void Hello(const CPerson& person) {
//     std::cout << "Hello. I'm " << person.name() << std::endl;
// }


// void Log(CLogger& log, const char* message) {
//     log.Log(message);
// }




// int main(int, char**){
//     CConsoleLogger consoleLog {};
//     CFileLogger fileLogger{"temp.txt"};

//     consoleLog.Log("Hello");
//     fileLogger.Log("Hello");


//     Log(consoleLog, "Hello");
//     Log(fileLogger, "Hello");


//     // CPerson p {"Ivan Ivanov", 2007};
//     // CStudent st {"Petr Petrov", 2007, "ITMO"};
//     // CBudgetStudent bst {"Ivan Ivanov", 2007, "ITMO", 10000};

//     // std::cout << sizeof(CPerson) << std::endl;
//     // std::cout << sizeof(CStudent) << std::endl;
//     // std::cout << sizeof(CBudgetStudent) << std::endl;
//     // std::cout << sizeof(CEmployee) << std::endl;
//     // std::cout << sizeof(CIntern) << std::endl;

//     //st.age();
//     ///st.name();



//     //Hello(bst);
// }
