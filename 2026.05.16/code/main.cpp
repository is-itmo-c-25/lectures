#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include <numeric>


// 1й поток



// namespace NGenerate {

// void sequential() {
//     size_t count = 1000'000'000ull;
//     std::vector<int> values(count);

//     const auto start{std::chrono::steady_clock::now()};
//     std::generate(values.begin(), values.end(), []() { return rand() % 100;});

//     const auto finish{std::chrono::steady_clock::now()};
//     const std::chrono::duration<double> elapsed_seconds{finish - start};
//     std::cout << elapsed_seconds << '\n';
// }



// void parallel() {


//     size_t count = 1000'000'000ull;
//     std::vector<int> values(count);
//     size_t threadCount = 2;
//     size_t bucketSize = count / threadCount;

//     std::vector<std::thread> threads;

//     const auto start{std::chrono::steady_clock::now()};
//     for(size_t i  = 0; i < threadCount; ++i) {
//         std::thread tr {
//             [=,&values]() {
//                 std::generate(values.begin() + i * bucketSize, values.begin()  + (i + 1) * bucketSize , []() { return rand() % 2;});
//             }
//         };

//         threads.emplace_back(std::move(tr));
//     }

//     for(auto&& tr : threads) {
//         if(tr.joinable())
//             tr.join();
//     }

//     const auto finish{std::chrono::steady_clock::now()};
//     const std::chrono::duration<double> elapsed_seconds{finish - start};
//     std::cout << elapsed_seconds << '\n';



// }





// void parallel2() {


//     size_t count = 1000'000'000ull;
//     std::vector<int> values(count);
//     size_t threadCount = 2;
//     size_t bucketSize = count / threadCount;

//     std::vector<std::thread> threads;

//     const auto start{std::chrono::steady_clock::now()};
//     for(size_t i  = 0; i < threadCount; ++i) {
//         std::thread tr {
//             [=,&values]() {
//                 for(int j = i; j < count; j += threadCount) {
//                     values[j] = rand() % 100;
//                 }
//             }
//         };

//         threads.emplace_back(std::move(tr));
//     }

//     for(auto&& tr : threads) {
//         if(tr.joinable())
//             tr.join();
//     }

//     const auto finish{std::chrono::steady_clock::now()};
//     const std::chrono::duration<double> elapsed_seconds{finish - start};
//     std::cout << elapsed_seconds << '\n';

// }


// }




// namespace NAccum {


//     void sequential(const std::vector<int>& data) {

//         const auto start{std::chrono::steady_clock::now()};

//         int result = 0;
//         for(size_t i = 0; i < data.size(); ++i)
//             result += data[i];

//         const auto finish{std::chrono::steady_clock::now()};
//         const std::chrono::duration<double> elapsed_seconds{finish - start};
//         std::cout << elapsed_seconds << '\n';


//         std::cout << result << std::endl;
//     }


//     void parallel(const std::vector<int>& data) {


//         const auto start{std::chrono::steady_clock::now()};

//         std::atomic<int> result = 0;
//         size_t threadCount = 8;
//         size_t bucketSize = data.size() / threadCount;


//         std::vector<std::thread> threads;




//         for(size_t i  = 0; i < threadCount; ++i) {
//             std::thread tr {
//                 [=,&data, &result]() {

//                     int localResult = 0;
//                     for(size_t j = i * bucketSize; j < (i+1) * bucketSize; ++j) {

//                         localResult += data[j];
//                     }

//                     result += localResult;

//                 }
//             };

//             threads.emplace_back(std::move(tr));
//         }

//         for(auto&& tr : threads) {
//             if(tr.joinable())
//                 tr.join();
//         }



//         const auto finish{std::chrono::steady_clock::now()};
//         const std::chrono::duration<double> elapsed_seconds{finish - start};
//         std::cout << elapsed_seconds << '\n';




//         std::cout << result << std::endl;
//     }
// }



// #include <queue>
// #include <functional>
// #include <mutex>
// #include <condition_variable>


// class ThreadPool {
//     using TTask = std::function<void()>;
// public:
//     ThreadPool(size_t threadCount) {
//         for(size_t i = 0; i < threadCount; ++i) {
//             threads_.emplace_back(
//                 [this]() {
//                     while(true) {
//                         TTask task;
//                         {
//                             std::unique_lock<std::mutex> lock{mutex_};
//                             cv_.wait(lock, [this] {
//                                 return !taskList_.empty() || stop_;
//                             });

//                             if(taskList_.empty())
//                                 return;

//                             task = std::move(taskList_.front());
//                             taskList_.pop();
//                         }

//                         task();
//                     }
//                 }
//             );
//         }
//     }

//     ThreadPool(const ThreadPool&) = delete;
//     ThreadPool& operator=(const ThreadPool&) = delete;


//     ~ThreadPool() {
//         {
//             std::lock_guard<std::mutex> guard{mutex_};
//             stop_ = true;
//         }
//         cv_.notify_all();

//         for(auto& tr : threads_)
//             if(tr.joinable())
//                 tr.join();
//     }


//     template<typename TFunc, typename... TArgs>
//     void addTask(TFunc&& func, TArgs&&... args) {
//         auto bound = [
//             func = std::forward<TFunc>(func),
//             ...args = std::forward<TArgs>(args)
//         ]() mutable {
//             func(args...);
//         };

//         {
//             std::lock_guard<std::mutex> guard{mutex_};
//             if(stop_)
//                 throw std::runtime_error{"addTask on stopped ThreadPool"};
//             taskList_.push(std::move(bound));
//         }
//         cv_.notify_one();
//     }

// private:
//     std::queue<TTask> taskList_;
//     std::vector<std::thread> threads_;
//     std::mutex mutex_;
//     std::condition_variable cv_;
//     bool stop_ = false;
// };


// int main(int argc, char** argv) {

//     using namespace std::chrono;

//     ThreadPool pool{2};
//     auto f = [](int n, int id) {
//         auto thread_id = std::this_thread::get_id();
//         for(int i = 0; i < n; ++i){
//             std::println("Thread id {}, Task Id {}, value : {}", thread_id, id, i);
//             std::this_thread::sleep_for(1s);
//         }
//     };


//     for(int i = 0; i < 4; ++i)
//         pool.addTask(f, 5, i);


//     return 0;


//     return 0;
//     std::mutex m1;
//     std::mutex m2;

//     std::thread tr1 {
//         [&]() {
//             int i = 0;
//             while(true) {
//                 ++i;
//                 m1.lock();
//                 m2.lock();
//                 std::cout << "progress tr1 " << i << std::endl;
//                 m1.unlock();
//                 m2.unlock();
//             }

//         }
//     };

//     std::thread tr2 {
//         [&]() {
//             int i = 0;
//             while(true) {

//                 if(!m2.try_lock())
//                     continue;
//                 m1.lock();
//                 ++i;
//                 std::cout << "progress tr2 " << i << std::endl;
//                 m2.unlock();
//                 m1.unlock();
//             }
//         }
//     };



//     tr1.join();
//     tr2.join();



//     return 0;

//     std::vector<int> data(1000'000'000ull, 1);


//     std::cout << "Parallel\n";
//     NAccum::parallel(data);

//     std::cout << "Sequential\n";
//     NAccum::sequential(data);
//     return 0;
// }




void sequential() {



    size_t count = 1000'000'000ull;
    std::vector<int> values(count);

    const auto start{std::chrono::steady_clock::now()};

    std::generate(values.begin(), values.end(), []() { return rand() % 100;});


    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{finish - start};
    std::cout << elapsed_seconds << '\n';
}



void parallel() {



    size_t count = 1000'000'000ull;
    size_t threadCount = 8;
    size_t perThreadCount = count / threadCount;

    std::vector<int> values(count);

    std::vector<std::thread> threads;


    const auto start{std::chrono::steady_clock::now()};

    for(int i = 0; i < threadCount; ++i) {
        auto begin = values.begin() + i * perThreadCount;
        auto end = values.begin() + (i + 1) * perThreadCount;
        threads.emplace_back(
            [&](){
                std::generate(begin, end, []() {return rand() % 100;});
            }
        );
    }
    for(auto& tr : threads)
        tr.join();

    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{finish - start};
    std::cout << elapsed_seconds << '\n';

}


namespace NAccum {


    void sequential(const std::vector<int>& data) {

        const auto start{std::chrono::steady_clock::now()};

        int result = 0;
        for(size_t i = 0; i < data.size(); ++i)
            result += data[i];

        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};
        std::cout << elapsed_seconds << '\n';


        std::cout << result << std::endl;
    }


    void parallel(const std::vector<int>& data, size_t threadCount) {
        const auto start{std::chrono::steady_clock::now()};
        std::vector<std::thread> threads;
        std::atomic<int> result = 0;

        size_t perThreadCount = data.size() / threadCount;
        std::mutex mutex;
        for(int t = 0; t < threadCount; ++t) {
            threads.emplace_back([&](int thread){
                int localResult = 0;
                for(size_t i = thread * perThreadCount; i < (thread + 1) * perThreadCount; ++i) {
                    localResult += data[i];
                }

                result.fetch_add(localResult, std::memory_order_relaxed);


            }, t);
        }


        for(auto& tr : threads)
            tr.join();

        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};
        std::cout << elapsed_seconds << '\n';

        std::cout << result << std::endl;
    }
}

#include <functional>
#include <list>
#include <mutex>
using namespace std::chrono;

class ThreadPool {
    using TTask = std::function<void()>;

public:
    ThreadPool(size_t threadCount){
        for(int i = 0; i < threadCount; ++i)
            threads_.emplace_back(
                [this]() {
                    while (true) {
                        TTask task;
                        {
                            std::lock_guard<std::mutex> lock(mutex_);
                            if(tasks_.empty() && stop_) {

                                    return;

                            }

                            if(tasks_.empty())
                                continue;

                            task = std::move(tasks_.front());
                            tasks_.pop_front();
                        }

                        task();

                    }
                }
            );
    }


    ~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
        for (auto& thread : threads_) {
            if (thread.joinable())
                thread.join();
        }
    };

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template<typename TFunc, typename... TArgs>
    void addTask(TFunc&& func, TArgs&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.push_back(
            [func = std::forward<TFunc>(func),
             ...args = std::forward<TArgs>(args)]() mutable {
                //std::invoke(func, args...);
                func(args...);
            }
        );
    }

private:
    std::vector<std::thread> threads_;
    std::list<TTask> tasks_;
    std::mutex mutex_;
    bool stop_ = false;
};


int main() {
    using namespace std::chrono;
    ThreadPool pool{2};

    auto f = [](int n) {
        auto thread_id = std::this_thread::get_id();
        for(int i = 0; i < n; ++i){
            std::println("Thread id {},  value : {}", thread_id, i);
            std::this_thread::sleep_for(1s);
        }
    };

    for(int i = 0; i < 4; ++i)
        pool.addTask(f, 5);



    // std::mutex m1;
    // std::mutex m2;

    // std::thread tr1 {
    //     [&]() {
    //         int i = 0;
    //         while(true) {
    //             if(!m1.try_lock()) {
    //                 std::cout << "tr1 continue\n";
    //                 continue;
    //             }

    //             m2.lock();
    //             ++i;
    //             std::cout << "progress tr1 " << i << std::endl;
    //             m1.unlock();
    //             m2.unlock();
    //         }

    //     }
    // };

    // std::thread tr2 {
    //     [&]() {
    //         int i = 0;
    //         while(true) {

    //             m2.lock();
    //             if(!m1.try_lock()) {
    //                 std::cout << "tr2 continue\n";
    //                 m2.unlock();
    //                 continue;

    //             }

    //             ++i;
    //             std::cout << "progress tr2 " << i << std::endl;
    //             m2.unlock();
    //             m1.unlock();
    //         }
    //     }
    // };



    // tr1.join();
    // tr2.join();




    // std::vector<int> data(10'000'000'000ull, 1);


    // std::cout << "Parallel\n";
    // NAccum::parallel(data, 16);

    // std::cout << "Sequential\n";
    // NAccum::sequential(data);
    return 0;
}


// int main(int argc, char** argv) {
//     using namespace std::chrono_literals;

//     int j = 0;
//     for(int i = 0; i < 8; ++i) {
//         std::thread tr{[&j]{
//             int i = 0;
//             std::print(
//                 "Hello from {0}. i has address {1}, j has address {2}\n",
//                 std::this_thread::get_id(), (void*)std::addressof(i), (void*)std::addressof(j)
//             );
//         }};
//         tr.detach();
//     }

//     std::this_thread::sleep_for(1s);
//     return 0;
// }