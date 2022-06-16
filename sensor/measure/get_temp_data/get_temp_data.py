import struct, array, time, io, fcntl

I2C_CH =            1
I2C_SLAVE=          0x0703
HDC1080_ADDRESS =   0x40

HDC1080_fr= io.open("/dev/i2c-"+str(I2C_CH), "rb", buffering=0)
fcntl.ioctl(HDC1080_fr, I2C_SLAVE, HDC1080_ADDRESS)

data = HDC1080_fr.read(2)
buf = array.array('B', data)
temp = (buf[0] * 256) + buf[1]
cTemp = (temp / 65536.0) * 165.0 - 40
print ("%.4f" % cTemp)
