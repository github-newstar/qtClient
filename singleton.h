//
// Created by jo on 2025/2/19.
//

#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"

template<typename T>
class Singleton {
public:
    void PrintAddress(){
        std::cout << instance_.get() << std::endl;
        }
    ~Singleton(){
        std::cout<< "this is singleton destruct " << std::endl;
     }
    static std::shared_ptr<T> GetInstance() {
          static std::once_flag flag;
          std::call_once(flag, [](){
              instance_ = std::shared_ptr<T>(new T);
              });
          return instance_;
      }
protected:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static std::shared_ptr<T> instance_;
};

template <typename  T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;



#endif //SINGLETON_H
