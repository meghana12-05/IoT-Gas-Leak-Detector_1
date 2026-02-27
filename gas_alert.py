import paho.mqtt.client as mqtt
from twilio.rest import Client
import time

# --- Fill in your Twilio details ---
TWILIO_SID = "YOUR_TWILIO_SID_HERE"
TWILIO_TOKEN = "YOUR_TWILIO_TOKEN_HERE"
TWILIO_NUMBER = "+1234567890" 
YOUR_PHONE = "+910000000000"   # Your actual mobile number

twilio_Client = Client(TWILIO_SID, TWILIO_TOKEN)
last_sms_time = 0 

def send_emergency_sms(gas_value):
    global last_sms_time
    if time.time() - last_sms_time > 60: # Send max 1 SMS per minute
        twilio_Client.messages.create(
            body=f"🚨 ALERT: High gas levels detected! (Level: {gas_value})",
            from_=TWILIO_NUMBER,
            to=YOUR_PHONE
        )
        print("📱 SMS Sent!")
        last_sms_time = time.time()

def on_message(client, userdata, msg):
    gas_level = int(msg.payload.decode())
    print(f"Current Gas Level: {gas_level}")
    
    if gas_level > 2000: # Danger threshold
        send_emergency_sms(gas_level)

client = mqtt.Client()
client.on_message = on_message
client.connect("test.mosquitto.org", 1883, 60)
client.subscribe("home/kitchen/gas")

print("🛡️ Backend Running. Listening for gas leaks...")
client.loop_forever()