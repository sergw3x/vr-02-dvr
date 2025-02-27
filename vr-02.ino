/*
  Press button, light LED.
  ------------------------------------------------------------------------------
  
  [ See pinout: https://goo.gl/ijL0of ]
  
  Turns on and off a light emitting diode(LED) connected to digital
  pin 2, when pressing a pushbutton attached to pin 3.

  [ LED_PIN ]    -> [Resistor 240R]   -> [LED] -> [Ground]
  [ BUTTON_PIN ] -> [ Button ]     -> [Vcc]
  [ BUTTON_PIN ] -> [Resistor 10k] -> [Ground]
       
*/

const uint8_t buttonPin = 3;  // the number of the pushbutton pin
const uint8_t ledPin = 2;  // the number of the LED pin

int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

/*
таки шо нам нада.
при включении включаем основной канал (на котором будет пайп от VRX и до контроллера дисплея)
при нажатии кнопки переключаем канал на следующий, отключая предварительно предыдущий.
для каждого канала свой LED
*/

int myPins[] = {2, 4, 8, 3, 6, 4};


void setup() {
  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}


void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
