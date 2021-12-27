#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
using namespace std;

struct HotDrink {
  virtual ~HotDrink() = default;
  virtual void prepare(int volumn) = 0;
};
struct Tea : HotDrink {
  void prepare(int volumn) override {
    cout << "Take tea bag, boil water, pour " << volumn << "ml, add some lemon"
         << endl;
  }
};
struct Coffee : HotDrink {
  void prepare(int volumn) override {
    cout << "Grind some beans, boil water pour " << volumn
         << "ml, add cream, enjoy!" << endl;
  }
};
