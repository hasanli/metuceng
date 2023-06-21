#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const { }

	__expr_t* NegOp::eval(const var_map_t& vars) const { }

	__expr_t* NegOp::diff(const std::string& v) const { }

	std::ostream& NegOp::operator<< (std::ostream &out) const { }

	bool NegOp::operator==(const __expr_t& other_) const { }
}

namespace sym 
{
	bool ExpOp::is_exp() const { }

	__expr_t* ExpOp::eval(const var_map_t& vars) const { }

	__expr_t* ExpOp::diff(const std::string& v) const { }

	std::ostream& ExpOp::operator<< (std::ostream &out) const { }

	bool ExpOp::operator==(const __expr_t& other_) const { }
}
