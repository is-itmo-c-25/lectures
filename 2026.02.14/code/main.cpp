#include <iostream>
#include <list>
#include <forward_list>


template <typename T>
class CSimpleAllocator {
public:
   typedef size_t size_type ;
   typedef ptrdiff_t difference_type ;
   typedef T* pointer ;
   typedef const T* const_pointer ;
   typedef T& reference ;
   typedef const T& const_reference ;
   typedef T value_type ;

   pointer allocate( size_type size) {
       pointer result = static_cast <pointer >(malloc(size * sizeof(T)));
       if(result == nullptr ) {
           // error
       }
       std::cout << "Allocate count " << size << " elements. Pointer: " << result << std::endl;
       return result;
   }

   void deallocate(pointer p, size_type n) {
       std::cout << "Deallocate pointer: " << p << std::endl;
       free(p);
   }

};


struct SPoint {
   int x;
   int y;
};



template<typename T, typename Container = std::vector<T>>
class MyStack {
public:
    void push(const T& value) {
        data_.push_back(value);
    };


    void pop() {
        data_.pop_back();
    }

    const T& top() const {
        return data_.back();
    }

    bool empty() const {
        return data_.empty();
    }
private:
    //std::vector<T, Allocator> data_;
    //std::list<T> data_;
    Container data_;
};



template<typename Container, typename T = Container::value_type>
class MyBackInsertIterator {
public:
    MyBackInsertIterator(Container& c)
        : container_(c)
    {}

    T& operator*() {
        
    }

    MyBackInsertIterator& operator++() {
        c.push_back();
    }

    MyBackInsertIterator operator++(int) {

    }
private:
    Container& container_;
}

int main () {
    int arr[] = {1,2,3,4,5};
    std::vector<int> v;
    std::copy(arr, arr + 5, MyBackInsertIterator(v));
    //std::copy(arr, arr + 5, v.begin());

    for(int i : v)
        std::cout << i << std::endl;
    return 0;

    return 0;
    MyStack<int> s;


   std::allocator_traits<CSimpleAllocator<int>> at;
   std::vector<SPoint, CSimpleAllocator<SPoint>> data;


   for(int i = 0; i < 10; ++i)
        data.push_back({i,i});

   data.pop_back();
    std::cout << "here we go\n";

   return 0;
}
