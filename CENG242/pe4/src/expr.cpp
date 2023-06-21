#include "expr.h"

namespace sym 
{
	Expr::Expr(const Const& c) { }
	Expr::Expr(const Var& v) { }
	Expr::Expr(const __expr_t* e) { }
	Expr::Expr(const __expr_t& e) { }
	Expr::Expr(const Expr& e) { }
		
	Expr::~Expr() { }

	__expr_t* Expr::eval(const var_map_t& var_map) const { }
	__expr_t* Expr::diff(const std::string& v) const { }
	std::ostream& Expr::operator<< (std::ostream &out) const { }
	bool Expr::operator==(const Expr& other) const { }
	bool Expr::operator==(const __expr_t& other) const { }
}                                                                   	
