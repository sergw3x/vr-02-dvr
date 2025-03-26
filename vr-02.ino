
#define _BTN_PIN PB0;
#define _VRX_LED PB1;
#define _DVR_LED PB2;
#define _SW_PIN  PB4;

#define _debounceDelay 100;

uint8_t debounceDelay = _debounceDelay;

uint8_t BTN_PIN = _BTN_PIN ;
uint8_t VRX_LED = _VRX_LED;
uint8_t DVR_LED = _DVR_LED ;
uint8_t SW_PIN = _SW_PIN ;


uint32_t lastDebounceTime = 0;
uint8_t buttonState = LOW;
uint8_t lastButtonState = LOW;

uint8_t sw_state = LOW;

void setup() {
  pinMode(BTN_PIN, INPUT);
  pinMode(DVR_LED, OUTPUT);
  pinMode(VRX_LED, OUTPUT);
  pinMode(SW_PIN, OUTPUT);

  digitalWrite(VRX_LED, HIGH);
  digitalWrite(DVR_LED, LOW);
  digitalWrite(SW_PIN, sw_state);

  blink();
}

void loop() {

  if (digitalRead(BTN_PIN) != lastButtonState) {
    lastButtonState = !lastButtonState;
    lastDebounceTime = millis();
  } else if ((millis() - lastDebounceTime) > debounceDelay && buttonState != lastButtonState) {
    buttonState = lastButtonState;
    
    if (buttonState == HIGH) {

      if (sw_state) {
        sw_state = LOW;
      } else {
        sw_state = HIGH;
      }

    }
  }

  if (sw_state) {
    digitalWrite(VRX_LED, HIGH);
    digitalWrite(DVR_LED, LOW);
    sw_state = LOW;
  } else {
    digitalWrite(VRX_LED, LOW);
    digitalWrite(DVR_LED, HIGH);
    sw_state = HIGH;
  }
  
  digitalWrite(SW_PIN, sw_state);

}

void blink() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(VRX_LED, HIGH);
    digitalWrite(DVR_LED, LOW);
    delay(200);
    digitalWrite(VRX_LED, LOW);
    digitalWrite(DVR_LED, HIGH);
    delay(200);
  }
}
