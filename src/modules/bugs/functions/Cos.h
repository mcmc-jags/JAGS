#ifndef FUNC_COS_H_
#define FUNC_COS_H_

#include <function/ScalarFunc.h>

namespace bugs {

    /**
     * @short Cosine function
     * @see Sin
     * <pre>
     * y <- cos(x)
     * </pre>
     */
    class Cos : public ScalarFunc
    {
    public:
	Cos ();
	double evaluateScalar(std::vector<double const *> const &args) const;
    };

}

#endif /* FUNC_COS_H_ */