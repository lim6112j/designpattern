#pragma once
#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <memory>

struct HotDrink;
struct CoffeeFactory : HotDrinkFactory {
  unique_ptr<HotDrink> make() const override { return make_unique<Coffee>(); }
};
