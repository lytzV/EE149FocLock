import serial
ser = serial.Serial('/dev/tty.usbmodem141401', 115200)  # open serial port
print(ser.name)         # check which port was really used
ser.write(b'Hello')     # write a string
ser.close()