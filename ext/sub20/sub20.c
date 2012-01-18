#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libusb.h>

#include "ruby.h"
#include "libsub.h"


VALUE cSub20;

static VALUE s_init(VALUE self) {
    VALUE s_dev;
    sub_handle* fd = NULL ;
    struct usb_device* dev = NULL;

    /* Open USB device */
    fd = sub_open( dev );

    s_dev = Data_Wrap_Struct(cSub20, 0, free, fd);
    rb_iv_set(self, "@device", s_dev);
    return self;
}

static VALUE s_lcd_write(VALUE self, VALUE str) {
    sub_handle* fd = NULL;
    VALUE s_dev;
    char strr = 'a';
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    sub_lcd_write(fd, &strr);
    return str;
}
void Init_sub20() {
    cSub20 = rb_define_class("Sub20", rb_cObject);
    rb_define_method(cSub20, "initialize", s_init, 0);
    rb_define_method(cSub20, "lcd_write", s_lcd_write, 1);
}