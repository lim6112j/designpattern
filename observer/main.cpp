#include "Observable.hpp"
#include "Observer.hpp"
#include <iostream>
#include <string>
using namespace std;
class Person : public Observable<Person> { // observable
  int age;

public:
  Person(int age) : age(age) {}
  int get_age() { return age; }
  void set_age(int age) {
    //     Person::age = age;
    if (this->age == age)
      return;
    this->age = age;
    notify(*this, "age");
  }
};
// observer & observable
struct ConsolePersonObserver : public Observer<Person> {
  void field_changed(Person &source, const std::string &field_name) override {
    cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age")
      cout << source.get_age();
    cout << "\n.";
  }
};
int main() {
  Person person(10);
  ConsolePersonObserver cpo;
  person.subscribe(cpo);
  person.set_age(20);
  getchar();
  return 0;
}
