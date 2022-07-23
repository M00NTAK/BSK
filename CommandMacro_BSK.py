import serial
import win32api
import keyboard

HOTKEY_A = 0X41
HOTKEY_S = 0X53
HOTKEY_D = 0X44
HOTKEY_F = 0X46
HOTKEY_G = 0X47
HOTKEY_V = 0X56
HOTKEY_ALT = 0XA4
HOTKEY_SHIFT = 0XA0
HOTKEY_CTRL = 0XA2


debounceTime = 0 #declare a variable for debouncing

LIST_HOTKEY = [HOTKEY_A, HOTKEY_S, HOTKEY_D, HOTKEY_F, HOTKEY_G, HOTKEY_V,
HOTKEY_ALT, HOTKEY_CTRL, HOTKEY_SHIFT]

LIST_CHARACTER = ['a', 's', 'd', 'f', 'g', 'v', 'q,' 'w', 'e']

py_serial = serial.Serial(
    port = 'COM7', #select a port Arduino plugged in
    baudrate = 115200, #synchronize baudrate with Arduino
)

keyboard.block_key('a')

while True: #굳이 키검사를 하고 보내야하나? 어차피 아두이노에서 검사하는데 리소스낭비같다.
    for i in range (0, 9):
        if(win32api.GetKeyState(LIST_HOTKEY[i]) & 0x8000): 
            py_serial.write(LIST_CHARACTER[i].encode()) 
            while(win32api.GetKeyState(LIST_HOTKEY[i]) not in [0x0001, 0]):
                pass
    
    
    '''
    if(win32api.GetAsyncKeyState(HOTKEY_A) & 0x8000): 
        py_serial.write('a'.encode()) 
        while(win32api.GetAsyncKeyState(HOTKEY_A) not in [0x0001, 0]):
            pass

    elif(win32api.GetAsyncKeyState(HOTKEY_S) & 0x8000): 
        py_serial.write('s'.encode()) 
        while(win32api.GetAsyncKeyState(HOTKEY_S) not in [0x0001, 0]):
            pass

    elif(win32api.GetAsyncKeyState(HOTKEY_D) & 0x8000): 
        py_serial.write('d'.encode()) 
        while(win32api.GetAsyncKeyState(HOTKEY_D) not in [0x0001, 0]):
            pass

    elif(win32api.GetAsyncKeyState(HOTKEY_F) & 0x8000): 
        py_serial.write('f'.encode()) 
        while(win32api.GetAsyncKeyState(HOTKEY_F) not in [0x0001, 0]):
            pass

    elif(win32api.GetAsyncKeyState(HOTKEY_G) & 0x8000): 
        py_serial.write('g'.encode()) 
        while(win32api.GetAsyncKeyState(HOTKEY_G) not in [0x0001, 0]):
            pass

        #테스트 코드 정상동작, 아두이노 단에서 문제 찾아야 함.'''
        