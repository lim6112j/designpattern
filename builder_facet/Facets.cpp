#include "Person.h"
int main__() {
  Person p = Person::create()
                 .lives()
                 .at("123 road")
                 .with_postcode("2323")
                 .in("london")
                 .works()
                 .at("pramasoft")
                 .as_a("consultant")
                 .earning(10e6);
  cout << p << endl;
  getchar();
  return 0;
}
