int rfSwitchInput = 13; // Pin for recieving RF keyfob. Digital only
int relayExtend = 2; // Pin triggering relay to extend
int relayPause = 4 ; // Activates relay #2 and disconnects ground to motor module
 
void setup() {
  pinMode(rfSwitchInput, INPUT);
  pinMode(relayExtend, OUTPUT);
  pinMode(relayPause, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(rfSwitchInput) == LOW) {
        digitalWrite(relayPause, LOW); // Connects ground to motor module
        digitalWrite(relayExtend, LOW); // Sets motor module to default state of retraction
        Serial.println("DOOR Closing");   
    }
  
  else {
      Serial.print("OPENING DOOR");
      digitalWrite(relayExtend, HIGH);
      Serial.println(digitalRead(rfSwitchInput));
      delay(10000); // Extend for X seconds (1000 = 1 sec)
      digitalWrite(relayPause, HIGH); // Breaks ground on relay #2 to pause retraction
      digitalWrite(relayExtend, LOW); // Reverts module to default retraction mode
      delay(10000); // // Pause for X seconds (1000 = 1 sec)
      }
}
