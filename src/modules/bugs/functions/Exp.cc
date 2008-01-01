#include <config.h>
#include "Exp.h"

#include <cmath>

using std::vector;
using std::exp;
using std::log;

namespace bugs {

    Exp::Exp ()
	: InverseLinkFunc ("exp", "log")
    {
    }

    double Exp::evaluateScalar(vector<double const *> const &args) const
    {
	return exp(*args[0]);
    }

    double Exp::link(double mu) const
    {
	return log(mu);
    }

    double Exp::gradLink(double mu) const
    {
	return 1/mu;
    }

}