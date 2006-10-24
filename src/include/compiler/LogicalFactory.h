#ifndef LOGICAL_FACTORY_H_
#define LOGICAL_FACTORY_H_

#include <graph/Graph.h>
#include <graph/Node.h>
#include <sarray/SArray.h>

#include <vector>
#include <utility>
#include <map>
#include <cfloat>

class Function;
class LogicalNode;

/**
 * A "logical pair", consisting of a function and a vector of arguments,
 * uniquely defines a logical node.
 */
typedef std::pair<Function const*,std::vector<Node const *> > LogicalPair;
/**
 * "Less than" operator for LogicalPairs. Two LogicalPairs A and B are
 * considered to be equivalent (i.e. lt(A,B) and lt(B,A) are both
 * false) if they have the same function, the parameter vectors are
 * the same length, and an element-wise call to equal (NodeFactory.h)
 * returns true.
 *
 * For non-equivalent LogicalPairs, the ordering is unique, but 
 * arbitrary. The only use of this function is for the STL map class
 * with LogicalPair as key.
 */
bool lt(LogicalPair const &arg1, LogicalPair const &arg2);
/**
 * Function object for the STL map class using LogicalPair as a key
 */
struct ltlogical
{
  bool operator()(LogicalPair const &arg1, LogicalPair const &arg2)
  {
    return lt(arg1, arg2);
  }
};

/**
 * @short Factory object for logical nodes 
 * The value of a logical node is determined uniquely by its function
 * and its parameters.  The purpose of a LogicalFactory is to avoid
 * unnecessary duplication of logical nodes by having a container
 * class and factory object for them that will create and/or lookup
 * logical nodes based on the function and the parameter vector
 */
class LogicalFactory 
{ 
  std::map<LogicalPair, LogicalNode*, ltlogical> _logicalmap;
	
public:
  /**
   * Get a logical node with a given function and given parameters.
   * The results are cached, so if a request is repeated, the same
   * node will be returned. If a newly allocated node is returned,
   * it is also added to the given Graph.
   */
  LogicalNode *getLogicalNode(Function const *func, 
			      std::vector<Node const*> const &param,
                              Graph &graph);
};

#endif /* LOGICAL_FACTORY_H_ */
