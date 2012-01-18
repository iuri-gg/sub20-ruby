# encoding: UTF-8
require 'mkmf'
$CFLAGS << ' -DLIBUSB_1_0 -I/usr/local/include/libusb-1.0 -O2 -Wall -Werror -g -I../src -I../boot/vnd/fw -I.'
$LDFLAGS << ' -L/usr/local/lib -lusb-1.0 -lm '

create_makefile('sub20')