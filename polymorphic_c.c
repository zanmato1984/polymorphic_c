#include "polymorphic_c.h"

#include <stdarg.h>

void init_vtable(vfunc vtable[], int size, ...)
{
  va_list args;
  va_start(args, size);
  for (int i = 0; i < size; i++)
  {
    int e = va_arg(args, int);
    vtable[e] = va_arg(args, vfunc);
  }
  va_end(args);
}

void def_classes(int size, ...)
{
  va_list args;
  va_start(args, size);
  for (int i = 0; i < size; i++)
  {
    def_class f = va_arg(args, def_class);
    f();
  }
  va_end(args);
}
