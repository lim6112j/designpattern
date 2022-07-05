struct Point {
  int x{0}, y{0};

  Point() {}

  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line {
  Point *start, *end;

  Line(Point *const start, Point *const end) : start(start), end(end) {}

  ~Line() {
    delete start;
    delete end;
  }

  Line deep_copy() const {
    Line line{new Point(this->start->x, this->start->y),
              new Point(this->end->x, this->end->y)};
    return line;
  }
};
