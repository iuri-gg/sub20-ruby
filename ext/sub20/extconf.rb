# encoding: UTF-8
require 'mkmf'
$CFLAGS << ' -DLIBUSB_1_0 -I/usr/local/include/libusb-1.0'

create_makefile('sub20')