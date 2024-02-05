#include <Arduino.h>

const byte potPin = PA0;
const byte buttonPin = PB10;
const byte buttonPin2= PB11;
const byte triggerPin = PA6;
const byte cvPin = PA2;

// hack to update serial monitor less frequently.
int jitterTollerance = 15;

int potVal=0;
int buttonState = 0;
int buttonState2 = 0;
int triggerVal=0;
int cvVal=0;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(triggerPin, INPUT);

  // Tell the framework we have a 12-bit ADC
  analogReadResolution(12);
}

void loop() {
  // The button.
  int curButtonState = digitalRead(buttonPin);
  int curButtonState2 = digitalRead(buttonPin2);

  // Only update when there is an actual change in state.
  if (curButtonState != buttonState){
    buttonState = curButtonState;
    if (buttonState == HIGH) {
      Serial.println("Button 1: HIGH");
    } else {
      Serial.println("Button 1: LOW");
    }
  }

  // Only update when there is an actual change in state.
  if (curButtonState2 != buttonState2){
    buttonState2 = curButtonState2;
    if (buttonState2 == HIGH) {
      Serial.println("Button 2: HIGH");
    } else {
      Serial.println("Button 2: LOW");
    }
  }

  // The potentiometer
  int curVal;
  curVal = analogRead(potPin);

  // Deal with jitter....
  if (curVal < (potVal - jitterTollerance) || curVal > (potVal + jitterTollerance)){
    potVal = curVal;
    int reversedVal = map(potVal, 0, 4096, 4096, 0);
    Serial.println("PotVal: " + String(potVal) + ", reversedVal: " + String(reversedVal));
  }

  // Trigger via digital input.
  int curTriggerVal = digitalRead(triggerPin);

  // Only update if there is an actual change in state.
  if (curTriggerVal != triggerVal){
    triggerVal = curTriggerVal;
    Serial.print("TRIGGER: " + String(triggerVal));

    if (triggerVal == HIGH) {
      Serial.println(" - HIGH");
    } else {
      Serial.println(" - LOW");
    }
  }


  // Control Voltage via analog pin.
  int curCvVal = analogRead(cvPin);

  // Only update if athere is an actual chqange.
  if (curCvVal != cvVal){
    cvVal = curCvVal;

    Serial.print("CV: " + String(cvVal));
  }
}
