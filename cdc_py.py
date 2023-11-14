from winusbcdc import ComPort
p = ComPort("My USB Device")  # friendly name as shown in device manager
# or
p = ComPort(vid=0xCafe, pid=0x4000)

p.open()
p.write(b'foo')
print(p.read())
p.close()