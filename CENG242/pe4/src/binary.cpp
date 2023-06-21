#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const { }

	__expr_t* AddOp::eval(const var_map_t& vars) const { }

	__expr_t* AddOp::diff(const std::string& v) const { }

	std::ostream& AddOp::operator<< (std::ostream &out) const { }

	bool AddOp::operator==(const __expr_t& other_) const { }
}

namespace sym 
{
	bool MulOp::is_mul() const { }

	__expr_t* MulOp::eval(const var_map_t& vars) const { }

	__expr_t* MulOp::diff(const std::string& v) const { }

	std::ostream& MulOp::operator<< (std::ostream &out) const { }

	bool MulOp::operator==(const __expr_t& other_) const { }
}
