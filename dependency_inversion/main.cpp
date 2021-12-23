#include <iostream>
#include <vector>
using namespace std;
enum class Relationship { parent, child, sibling };
struct Person {
  string name;
};
struct Relationships {
  vector<tuple<Person, Relationship, Person>> relation;
  void add_parent_and_child(const Person &parent, const Person &child) {}
};
int main(int argc, char *argv[]) { return 0; }
