#include "polymorphic_c.h"

#include <stdio.h>

BEGIN_DEF_CLASS(base)
  int dummy;
END_DEF_CLASS(base)
DECL_CLASS_VFUNCS(base,
    get_name,
    say_hello)

DEF_VFUNC_NO_PARAM(base, const char *, get_name)
{
  return "base";
}

DEF_VFUNC_NO_PARAM(base, void, say_hello)
{
  printf("Hello, I'm %s.\n", VFUNC_CALL_NO_PARAM(this, get_name));
}

DEF_CLASS_VFUNCS(base, 2,
    get_name, base_get_name,
    say_hello, base_say_hello)

BEGIN_DEF_SUBCLASS(derived, base)
  char *name;
END_DEF_SUBCLASS(derived, base)

DECL_SUBCLASS_VFUNCS(derived, base,
    set_name)

OVERRIDE_VFUNC_NO_PARAM(derived, const char *, get_name)
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

DEF_SUBCLASS_VFUNCS(derived, base, 3,
    say_hello, base_say_hello,
    get_name, derived_get_name,
    set_name, derived_set_name)

DEF_CLASSES(2, def_class_base, def_class_derived)

int main()
{
  polymorphic_c_init();

  base *b = new_base();
  VFUNC_CALL_NO_PARAM(b, say_hello);

  derived *d = new_derived();
  base *bd = d;
  VFUNC_CALL_NO_PARAM(bd, say_hello);
  VFUNC_CALL(d, set_name, "renamed");
  VFUNC_CALL_NO_PARAM(bd, say_hello);
  VFUNC_CALL_NO_PARAM(d, say_hello);

  return 0;
}
