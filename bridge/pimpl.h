#include <memory>
template <typename T> class pimpl {
private:
  pimpl();
  ~pimpl();
  template <typename... Args> pimpl(Args &&...args);
  T *operator->();
  T &operator*();
};
