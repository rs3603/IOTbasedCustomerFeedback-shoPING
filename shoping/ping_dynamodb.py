import mraa
import math
import pyupm_i2clcd as lcd
import time
import boto
import boto.dynamodb2
import time
import json
import serial
import time
#import testdata
from boto.dynamodb2.fields import HashKey, RangeKey, KeysOnlyIndex, GlobalAllIndex
from boto.dynamodb2.types import NUMBER
from boto.dynamodb2.items import Item

ACCOUNT_ID = ''
IDENTITY_POOL_ID = ''
ROLE_ARN = ''

# Use cognito to get an identity.
cognito = boto.connect_cognito_identity()
cognito_id = cognito.get_id(ACCOUNT_ID, IDENTITY_POOL_ID)
oidc = cognito.get_open_id_token(cognito_id['IdentityId'])
 
# Further setup your STS using the code below
sts = boto.connect_sts()
assumedRoleObject = sts.assume_role_with_web_identity(ROLE_ARN, "XX", oidc['Token'])

DYNAMODB_TABLE_NAME = 'pingdata'
# Prepare DynamoDB client
client_dynamo = boto.dynamodb2.connect_to_region('us-east-1',aws_access_key_id=assumedRoleObject.credentials.access_key,aws_secret_access_key=assumedRoleObject.credentials.secret_key,security_token=assumedRoleObject.credentials.session_token)

KINESIS_STREAM_NAME = 'edisonDemoKinesis'
# Prepare Kinesis client
client_kinesis = boto.connect_kinesis(aws_access_key_id=assumedRoleObject.credentials.access_key,aws_secret_access_key=assumedRoleObject.credentials.secret_key,security_token=assumedRoleObject.credentials.session_token)
from boto import kinesis
#kinesis = kinesis.connect_to_region("us-east-1")
#stream = kinesis.create_stream("edisonDemoKinesis", 1)
#kinesis.describe_stream("edisonDemoKinesis")
#kinesis.list_streams()
#global count_dyn 
count_dyn=0

from boto.dynamodb2.table import Table
table_dynamo = Table(DYNAMODB_TABLE_NAME, connection=client_dynamo)
try:
        pingdata = Table.create('pingdata', schema=[HashKey('timestamp')],connection = client_dynamo)
	count_dyn=0
	pingdata = Table('pingdata', schema = [HashKey('timestamp')], connection = client_dynamo)
except:
	#count_dyn = tempdata.count() + 1
	pingdata = Table('pingdata', schema = [HashKey('timestamp')], connection = client_dynamo)	
	existingitems = pingdata.scan()
	for i in existingitems:	
	    count_dyn=count_dyn+1
time.sleep(.15)
#tempdata = Table('tempdata', schema = [HashKey('timestamp')], connection = client_dynamo)

#B = 4275
#R0 = 100000
 
#lcdDisplay = lcd.Jhd1313m1(0, 0x3E, 0x62)
#tempSens = mraa.Aio(1)

#switch_pin_number=8


# Configuring the switch and buzzer as GPIO interfaces
#switch = mraa.Gpio(switch_pin_number)

 
# Configuring the switch and buzzer as input & output respectively
#switch.dir(mraa.DIR_IN)

print "Press Ctrl+C to escape..."
count = 0

count_kin = 0


s = None
def setup():
        global s
 # open serial COM port to /dev/ttyS0, which maps to UART0(D0/D1)
 # the baudrate is set to 57600 and should be the same as the one
 # specified in the Arduino sketch uploaded to ATMega32U4.
        s = serial.Serial("/dev/ttyS0", 57600)

setup()

def loop():
 # send "1" to the Arduino sketch on ATMega32U4.
 # the sketch will turn on the LED attached to D13 on the board
	global count_dyn
	count_dyn  = count_dyn+1;
        a = s.read(1)
	pingdata.put_item(data={'iter':str(count_dyn)+'-'+str(a),'temperature':str(count_dyn),'timestamp':str(time.time())},overwrite=True)
        time.sleep(1)
	print a

try:
	while True:
        	loop()
except KeyboardInterrupt:
        exit




