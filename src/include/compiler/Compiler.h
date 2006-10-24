#ifndef COMPILER_H_
#define COMPILER_H_

#include <compiler/LogicalFactory.h>
#include <compiler/ConstantFactory.h>
#include <compiler/MixtureFactory.h>
#include <compiler/CounterTab.h>
#include <distribution/DistTab.h>
#include <function/FuncTab.h>
#include <model/BUGSModel.h>

#include <map>
#include <string>
#include <utility>
#include <list>

class ParseTree;
class Graph;
class SymTab;
class FuncTab;
class DistTab;
class NodeAlias;

class Compiler;
typedef void (Compiler::*CompilerMemFn) (ParseTree const *);

class Compiler {
  BUGSModel &_model;
  CounterTab _countertab;
  std::map<std::string, SArray> const &_data_table;
  std::map<std::string, std::vector<bool> > _constant_mask;
  unsigned int _n_resolved, _n_relations;
  bool *_is_resolved;
  bool _strict_resolution;
  ConstantFactory _constantfactory;
  LogicalFactory _logicalfactory;
  MixtureFactory _mixfactory;
  std::map<std::string, std::vector<std::vector<int> > > _node_array_ranges;

  Node *getArraySubset(ParseTree const *t);
  bool constantExpression(ParseTree const *p, double &value);
  Range VariableSubsetRange(ParseTree const *var);
  Range CounterRange(ParseTree const *var);
  Node* VarGetNode(ParseTree const *var);
  Range getRange(ParseTree const *var,  Range const &default_range);;

  void traverseTree(ParseTree const *relations, CompilerMemFn fun,
		    bool resetcounter=true);
  void allocate(ParseTree const *rel);
  Node * allocateStochastic(ParseTree const *stoch_rel);
  Node * allocateLogical(ParseTree const *dtrm_rel);
  void setConstantMask(ParseTree const *rel);
  void writeConstantData(ParseTree const *rel);
  void writeVariableData();
  void getArrayDim(ParseTree const *p);
  bool getLogicalParameterVector(ParseTree const *t,
			      std::vector<Node const *> &parents);
  Node * getSubSetNode(ParseTree const *var);
  double constFromTable(ParseTree const *p);
  double constFromNode(ParseTree const *p);
  void addDevianceNode();
public:
  bool indexExpression(ParseTree const *t, int &value);
  MixtureFactory &mixtureFactory();
  BUGSModel &model() const;
  Node* getParameter(ParseTree const *t);
  /**
   * Constructor
   * @param model To be created by the compiler.
   * @param datatab Data table. This is required since some constant
   * expressions in the BUGS language may depend on data values.
   */
  Compiler(BUGSModel &model, std::map<std::string, SArray> const &data_table);
  void declareVariables(std::vector<ParseTree*> const &pvariables);
  /**
   * Adds variables without an explicit declaration to the symbol
   * table.  Variables supplied in the data table are added, then
   * any variables that appear on the left hand side of a relation
   */
  void undeclaredVariables(ParseTree const *prelations);
  /**
   * Traverses the ParseTree creating nodes.
   */
  void writeRelations(ParseTree const *prelations);
  /** 
   * The function table used by the compiler to look up functions by
   * name.  It is shared by all Compiler objects.
   */
  static FuncTab &funcTab();
  /** 
   * The distribution table used by the compiler to look up
   * distributions by name.  It is shared by all Compiler objects.
   */
  static DistTab &distTab();
};


#endif /* COMPILER_H_ */

