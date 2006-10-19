#include <config.h>
#include "ILogit.h"

#include <cmath>
#include <cfloat>

#include <JRmath.h>

using std::vector;

ILogit::ILogit ():InverseLinkFunc ("ilogit", "logit")
{
}

double
ILogit::eval (vector<double const *> const &args) const
{
  /* Returning 0 or 1 can cause numerical problems. A result
     of 0 or 1 may just be the result of numerical imprecision.
     What we really want to return is e  or (1 - e) for very
     small e */

  double q = *args[0];
  double y = exp (-q);
  if (!R_FINITE (y)) {
    return DBL_EPSILON;
  }
  else {
    double p =  1 / (1 + y);
    return p == 1 ? 1 - DBL_EPSILON : p;
  }
}

double ILogit::link(double mu) const
{
  return log(mu) - log(1- mu);
}

double ILogit::gradLink(double mu) const
{
  return 1/(mu*(1-mu));
}
