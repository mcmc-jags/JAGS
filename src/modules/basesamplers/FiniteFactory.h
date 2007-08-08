#ifndef FINITE_FACTORY_H_
#define FINITE_FACTORY_H_

#include <sampler/SingletonFactory.h>
class StochasticNode;
class Graph;

namespace basesamplers {

/**
 * @short Factory object for finite samplers
 */
    class FiniteFactory : public SingletonFactory {
    public:
	bool canSample(StochasticNode *snode, Graph const &graph) const;
	Sampler *makeSingletonSampler(StochasticNode *snode, Graph const &graph,
				      unsigned int nchain) const;
    };

}

#endif /* FINITE_FACTORY_H_ */
