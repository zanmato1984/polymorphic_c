#define MAX_VFUNC 256

typedef void(*vfunc)();

#define BEGIN_DEF_SUBCLASS(c, p) \
  vfunc c##_vtable[MAX_VFUNC]; \
  typedef struct \
  { \
  void (**vptr)(); \
    p parent;

#define END_DEF_SUBCLASS(c, p) \
  } c; \
  void construct_##c(c *o) \
  { \
    construct_##p(&o->parent); \
    o->vptr = c##_vtable; \
  } \
  c *new_##c() \
  { \
    c *o = malloc(sizeof(c)); \
    memset(o, 0, sizeof(c)); \
    construct_##c(o); \
    return o; \
  }

#define BEGIN_DEF_CLASS(c) \
  vfunc c##_vtable[MAX_VFUNC]; \
  typedef struct \
  { \
  void (**vptr)();

#define END_DEF_CLASS(c) \
  } c; \
  void construct_##c(c *o) \
  { \
    o->vptr = c##_vtable; \
  } \
  c *new_##c() \
  { \
    c *o = malloc(sizeof(c)); \
    memset(o, 0, sizeof(c)); \
    construct_##c(o); \
    return o; \
  }

#define DEF_VFUNC_NO_PARAM(c, r, f) \
  typedef r (*f##_t)(c *this); \
  r c##_##f(c *this)

#define DEF_VFUNC(c, r, f, ...) \
  typedef r (*f##_t)(c *this, __VA_ARGS__); \
  r c##_##f(c *this, __VA_ARGS__)

#define OVERRIDE_VFUNC_NO_PARAM(c, r, f) \
  r c##_##f(c *this)

#define OVERRIDE_VFUNC(c, r, f, ...) \
  r c##_##f(c *this, __VA_ARGS__)

void init_vtable(vfunc vtable[], int size, ...);

typedef void(*def_class)();

#define DECL_SUBCLASS_VFUNCS(c, p, ...) \
  enum c##_vfuncs \
  { \
    c##_first_vfunc = p##_last_vfunc, \
    __VA_ARGS__, \
    c##_last_vfunc, \
  }; \

#define DEF_SUBCLASS_VFUNCS(c, p, ...) \
  void def_class_##c##_vfuncs(vfunc vtable[]) \
  { \
    def_class_##p##_vfuncs(vtable); \
    init_vtable(vtable, __VA_ARGS__); \
  } \
  void def_class_##c() \
  { \
    def_class_##c##_vfuncs(c##_vtable); \
  }

#define DECL_CLASS_VFUNCS(c, ...) \
  enum c##_vfuncs \
  { \
    c##_first_vfunc = 0, \
    __VA_ARGS__, \
    c##_last_vfunc, \
  }; \

#define DEF_CLASS_VFUNCS(c, ...) \
  void def_class_##c##_vfuncs(vfunc vtable[]) \
  { \
    init_vtable(vtable, __VA_ARGS__); \
  } \
  void def_class_##c() \
  { \
    def_class_##c##_vfuncs(c##_vtable); \
  }

void def_classes(int size, ...);

#define DEF_CLASSES(...) \
  void polymorphic_c_init() \
  { \
    def_classes(__VA_ARGS__); \
  }

#define VFUNC_CALL_NO_PARAM(p, f) \
  ((f##_t)(p->vptr[f]))(p)

#define VFUNC_CALL(p, f, ...) \
  ((f##_t)(p->vptr[f]))(p, __VA_ARGS__)

#define PARENT_VFUNC_CALL(p, f) \
  ((f##_t)(p->parent.vptr[fn]))(p)

#define PARENT_VFUNC_CALL(p, f, ...) \
  ((f##_t)(p->parent.vptr[fn]))(p, __VA_ARGS__)
