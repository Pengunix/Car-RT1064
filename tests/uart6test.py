import serial
import struct
from time import sleep
from random import randint

try:
    while True:
        buzzer = randint(-1, 5)
        servo = 1700
        speed = -1.5
        txFrame = struct.pack("<BbHfBBBB", 0x34, buzzer, servo, speed, 0, 0, 0, 0x43)
        xorCheck = 0
        for i in txFrame:
            xorCheck ^= i
        txFrame = struct.pack("<BbHfBBBB", 0x34, buzzer, servo, speed, 0, 0, xorCheck, 0x43)

        uart6 = serial.Serial("/dev/ttyUSB0", 921600)
        uart6.write(txFrame)
        sleep(0.01)
except KeyboardInterrupt:
    uart6.close()
    print(txFrame.hex())