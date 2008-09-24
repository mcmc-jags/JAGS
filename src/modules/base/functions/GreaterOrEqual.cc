#include <config.h>
#include "GreaterOrEqual.h"

#include <cmath>
#include <cfloat>

using std::vector;

namespace base {

GreaterOrEqual::GreaterOrEqual () : Infix (">=")
{
}

double GreaterOrEqual::evaluateScalar(vector<double const *> const &args) const
{
  return *args[0] >= *args[1];
}

bool GreaterOrEqual::isDiscreteValued(std::vector<bool> const &mask) const
{
  return true;
}

}