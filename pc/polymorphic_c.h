#include <stdlib.h>
#include <string.h>

#define MAX_VFUNC 256

// virtual function type
typedef void (*__vfunc_t)();

// single inheritance root class object
__vfunc_t __object_vtable[1];

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

// vtable manipulation functions
void __register_vfuncs(__vfunc_t vtable[], ...);

// universal object delete function
void delete(object *p);

// macros to define classes
#define BEGIN_DEF_CLASS(c, p) \
  __vfunc_t __##c##_vtable[MAX_VFUNC]; \
  typedef struct { \
    p parent;

#define END_DEF_CLASS(c, p) \
  } c; \
  void __##c##_ctor_internal(c *this); \
  void __##c##_ctor(c *this) { \
    __##p##_ctor((p *)this); \
    __##c##_ctor_internal(this); \
    *(__vfunc_t **)this = __##c##_vtable; \
  } \
  c *new_##c() { \
    c *this = malloc(sizeof(c)); \
    memset(this, 0, sizeof(c)); \
    __##c##_ctor(this); \
    return this; \
  } \
  void __##c##_dtor_internal(c *this); \
  void __##c##_dtor(c *this) { \
    __##c##_dtor_internal(this); \
    __##p##_dtor((p *)this); \
  }

#define __VFUNC_NAME(c, f) \
  __##c##_##f

#define __VFUNC_TYPE_NAME(f) \
  __##f##_t

// macros to define constructor and destructor
#define DEF_CTOR(c) \
  void __##c##_ctor_internal(c *this)

#define DEF_DTOR(c) \
  void __##c##_dtor_internal(c *this)

// macro to reference a vfunc when registering
#define VFUNC_REF(c, f) \
  __VFUNC_NAME(c, f)

// macros to define virtual functions
#define OVERRIDE_VFUNC(r, c, f, ...) \
  r __VFUNC_NAME(c, f)(c *this, ##__VA_ARGS__)

#define DEF_VFUNC(r, c, f, ...) \
  typedef r (*__VFUNC_TYPE_NAME(f))(c *this, ##__VA_ARGS__); \
  OVERRIDE_VFUNC(r, c, f, ##__VA_ARGS__)

// macro to declare subclass-only virtual functions
#define DECL_CLASS_VFUNCS(c, p, ...) \
  enum { \
    __##c##_first_vfunc = __##p##_last_vfunc, \
    ##__VA_ARGS__, \
    __##c##_last_vfunc, \
  };

#define __REGISTER_CLASS_FUNC_NAME(c) \
  __register_##c

// macro to reference a class when registering
#define CLASS_REF(c) \
  __REGISTER_CLASS_FUNC_NAME(c)

// macro to register subclass-implemented (new or overriden) virtual functions
#define REGISTER_CLASS_VFUNCS(c, p, ...) \
  void __register_##c##_vfuncs(__vfunc_t vtable[]) { \
    __register_##p##_vfuncs(vtable); \
    __register_vfuncs(vtable, ##__VA_ARGS__, dtor, __##c##_dtor, MAX_VFUNC); \
  } \
  void __REGISTER_CLASS_FUNC_NAME(c)() { \
    __register_##c##_vfuncs(__##c##_vtable); \
  }

// class virtual function registering macros
typedef void (*__register_class_func_t)();

void __register_classes(int dummy, ...);

#define REGISTER_CLASSES(...) \
  void polymorphic_c_init() { \
    __register_classes(0, ##__VA_ARGS__, NULL); \
  }

#define VFUNC_CALL(this, f, ...) \
  ((__VFUNC_TYPE_NAME(f))(*(__vfunc_t **)this)[f])(this, ##__VA_ARGS__)
