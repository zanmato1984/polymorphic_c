#include <stdlib.h>
#include <string.h>

#define MAX_VFUNC 256

// universal new operator
#define new(c) \
  __##c##_ctor(malloc(sizeof(c)))

// universal delete operator
void delete(void *this);

//// virtual function stuff
typedef void (*__vfunc_t)();

#define __VPTR(this) \
  (*(__vfunc_t **)(this))

#define OVERRIDE_VFUNC(r, c, f, ...) \
  r __VFUNC_NAME(c, f)(c *this, ##__VA_ARGS__)

#define DEF_VFUNC(r, c, f, ...) \
  typedef r (*__VFUNC_TYPE_NAME(f))(c *this, ##__VA_ARGS__); \
  OVERRIDE_VFUNC(r, c, f, ##__VA_ARGS__)

#define VFUNC_CALL(this, f, ...) \
  ((__VFUNC_TYPE_NAME(f))__VPTR(this)[f])(this, ##__VA_ARGS__)
////

//// single inheritance root class 'object' and related stuff.
__vfunc_t __object_vtable[1];

struct object;

typedef struct {
  __vfunc_t *__vptr;
} object;

void __object_ctor(object *this);

typedef void (*__dtor_t)(object *this);

void __object_dtor(object *this);

enum {
  dtor = 0,
  __object_last_vfunc,
};

void __register_object_vfuncs(__vfunc_t vtable[]);
////

//// class define stuff.
#define BEGIN_DEF_CLASS(c, p) \
  __vfunc_t __##c##_vtable[MAX_VFUNC]; \
  typedef struct { \
    p parent;

#define END_DEF_CLASS(c, p) \
  } c; \
  void __##c##_ctor_internal(c *this); \
  c *__##c##_ctor(c *this) { \
    __##p##_ctor((p *)this); \
    __##c##_ctor_internal(this); \
    __VPTR(this) = __##c##_vtable; \
    return this; \
  } \
  void __##c##_dtor_internal(c *this); \
  void __##c##_dtor(c *this) { \
    __##c##_dtor_internal(this); \
    __##p##_dtor((p *)this); \
  }

#define DECL_CLASS_VFUNCS(c, p, ...) \
  enum { \
    __##c##_first_vfunc = __##p##_last_vfunc, \
    ##__VA_ARGS__, \
    __##c##_last_vfunc, \
  };
////

//// constructor and destructor stuff
#define DEF_CTOR(c) \
  void __##c##_ctor_internal(c *this)

#define DEF_DTOR(c) \
  void __##c##_dtor_internal(c *this)
////

//// internal names
#define __VFUNC_NAME(c, f) \
  __##c##_##f

#define __VFUNC_TYPE_NAME(f) \
  __##f##_t

#define __REGISTER_CLASS_FUNC_NAME(c) \
  __register_##c
////

//// virtual function and class referencing stuff
#define VFUNC_REF(c, f) \
  __VFUNC_NAME(c, f)

#define CLASS_REF(c) \
  __REGISTER_CLASS_FUNC_NAME(c)
////

//// virtual function registering stuff.
void __register_vfuncs(__vfunc_t *vtable, ...);

#define REGISTER_CLASS_VFUNCS(c, p, ...) \
  void __register_##c##_vfuncs(__vfunc_t *vtable) { \
    __register_##p##_vfuncs(vtable); \
    __register_vfuncs(vtable, ##__VA_ARGS__, dtor, __##c##_dtor, MAX_VFUNC); \
  } \
  void __REGISTER_CLASS_FUNC_NAME(c)() { \
    __register_##c##_vfuncs(__##c##_vtable); \
  }
////

//// class registering stuff.
typedef void (*__register_class_func_t)();

void __register_classes(int dummy, ...);

#define REGISTER_CLASSES(...) \
  void polymorphic_c_init() { \
    __register_classes(0, ##__VA_ARGS__, NULL); \
  }
////
