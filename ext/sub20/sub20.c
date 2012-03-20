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
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    sub_lcd_write(fd, StringValueCStr(str));
    return str;
}

static VALUE s_get_serial_number(VALUE self) {
    sub_handle* fd = NULL;
    VALUE s_dev;
    char sn_buf[20];
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    sub_get_serial_number(fd, sn_buf, 20);
    return rb_str_new2(sn_buf);
}

static VALUE s_get_product_id(VALUE self) {
    sub_handle* fd = NULL;
    VALUE s_dev;
    char id_buf[20];
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    sub_get_product_id(fd, id_buf, 20);
    return rb_str_new2(id_buf);
}

static VALUE s_strerror(VALUE self, VALUE error_code) {
    sub_handle* fd = NULL;
    VALUE s_dev;
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    return rb_str_new2(sub_strerror(FIX2INT(error_code)));
}

static VALUE s_gpio_config(VALUE self, VALUE set, VALUE mask) {
    sub_handle* fd = NULL;
    VALUE s_dev;
    sub_int32_t read_config;
    int ret_code;
    s_dev = rb_iv_get(self, "@device");
    Data_Get_Struct(s_dev,sub_handle,fd);
    ret_code = sub_gpio_config(fd, FIX2INT(set), &read_config, FIX2INT(mask));
    return INT2FIX(ret_code);
}

void Init_sub20() {
    cSub20 = rb_define_class("Sub20", rb_cObject);
    rb_define_method(cSub20, "initialize", s_init, 0);
    rb_define_method(cSub20, "lcd_write", s_lcd_write, 1);
    rb_define_method(cSub20, "get_serial_number", s_get_serial_number, 0);
    rb_define_method(cSub20, "get_product_id", s_get_product_id, 0);
    rb_define_method(cSub20, "strerror", s_strerror, 1);
    rb_define_method(cSub20, "gpio_config", s_gpio_config, 2);
}