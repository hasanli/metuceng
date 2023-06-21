#include "type.h"
#include "nullary.h"

namespace sym 
{
	double Const::get_value() const { }
	Const::operator double() const { }

	bool Const::is_con() const { }

	__expr_t* Const::eval(const var_map_t& var_map) const { }

	__expr_t* Const::diff(const std::string& v) const { }

	std::ostream& Const::operator<< (std::ostream &out) const { }

	bool Const::operator==(const __expr_t& other) const { }
}

namespace sym 
{
	std::string Var::get_variable() const { }
	Var::operator std::string () const { }
	
	bool Var::is_var() const { }

	__expr_t* Var::eval(const var_map_t& vars) const { }

	__expr_t* Var::diff(const std::string& v) const { }
	
	std::ostream& Var::operator<< (std::ostream &out) const { }

	bool Var::operator==(const __expr_t& other) const { }
}
