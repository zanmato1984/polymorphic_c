#include <stdio.h>
#include <stdlib.h>

#define MAX_VFUNC 256

typedef void (*vfunc_t)();
typedef void (*dtor_t)(void *this);

vfunc_t vfunc(void *this, int e) {
  return (*(vfunc_t **)this)[e];
}

enum {
  dtor = 0,
};

void delete(void *this) {
  ((dtor_t)vfunc(this, dtor))(this);
  free(this);
}

vfunc_t base_vtable[MAX_VFUNC];

typedef struct {
  vfunc_t *vptr;
  const char *name;
} base;

void base_ctor(base *this) {
  this->vptr = base_vtable;
  this->name = NULL;
}

base *new_base() {
  base *this = malloc(sizeof(base));
  base_ctor(this);
  return this;
}

void base_dtor(base *this) {
}

enum {
  get_name = dtor + 1,
  say_hello,
};

typedef const char *(*get_name_t)(base *this);

typedef void (*say_hello_t)(base *this);

const char *base_get_name(base *this) {
  return "base";
}

void base_say_hello(base *this) {
  printf("Hello, I'm %s.\n", ((get_name_t)vfunc(this, get_name))(this));
}

void register_base(vfunc_t *vtable) {
  vtable[dtor] = (vfunc_t)base_dtor;
  vtable[get_name] = (vfunc_t)base_get_name;
  vtable[say_hello] = (vfunc_t)base_say_hello;
}

vfunc_t derived_vtable[MAX_VFUNC];

typedef struct {
  base parent;
} derived;

void derived_ctor(derived *this) {
  base_ctor((base *)this);
  this->parent.vptr = derived_vtable;
}

derived *new_derived() {
  derived *this = malloc(sizeof(derived));
  derived_ctor(this);
  return this;
}

void derived_dtor(derived *this) {
  base_dtor((base *)this);
}

enum {
  set_name = say_hello + 1,
};

typedef void (*set_name_t)(derived *this, const char *name);

const char *derived_get_name(derived *this) {
  if (this->parent.name == NULL) {
    return "derived";
  }
  return this->parent.name;
}

void derived_set_name(derived *this, const char *name) {
  this->parent.name = name;
}

void register_derived(vfunc_t *vtable) {
  register_base(vtable);
  vtable[dtor] = (vfunc_t)derived_dtor;
  vtable[get_name] = (vfunc_t)derived_get_name;
  vtable[set_name] = (vfunc_t)derived_set_name;
}

int main() {
  register_base(base_vtable);
  register_derived(derived_vtable);

  base *b = new_base();
  derived *d = new_derived();
  base *bd = (base *)d;

  ((say_hello_t)vfunc(b, say_hello))(b);
  ((say_hello_t)vfunc(bd, say_hello))(bd);
  ((set_name_t)vfunc(d, set_name))(d, "renamed");
  ((say_hello_t)vfunc(bd, say_hello))(bd);
  ((say_hello_t)vfunc(d, say_hello))((base *)d);

  delete(b);
  delete(bd);

  return 0;
}
