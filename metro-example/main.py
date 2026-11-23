import time
import board
import digitalio

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    led.sleep(0.5)
    led.value = False
    led.sleep(0.5)