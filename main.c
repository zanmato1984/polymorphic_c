#include "polymorphic_c.h"

#include <stdio.h>

BEGIN_DEF_CLASS(A)
int a;
END_DEF_CLASS(A)

DEF_VFUNC(A, int, get_a)
{
	return this->a;
}

DEF_VFUNC(A, void, set_a, int a)
{
	this->a = a;
}

DECL_CLASS_VFUNCS(A, get_a, set_a)
DEF_CLASS_VFUNCS(A, 2, get_a, A_get_a, set_a, A_set_a)

BEGIN_DEF_SUBCLASS(B, A)
int b;
END_DEF_SUBCLASS(B, A)

DEF_VFUNC(B, int, get_a)
{
	return this->b;
}

DEF_VFUNC(B, void, set_a, int a)
{
	this->b = a;
}

DEF_VFUNC(B, int, get_b)
{
	return this->b;
}

DEF_VFUNC(B, void, set_b, int b)
{
	this->b = b;
}

DECL_SUBCLASS_VFUNCS(B, A, get_b, set_b)
DEF_SUBCLASS_VFUNCS(B, A, 4, get_a, B_get_a, set_a, B_set_a, get_b, B_get_b, set_b, B_set_b)

DEF_CLASSES(2, def_class_A, def_class_B)

int main()
{
	polymorphic_c_init();

	A *a1 = new_A();
	printf("a1's a is %d.\n", VFUNC_CALL(a1, get_a));

	B *b = new_B();
	A *a2 = b;
	VFUNC_CALL(a2, set_a, 1);
	printf("a2's a is %d.\n", VFUNC_CALL(a2, get_a));
	VFUNC_CALL(b, set_b, 2);
	printf("b's b is %d.\n", VFUNC_CALL(b, get_b));
	printf("a2's a is %d.\n", VFUNC_CALL(a2, get_a));
	return 0;
}