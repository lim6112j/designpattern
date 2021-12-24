#include "pimpl.h"

template <typename T> pimpl<T>::pimpl() : impl { new T{}; }
{}
template <typename T> pimpl<T>::~pimpl() {}
