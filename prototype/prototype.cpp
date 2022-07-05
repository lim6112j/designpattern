#include <iostream>
using namespace std;
struct Address {
  string street, city;
  int suite;
  Address(const string &street, const string &city, int suite)
      : street(street), city(city), suite(suite) {}
  Address(const Address &address)
      : street(address.street), city(address.city), suite(address.suite) {}
  friend ostream &operator<<(ostream &os, const Address &address) {
    os << "street : " << address.street << " city : " << address.city
       << " suite : " << address.suite;
    return os;
  }
};

struct Contact {
  string name;
  Address *address;
  Contact(const string &name, Address *address)
      : name(name), address(address) {}
  Contact(const Contact &other)
      : name(other.name), address(new Address{*other.address}) {}
  friend ostream &operator<<(ostream &os, const Contact &contact) {
    os << "name: " << contact.name << " address : " << *contact.address;
    return os;
  }
};
int main() {
  Contact john{"john", new Address{"garosu", "seoul", 3}};
  Contact jane = john; // shallow copy
  // Contact john{jane};
  jane.name = "jane smith";
  jane.address->suite = 103;
  cout << john << endl << jane << endl;
  delete jane.address;
  return 0;
}
