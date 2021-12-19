#include <iostream>
using namespace std;
class Rectangle {
protected:
  int width, height;

public:
  Rectangle(int width, int height) : width(width), height(height) {}
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  void setWidth(int width) { Rectangle::width = width; }
  void setHeight(int height) { Rectangle::height = height; }
  int area() const { return width * height; }
};
void process(Rectangle &r) {
  int w = r.getWidth();
  r.setHeight(10);
  cout << "expected area" << (w * 10) << " got area " << r.area() << endl;
}
int main() {
  auto r = Rectangle(5, 20);
  process(r);
  return 0;
}
