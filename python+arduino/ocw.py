import serial, os, sys, time

port = ""
usb_count = 0
devices = os.listdir("/dev")
for device in devices:
    if "cu.usbmodem" in device:  # was "cu.usbserial"
        port = device
        usb_count += 1
if usb_count == 0:
    sys.exit("No port found")
if usb_count > 1:
    sys.exit("Multiple ports found")

port = "/dev/" + port

print(port)

ser = serial.Serial(port, timeout=1)
s = ser.read(10000)
print(s)

message = "c2\n"
while True:
    ser.write(bytes("o2\n", 'utf-8'))
    time.sleep(1)
    ser.write(bytes("c2\n", 'utf-8'))
    time.sleep(1)
