import serial
import time
import re

print(serial.__version__)
ser0 = serial.Serial('COM3', 9600)
#ser1 = serial.Serial('COM4', 9600)
time.sleep(2)

#get data from keyboard
while True:
    data = input('Enter your command: ')
    if data == 'exit':
        #ser1.close()
        ser0.close()
        exit()
    elif data == '5':
        #send 5 to arduino
        ser0.write(data.encode())
        #ser1.write(data.encode())
        print('Sent: ' + data)
        time.sleep(0.5)
        data = input('Movement: ')
        ser0.write(data.encode())
        print("wait untill it stops")
    elif len(data) > 1:
        #store into a list which each character is an element and each integer is an element eg. [f, 12, l, 4]
        data = re.findall(r'\d+|\D', data)
        print(data)
        while len(data) > 0:
            #send each element to arduino
            if data[0] == 'f':
                ser0.write('1'.encode())
                #ser1.write(b'1')
                print('forward')
            if data[0] == 'l':
                ser0.write('2'.encode())
                #ser1.write(b'2')
                print('left')
            if data[0] == 'r':
                ser0.write('3'.encode())
                #ser1.write(b'3')
                print('right')
            if data[0] == 's':
                ser0.write('0'.encode())
                #ser1.write(b'0')
                print('stop')
            if data[0].isnumeric():
                #delay for the time of the integer
                time.sleep(int(data[0]))
                #send stop command
                ser0.write('0'.encode())
                print('stop')
                time.sleep(0.5)
            data.pop(0)
    else:
        if not data.isnumeric():
            print('Invalid input')
            continue
        else:
            #integer sent to arduino
            ser0.write(data.encode())
            #ser1.write(data.encode())
            if int(data) == 4:
                print('countdown 15s')
            print('Sent: ' + data)