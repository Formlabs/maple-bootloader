 # python
 # import os
 # try:
    # serial = os.environ["JTAG_SERIAL"]
 # except:
    # serial = "/dev/ttyACM0"
# gdb.execute('target extended-remote ' + serial)
# end

#target extended-remote /dev/cu.usbmodemDDE284C1
target extended-remote /dev/cu.usbmodemDDE3AAC1
set height 0
file build/maple_boot.elf
mon swdp_scan
attach 1
mon option erase
