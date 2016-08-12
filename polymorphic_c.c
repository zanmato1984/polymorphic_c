#include "polymorphic_c.h"

#include <stdarg.h>

void __object_ctor(object *this)
{
  this->__vptr = __object_vtable;
}

void __object_dtor(object *this)
{
}

void __register_object_vfuncs(__vfunc vtable[])
{
  __object_vtable[dtor] = __object_dtor;
}

void __register_vfuncs(__vfunc vtable[], int dummy, ...)
{
  va_list args;
  va_start(args, dummy);
  int e = va_arg(args, int);
  while (e != BARRIER)
  {
    vtable[e] = va_arg(args, __vfunc);
    e = va_arg(args, int);
  }
  va_end(args);
}

void __register_classes(int dummy, ...)
{
  va_list args;
  va_start(args, dummy);
  __register_class_func f = va_arg(args, __register_class_func);
  while (f != (__register_class_func)BARRIER)
  {
    f();
    f = va_arg(args, __register_class_func);
  }
  va_end(args);
}

void delete(object *p)
{
  VFUNC_CALL(p, dtor);
  free(p);
}

