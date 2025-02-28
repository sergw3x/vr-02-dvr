// pins DVR
const uint8_t _pin_DVR = 4;      // PB4
const uint8_t _pin_DVR_LED = 1;  // PB1

// state DVR
int state_pin_DVR = LOW;

// pins VideoRX
const uint8_t _pin_VRX = 3;      // PB3
const uint8_t _pin_VRX_LED = 0;  // PB0

// state VideoRX
int state_pin_VRX = HIGH;

// Button pin
const uint8_t _pin_BTN = 2;      // PB2

int buttonState;                 // the current reading from the input pin
int lastButtonState = LOW;       // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(_pin_DVR_LED, OUTPUT);
  pinMode(_pin_VRX_LED, OUTPUT);

  pinMode(_pin_BTN, INPUT);

  // enable led for default [VRX], enable LED & open the channel
  digitalWrite(_pin_VRX_LED, state_pin_VRX);
  digitalWrite(_pin_VRX, state_pin_VRX);

  digitalWrite(_pin_DVR_LED, state_pin_DVR);  
  digitalWrite(_pin_DVR, state_pin_DVR);
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
          digitalWrite(_pin_VRX, state_pin_VRX);
          digitalWrite(_pin_VRX_LED, state_pin_VRX);
          
          // enable DVR
          state_pin_DVR = HIGH;
          digitalWrite(_pin_DVR, state_pin_DVR);
          digitalWrite(_pin_DVR_LED, state_pin_DVR);

        } else {

          // disable DVR
          state_pin_DVR = LOW;
          digitalWrite(_pin_DVR, state_pin_DVR);
          digitalWrite(_pin_DVR_LED, state_pin_DVR);

          // enable VideoRX
          state_pin_VRX = HIGH;
          digitalWrite(_pin_VRX, state_pin_VRX);
          digitalWrite(_pin_VRX_LED, state_pin_VRX);
          
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
