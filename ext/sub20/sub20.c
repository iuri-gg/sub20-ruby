#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ruby.h"
#include "libsub.h"

static VALUE s_init(VALUE self)
{
  VALUE arr;

  arr = rb_ary_new();
  rb_iv_set(self, "@arr", arr);
  return self;
}

static VALUE s_add(VALUE self, VALUE anObject)
{
  VALUE arr;

  arr = rb_iv_get(self, "@arr");
  rb_ary_push(arr, anObject);
  return arr;
}

VALUE cSub20;

void Init_sub20() {
  cSub20 = rb_define_class("Sub20", rb_cObject);
  rb_define_method(cSub20, "initialize", s_init, 0);
  rb_define_method(cSub20, "add", s_add, 1);
}