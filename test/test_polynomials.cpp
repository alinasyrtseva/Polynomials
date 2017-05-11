#include "Polynomials.h"

#include <gtest/gtest.h>

char* exp1  = "-2.5*x^2y^2z^2+2.5*x^2y^2z^2-3*x^3y^3z^3";
char* expr2  = "3*x^3y^3z^3";
char* exp3  = "3*x^7y^7z^7";
Polynomial poly1 = Polynomial (exp1);
Polynomial poly2 = Polynomial (expr2);
Polynomial poly3 = Polynomial (exp3);

char * _add = "0";
char * _sub = "-6*x^3y^3z^3";
char * _mul = "-9*x^6y^6z^6";
Polynomial add /*= Polynomial (_add)*/;
Polynomial sub = Polynomial (_sub);
Polynomial mul = Polynomial (_mul);

TEST (Polynomial, can_create_poly)
{
	ASSERT_NO_THROW (Polynomial poly);
}

TEST (Polynomial, can_create_not_empty_poly) 
{
	ASSERT_NO_THROW (Polynomial (exp1));
}

TEST (Polynomial, can_add) 
{
	Polynomial res = poly1 + poly2;

	EXPECT_EQ (res, add);
}

TEST (Polynomial, can_sub) 
{
	Polynomial res = poly1 - poly2;

	ASSERT_TRUE (res == sub);
}

TEST (Polynomial, can_multi) 
{
	Polynomial res = poly1 * poly2;

	ASSERT_TRUE (res == mul);
}


TEST (Polynomial, throws_when_multiply_the_polynomials_with_large_exponents)
{
	ASSERT_ANY_THROW (poly2 * poly3);
}
