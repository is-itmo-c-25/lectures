#include <iostream>
#include <fstream>
#include <vector>

// 1й поток

class Logger {
public:
    virtual void Log(const char* message) {};
    void func() {

    }
protected:
    int v;
    // Table* vtbl      <---------------    void Log(const char* message) | 0x111111111
};

class ConsoleLogger : public Logger {
public:
    void Log(const char* message) override  {
        std::cout << message << std::endl;
    }
protected:
    // Table* vtbl      <---------------    void Log(const char* message) | 0x111111111
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
protected:
    // Table* vtbl      <---------------    void Log(const char* message) | 0x3333333333
};

void Log(Logger& log, const char* message) {
    // log.vtbl[void Log(const char* message)](message)
    log.Log(message);
}


class Base  {
public:
    Base() {
        std::cout << "Base()\n";
    }

    virtual ~Base() {
        std::cout << "~Base()\n";
    }
};



class Derrived : public Base {
public:
    Derrived()
        : ptr_(new int(100500))
    {
        std::cout << "Derrived()\n";
    }

    ~Derrived() {
        delete ptr_;
        std::cout << "~Derrived()\n";
    }
private:
    int* ptr_;
};


class Base2 {
public:
    virtual ~Base2() = default;
    friend std::ostream& operator<<(std::ostream& stream, const Base2& value);
protected:
    virtual void printImpl(std::ostream& stream) const {
        stream << "Base\n";
    }
};

std::ostream& operator<<(std::ostream& stream, const Base2& value) {
    value.printImpl(stream);

    return stream;
}

class Derrived2 : public Base2 {
protected:

    void printImpl(std::ostream& stream) const override {
        stream << "Derrived\n";
    }

private:
    int value_ = 239;
};





int main() {
    Base2 b;
    Derrived2 d;


    std::cout << b << std::endl;
    std::cout << d << std::endl;
    ConsoleLogger cl;
    Logger ll = cl;

    ll.Log();

    return 0;

    Logger loggers2[10];
    std::vector<Logger*> loggers;

    loggers.push_back(new ConsoleLogger{});
    loggers.push_back(new ConsoleLogger{});
    loggers.push_back(new ConsoleLogger{});
    loggers.push_back(new CFileLogger{"temp.txt"});
    loggers.push_back(new CFileLogger{"temp2.txt"});
    loggers.push_back(new ConsoleLogger{});
    loggers.push_back(new CFileLogger{"temp3.txt"});
    loggers.push_back(new ConsoleLogger{});



    for(Logger* log : loggers)
        log->Log("Hello");

    for(Logger* log : loggers)
        delete log;


    return 0;

    // Base* b = new Derrived{};
    // std::cout << "------\n";
    // delete b;
    // return 0;

    // ConsoleLogger cLog;
    // CFileLogger fileLogger{"temp.txt"};


    // Log(cLog, "Hello");
    // Log(fileLogger, "Hello");
}

// 2й поток
// class Logger {
// public:
//      virtual void Log(const char* message) = 0 ;
//     virtual ~Logger() = default;

// protected:
//     // Table* vtb_;      <--------------------     // void Log(const char* message) / 0x33333333333 /
// };

// class ConsoleLogger : public Logger {
// public:


//     void Log(const char* message) override {
//         std::cout << message << std::endl;
//     }

// protected:
//      // Table* vtb_   <--------------------     // Log / 0x33333333333  /
// };


// class CFileLogger : public Logger {
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

// protected:
//      // Table* vtb_   <--------------------     // Log / 0x22222222222 /

// private:
//     std::ofstream stream_;
// };


// void Log(Logger& log, const char* message) {

//     // log.vtb[Log](message)
//     log.Log(message);
// }


// void Log(ConsoleLogger& log, const char* message) {

//     // log.vtb[Log](message)
//     log.Log(message);
// }


// void Log(CFileLogger& log, const char* message) {

//     // log.vtb[Log](message)
//     log.Log(message);
// }


// void func(Logger* log) {
//     /*

//     */
// }



// class Base  {
// public:
//     Base() {
//         std::cout << "Base()\n";
//     }

//     ~Base() {
//         std::cout << "~Base()\n";
//     }

// };



// class Derrived : public Base {
// public:
//     Derrived() {
//          ptr_ = new int{100500};
//         std::cout << "Derrived()\n";
//     }

//     ~Derrived() {
//         delete ptr_;
//         std::cout << "~Derrived()\n";
//     }
// private:
//     int* ptr_;
// };


// // class Base {
// // public:
// //     virtual ~Base() = default;
// //     friend std::ostream& operator<<(std::ostream& stream, const Base& value);
// // protected:
// //     virtual void printImpl(std::ostream& stream) const {
// //         stream << "Base\n";
// //     }
// // };

// // std::ostream& operator<<(std::ostream& stream, const Base& value) {
// //     value.printImpl(stream);
// //     return stream;
// // }


// // class Derrived : public Base {
// // public:
// // protected:
// //     void printImpl(std::ostream& stream) const override {
// //         stream << "Derrived\n";
// //     }
// // private:
// //     int value_;
// // };


// int main() {
//     while(true) {
//         Base* b = new Derrived{};
//         delete b;
//     }
//     // Base b;
//     // std::cout << b << std::endl;

//     // Derrived d;
//     // std::cout << d << std::endl;

//     // return 0;
//     // Logger l[10];
//     // std::vector<Logger*> loggers;

//     // loggers.push_back(new ConsoleLogger{});
//     // loggers.push_back(new ConsoleLogger{});
//     // loggers.push_back(new ConsoleLogger{});
//     // loggers.push_back(new CFileLogger{"temp.txt"});
//     // loggers.push_back(new CFileLogger{"temp2.txt"});
//     // loggers.push_back(new CFileLogger{"temp3.txt"});
//     // loggers.push_back(new ConsoleLogger{});


//     // for(Logger* log : loggers)
//     //     log->Log("Hello");

//     // for(Logger* log : loggers)
//     //     delete log;




//     // Base* b = new Derrived{};

//     // delete b;

//     // return 0;
//     // Logger* log;
//     // if(true)
//     //     log = new ConsoleLogger{};
//     // else
//     //     log = new FileLogger{"temp.txt"};
//     // std::cout << sizeof(Logger) << std::endl;

//     // return 0;

//     // ConsoleLogger log;
//     // CFileLogger fileLog{"temp.txt"};


//     // func(&log);
//     // Log(log, "Hello");
//     // Log(fileLog, "Hello");
// }