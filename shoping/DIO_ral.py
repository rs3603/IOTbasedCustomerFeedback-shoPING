import mraa
import time
import sys

 
#switch_pin_number=8
#buzz_pin_number=1
encoderpin1 = 0
encoderpin2 = 1

lastencoded = 0
encodervalue = 0
lastencodervalue = 0

msb = 0
lsb = 0
 
# Configuring the switch and buzzer as GPIO interfaces
#switch = mraa.Gpio(switch_pin_number)
#buzz = mraa.Gpio(buzz_pin_number)

encoder1 = mraa.Gpio(encoderpin1)
encoder2 = mraa.Gpio(encoderpin2) 

# Configuring the switch and buzzer as input & output respectively
#switch.dir(mraa.DIR_IN)
#buzz.dir(mraa.DIR_OUT)
encoder1.dir(mraa.DIR_IN)
encoder2.dir(mraa.DIR_IN)

encoder1.mode(mraa.MODE_PULLUP)
encoder2.mode(mraa.MODE_PULLUP)

#encoder1.write(1)
#encoder2.write(1)

class Counter:
	count = 0

c = Counter()
enc_states = [0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0]
def updateencoder():
	global encoded,lastencoded,encodervalue,msb,lsb,enc_states
	msb = encoder1.read()
	lsb = encoder2.read()
	encoded = (msb << 1)|lsb
	sum = (lastencoded << 2)|encoded
	if(enc_states[sum]==1):
		c.count+=1
	if(enc_states[sum]==-1):
		c.count-=1
	lastencoded = encoded
	return enc_states[sum]
#encoder1.isr(mraa.EDGE_BOTH,updateencoder,updateencoder)
#encoder2.isr(mraa.EDGE_BOTH,updateencoder,updateencoder)
 
print "Press Ctrl+C to escape..."
try:
	while(1):
		#pass 
		if(updateencoder() and c.count%4==0):
			print updateencoder()
			print (c.count/4)%20
except KeyboardInterrupt:
	exit

