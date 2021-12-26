#pragma once
#include "Observer.hpp"
#include <algorithm>
#include <mutex>
#include <string>
#include <vector>
template <typename T> struct SafeObservable {
  std::vector<Observer<T> *> observers;
  typedef std::recursive_mutex mutex_t;
  mutex_t mtx;

public:
  void notify(T &source, const std::string &field_name) {
    std::scoped_lock<mutex_t> lock{mtx};
    for (auto observer : observers)
      if (observer)
        observer->field_changed(source, field_name);
  }
  void subscribe(Observer<T> &observer) {
    std::scoped_lock<mutex_t> lock{mtx};
    observers.push_back(&observer);
  }
  void unsubscribe(Observer<T> &observer) {
    auto it = std::find(begin(observers), end(observers), &observer);
    if (it != end(observers))
      *it = nullptr;
    // std::scoped_lock<mutex_t> lock{mtx};
    // observers.erase(remove(observers.begin(), observers.end(), &observer),
    // observers.end());
  }
};
