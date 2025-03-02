
#define BOARD_VERSION 1

#if BOARD_VERSION == 1

#define VRX_PIN 3
#define VRX_LED 1
#define DVR_PIN 4
#define DVR_LED 0
#define BTN_PIN 2

#elif BOARD_VERSION == 2

#define VRX_PIN = 3;
#define VRX_LED 1
#define DVR_PIN 4
#define DVR_LED 2
#define BTN_PIN 0

#endif

const uint8_t buttonPin = BTN_PIN;  // the number of the pushbutton pin
const uint8_t debounceDelay = 100;  // milliseconds the button must be in a stable state

uint8_t buttonState = HIGH;     // the current reading from the input pin,  initial value = default (pullup, so high)
uint8_t lastButtonState = LOW;  // the previous reading from the input pin, initial value = default (pullup, so high)

uint32_t lastDebounceTime = 0;  // the last time the output pin was toggled
uint8_t count = 0;


uint8_t vrx_status = HIGH;
uint8_t dvr_status = LOW;

const uint8_t vrx_pin = VRX_PIN;
const uint8_t vrx_led = VRX_LED;

const uint8_t dvr_pin = DVR_PIN;
const uint8_t dvr_led = DVR_LED;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(dvr_led, OUTPUT);
  pinMode(dvr_pin, OUTPUT);
  pinMode(vrx_led, OUTPUT);
  pinMode(vrx_pin, OUTPUT);

  // enable led for default [VRX], enable LED & open the channel
}

void loop() {

  if (digitalRead(buttonPin) != lastButtonState) {
    lastButtonState = !lastButtonState;  // Switched states, HIGH becomes LOW, or LOW becomes HIGH
    lastDebounceTime = millis();
  } else if ((millis() - lastDebounceTime) > debounceDelay && buttonState != lastButtonState) {
    buttonState = lastButtonState;

    // On the rising edge, that is when you release the button, toggle the LED
    if (buttonState == HIGH) {

      vrx_status = !vrx_status;
      dvr_status = !dvr_status;
    }
  }

  if (dvr_status == HIGH) {

    digitalWrite(vrx_pin, vrx_status);
    digitalWrite(vrx_led, vrx_status);

    digitalWrite(dvr_pin, dvr_status);
    digitalWrite(dvr_led, dvr_status);

  } else {

    digitalWrite(dvr_pin, dvr_status);
    digitalWrite(dvr_led, dvr_status);

    digitalWrite(vrx_pin, vrx_status);
    digitalWrite(vrx_led, vrx_status);
  }
}
