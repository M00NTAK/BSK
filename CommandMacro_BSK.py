import serial
from pynput import keyboard


HOTKEY_A = 0X41
HOTKEY_S = 0X53
HOTKEY_D = 0X44
HOTKEY_F = 0X46
HOTKEY_G = 0X47
HOTKEY_V = 0X56
HOTKEY_ALT = 0XA4
HOTKEY_SHIFT = 0XA0
HOTKEY_CTRL = 0XA2

LIST_HOTKEY = [HOTKEY_A, HOTKEY_S, HOTKEY_D, HOTKEY_F, HOTKEY_G, HOTKEY_V]

py_serial = serial.Serial(
    port = 'COM7', #select a port Arduino plugged in
    baudrate = 115200, #synchronize baudrate with Arduino
)
 
def keyboard_listener():
	global listener
	def on_press(key):
		pass

	def on_release(key):
		if key == keyboard.Key.esc:
			return False # This will quit the listener
 
	def win32_event_filter(msg, data):
		if (msg == 256) and data.vkCode in LIST_HOTKEY:
			py_serial.write(chr(data.vkCode).encode())
			print('{0} pressed'.format(chr(data.vkCode)))
			listener._suppress = True

		elif (msg == 257) and data.vkCode in LIST_HOTKEY:
			py_serial.write('0'.encode())
			print('{0} released'.format(chr(data.vkCode)))
			listener._suppress = True

		else:
	 		listener._suppress = False
		return True
			
	return keyboard.Listener(
		on_press=on_press,
		on_release=on_release,
		win32_event_filter=win32_event_filter,
		suppress=False
	)

listener = keyboard_listener()

if __name__ == '__main__':
	with listener as ml:
		ml.join() 