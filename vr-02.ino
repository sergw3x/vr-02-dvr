
const uint8_t _pin_DVR = 4;      // PB4
int state_pin_DVR = LOW;
const uint8_t _pin_VRX = 3;      // PB3
int state_pin_VRX = HIGH;
const uint8_t _pin_BTN = 2;      // PB2

const uint8_t _pin_LED_DVR = 1;  // PB1
int state_LED_DVR = HIGH;
const uint8_t _pin_LED_VRX = 0;  // PB0
int state_LED_VRX = LOW;

int buttonState;                 // the current reading from the input pin
int lastButtonState = LOW;       // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(_pin_LED_DVR, OUTPUT);
  pinMode(_pin_LED_VRX, OUTPUT);

  pinMode(_pin_BTN, INPUT);

  // enable led & open the channel
  digitalWrite(_pin_LED_DVR, HIGH);
  digitalWrite(_pin_LED_VRX, LOW);
  digitalWrite(_pin_VRX, HIGH);
}


void loop() {

  int reading = digitalRead(_pin_BTN);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {

        if (state_pin_VRX == HIGH) {
          // disable VideoRX
          state_pin_VRX = LOW;
          state_LED_VRX = LOW;

          digitalWrite(_pin_VRX, state_pin_VRX);
          digitalWrite(_pin_LED_VRX, state_LED_VRX);
          
          // enable DVR
          state_pin_DVR = HIGH;
          state_LED_DVR = HIGH;
          
          digitalWrite(_pin_DVR, state_pin_DVR);
          digitalWrite(_pin_LED_DVR, state_LED_DVR);

        } else {

          // disable DVR
          state_pin_DVR = LOW;
          state_LED_DVR = LOW;
          
          digitalWrite(_pin_DVR, state_pin_DVR);
          digitalWrite(_pin_LED_DVR, state_LED_DVR);

          // enable VideoRX
          state_pin_VRX = HIGH;
          state_LED_VRX = HIGH;

          digitalWrite(_pin_VRX, state_pin_VRX);
          digitalWrite(_pin_LED_VRX, state_LED_VRX);
          
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
