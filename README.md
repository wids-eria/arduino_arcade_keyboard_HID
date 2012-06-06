Arcade machine controls to usb keyboard mapper
----------------------------------------------

* Keyboard HID firmware for UNO 16u8 from http://hunt.net.nz/users/darran/weblog/b3029/Arduino_UNO_Keyboard_HID_version_03.html

Installation
------------

* Upload sketch to Arduino (while it has its original firmware)
* Install dfu-programmer on linux/osx.
* Put Arduino into DFU mode.
* dfu-programmer at90usb82 erase
* dfu-programmer at90usb82 flash (included firmware file)
* dfu-programmer at90usb82 reset
* Replug, and it should start sending button presses!

Usage
-----

Uses serial communication to talk to the usb at chip. Chip expects 8 bytes using Serial.write(byte_buffer, 8)

Byte Contents
0 Modifier keys:
  Bit 0 - Left CTRL
  Bit 1 - Left SHIFT
  Bit 2 - Left ALT
  Bit 3 - Left GUI
  Bit 4 - Right CTRL
  Bit 5 - Right SHIFT
  Bit 6 - Right ALT
  Bit 7 - Right GUI
1 Not used
2 - 7 HID active key usage codes. This represents up to 6 keys currently being pressed.



