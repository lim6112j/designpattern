#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

enum class PointType { cartesian, polar };
class Point {
  Point(const float x, const float y) : x(x), y(y) {}

public:
  float x, y;
  friend std::ostream &operator<<(std::ostream &os, const Point &obj) {
    return os << "x: " << obj.x << " y: " << obj.y;
  }
  static Point NewCartesian(float x, float y) { return {x, y}; }
  static Point NewPolar(float r, float theta) {
    return {static_cast<float>(r * cos(theta)),
            static_cast<float>(r * sin(theta))};
  }
};
int main() {
  auto p = Point::NewPolar(5, M_PI_4);
  std::cout << p << std::endl;
  std::getchar();
  return 0;
}
