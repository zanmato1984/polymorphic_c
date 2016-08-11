#include "polymorphic_c.h"

#include <stdio.h>

BEGIN_DEF_CLASS(base, object)
END_DEF_CLASS(base, object)

DECL_CLASS_VFUNCS(base, object,
    get_name,
    say_hello)

DEF_VFUNC(base, const char *, get_name)
{
  return "base";
}

DEF_VFUNC(base, void, say_hello)
{
  printf("Hello, I'm %s.\n", VFUNC_CALL(this, get_name));
}

REGISTER_CLASS_VFUNCS(base, object, 2,
    get_name, VFUNC_REF(base, get_name),
    say_hello, VFUNC_REF(base, say_hello))

BEGIN_DEF_CLASS(derived, base)
  char *name;
END_DEF_CLASS(derived, base)

DECL_CLASS_VFUNCS(derived, base,
    set_name)

OVERRIDE_VFUNC(derived, const char *, get_name)
{
  if (this->name == NULL)
  {
    return "derived";
  }
  return this->name;
}

DEF_VFUNC(derived, void, set_name, char *name)
{
  this->name = name;
}

REGISTER_CLASS_VFUNCS(derived, base, 2,
    get_name, VFUNC_REF(derived, get_name),
    set_name, VFUNC_REF(derived, set_name))

REGISTER_CLASSES(2,
    CLASS_REF(base),
    CLASS_REF(derived))

int main()
{
  polymorphic_c_init();

  base *b = new_base();
  derived *d = new_derived();
  base *bd = d;

  VFUNC_CALL(b, say_hello);
  VFUNC_CALL(bd, say_hello);
  VFUNC_CALL(d, set_name, "renamed");
  VFUNC_CALL(bd, say_hello);
  VFUNC_CALL(d, say_hello);

  delete(b);
  delete(bd);

  return 0;
}
