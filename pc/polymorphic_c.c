#include "polymorphic_c.h"
#include <stdarg.h>

void __object_ctor(object *this) {
  this->__vptr = __object_vtable;
}

void __object_dtor(object *this) {
}

void __register_object_vfuncs(__vfunc_t vtable[]) {
  __object_vtable[dtor] = __object_dtor;
}

void __register_vfuncs(__vfunc_t vtable[], ...) {
  va_list args;
  va_start(args, vtable);
  int e = va_arg(args, int);
  while (e != MAX_VFUNC) {
    vtable[e] = va_arg(args, __vfunc_t);
    e = va_arg(args, int);
  }
  va_end(args);
}

void __register_classes(int dummy, ...)
{
  va_list args;
  va_start(args, dummy);
  __register_class_func_t f = va_arg(args, __register_class_func_t);
  while (f != (__register_class_func_t)NULL) {
    f();
    f = va_arg(args, __register_class_func_t);
  }
  va_end(args);
}

void delete(object *p)
{
  VFUNC_CALL(p, dtor);
  free(p);
}
