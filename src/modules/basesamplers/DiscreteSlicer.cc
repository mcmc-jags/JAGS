#include <config.h>
#include <graph/StochasticNode.h>
#include <graph/NodeError.h>
#include <distribution/Distribution.h>
#include <sampler/ParallelDensitySampler.h>

#include "DiscreteSlicer.h"

#include <cmath>
#include <stdexcept>

using std::floor;
using std::vector;
using std::logic_error;

namespace basesamplers {

    DiscreteSlicer::DiscreteSlicer(StochasticNode const *node, 
				   unsigned int chain, double width, 
				   long ndoubles)
	: Slicer(width, ndoubles), _x(0)
    {
	if (!canSample(node)) {
	    throw logic_error("Invalid DiscreteSlicer");
	}

	_x = node->value(chain)[0];
    }

    bool DiscreteSlicer::canSample(StochasticNode const *node)
    {
	if (!node->isDiscreteValued() || node->length() != 1)
	    return false;
	
	if (df(node) == 0)
	    return false;
	
	return true;
    }

    void DiscreteSlicer::setValue(double x)
    {
	_x = x;
	x = floor(x);
	_sampler->setValue(&x, 1, _chain);
    }
  
    double DiscreteSlicer::value() const
    {
	return _x;
    }

    void DiscreteSlicer::getLimits(double *lower, double *upper) const
    {
	StochasticNode const *snode = _sampler->nodes().front();
	support(lower, upper, 1, snode, _chain);
	*upper += 1;
    }

    void DiscreteSlicer::update(RNG *rng)
    {
	updateDouble(rng);
    }

    string name() const
    {
	return "Discrete Slice Method";
    }

}