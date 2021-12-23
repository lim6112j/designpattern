#include "Observable.hpp"
#include "Observer.hpp"
#include <boost/signals2.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace boost::signals2;
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
template <typename T> struct Observable2 {
  boost::signals2::signal<void(T &, const string &)> field_changed;
};
class Person2 : public Observable2<Person2> {
  int age;

public:
  Person2(int age) {}
  int get_age() { return age; }
  void set_age(int age) {
    if (this->age == age)
      return;
    this->age = age;
    field_changed(*this, "age");
  };
};
int main() {
  Person person(10);
  ConsolePersonObserver cpo;
  person.subscribe(cpo);
  person.set_age(20);
  person.set_age(11);
  person.unsubscribe(cpo);
  person.set_age(69);

  // using boost signal
  Person2 p2(10);
  auto conn =
      p2.field_changed.connect([](Person2 &p, const string &field_name) {
        cout << field_name << " has changed to " << p.get_age() << "\n";
      });
  conn.connected();
  p2.set_age(20);
  p2.set_age(55);
  conn.disconnect();
  p2.set_age(65);
  getchar();
  return 0;
}
