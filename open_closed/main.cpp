#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace boost;
enum class Color { red, green, blue };
enum class Size { small, medium, large };
struct Product {
  string name;
  Color color;
  Size size;
};
struct ProductFilter {
  vector<Product *> by_color(vector<Product *> items, Color color) {
    vector<Product *> result;
    for (auto &i : items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }
  vector<Product *> by_size(vector<Product *> items, Size size) {
    vector<Product *> result;
    for (auto &i : items)
      if (i->size == size)
        result.push_back(i);
    return result;
  }
  vector<Product *> by_size_color(vector<Product *> items, Color color,
                                  Size size) {
    vector<Product *> result;
    for (auto &i : items)
      if (i->size == size && i->color == color)
        result.push_back(i);
    return result;
  }
};

int main(int argc, char *argv[]) {
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::red, Size::large};
  vector<Product *> items{&apple, &tree, &house};
  ProductFilter pf;
  auto green_things = pf.by_size_color(items, Color::green, Size::large);
  for (auto &item : green_things)
    cout << item->name << " is green\n";
  return 0;
}
