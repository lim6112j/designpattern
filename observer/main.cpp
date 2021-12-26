#include "Observable.hpp"
#include "Observer.hpp"
#include "SafeObservable.hpp"
#include <boost/signals2.hpp>
#include <iostream>
#include <string>
using namespace std;
class Person : public Observable<Person> { // observable
  int age;

public:
  Person(){};
  Person(int age) : age(age) {}
  int get_age() { return age; }
  void set_age(int age) {
    //     Person::age = age;
    if (this->age == age)
      return;
    auto old_can_vote = get_can_vote();
    this->age = age;
    notify(*this, "age");
    if (old_can_vote != get_can_vote())
      notify(*this, "can_vote");
  }
  bool get_can_vote() const { return age >= 16; }
};
class SafePerson : public SafeObservable<SafePerson> { // observable
  int age;

public:
  SafePerson(){};
  SafePerson(int age) : age(age) {}
  int get_age() { return age; }
  void set_age(int age) {
    //     Person::age = age;
    if (this->age == age)
      return;
    auto old_can_vote = get_can_vote();
    this->age = age;
    notify(*this, "age");
    if (old_can_vote != get_can_vote())
      notify(*this, "can_vote");
  }
  bool get_can_vote() const { return age >= 16; }
};
// observer & observable
struct ConsolePersonObserver : public Observer<Person> {
  void field_changed(Person &source, const std::string &field_name) override {
    cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age")
      cout << source.get_age();
    if (field_name == "can_vote")
      cout << boolalpha << source.get_can_vote();
    cout << "\n.";
  }
};
struct ConsoleSafePersonObserver : public Observer<SafePerson> {
  void field_changed(SafePerson &source,
                     const std::string &field_name) override {
    cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age")
      cout << source.get_age();
    if (field_name == "can_vote")
      cout << boolalpha << source.get_can_vote();
    cout << "\n.";
  }
};
// using boost signal
template <typename T> struct Observable2 {
  boost::signals2::signal<void(T &, const string &)> field_changed;
};
class Person2 : public Observable2<Person2> {
  int age;

public:
  Person2(){};
  Person2(int age){};
  int get_age() { return age; }
  void set_age(int age) {
    if (this->age == age)
      return;
    this->age = age;
    field_changed(*this, "age");
  };
};
int main() {
  Person person;
  ConsolePersonObserver cpo;
  person.subscribe(cpo);
  person.set_age(20);
  person.set_age(11);
  person.unsubscribe(cpo);
  person.set_age(69);

  // using boost signal
  Person2 p2;
  auto conn =
      p2.field_changed.connect([](Person2 &p, const string &field_name) {
        cout << field_name << " has changed to " << p.get_age() << "\n";
      });
  conn.connected();
  p2.set_age(20);
  p2.set_age(55);
  conn.disconnect();
  p2.set_age(65);
  ConsoleSafePersonObserver cspo;
  SafePerson p3;
  p3.subscribe(cspo);
  p3.set_age(12);
  p3.set_age(20);
  p3.unsubscribe(cspo);
  getchar();
  return 0;
}
