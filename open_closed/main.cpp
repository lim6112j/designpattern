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
template <typename T> struct AndSpecification;
template <typename T> struct Specification {
  virtual bool is_satisfied(T *item) = 0;
  AndSpecification<T> operator&&(Specification<T> &&other) {
    return AndSpecification<T>(*this, other);
  }
};
template <typename T> struct AndSpecification : Specification<T> {
  Specification<T> &first;
  Specification<T> &second;
  AndSpecification(Specification<T> &first, Specification<T> &second)
      : first(first), second(second) {}
  bool is_satisfied(T *item) override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};
template <typename T> struct Filter {
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};
struct BetterFilter : Filter<Product> {
  vector<Product *> filter(vector<Product *> items,
                           Specification<Product> &spec) override {
    vector<Product *> result;
    for (auto &item : items)
      if (spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};
struct ColorSpec : Specification<Product> {
  Color color;
  explicit ColorSpec(Color color) : color(color) {}
  bool is_satisfied(Product *item) override { return item->color == color; }
};
struct SizeSpec : Specification<Product> {
  Size size;
  explicit SizeSpec(Size size) : size(size) {}
  bool is_satisfied(Product *item) override { return item->size == size; }
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
  BetterFilter bf;
  ColorSpec red(Color::red);
  auto result = bf.filter(items, red);
  for (auto &item : result)
    cout << item->name << " is red\n";
  SizeSpec large(Size::large);
  AndSpecification<Product> green_and_large(red, large);
  auto result2 = bf.filter(items, green_and_large);
  for (auto &item : result2)
    cout << item->name << " is filtered\n";
  auto spec = ColorSpec(Color::green) && SizeSpec(Size::small);
  for (auto &item : bf.filter(items, spec))
    cout << item->name << " is green and large\n";

  return 0;
}
