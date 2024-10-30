
// // /**********************************************************************
// //   Filename    : ADC_DAC_SineWave
// //   Description : Generate sine wave and control frequency with potentiometer.
// //   Author      : Adapted for analog usage
// // **********************************************************************/
// // #include <math.h>

// // #define PIN_ANALOG_IN  4    // Pin connected to potentiometer
// // #define DAC_PIN        25   // DAC1 on ESP32 (GPIO 25)
// // #define SINE_RES       100  // Resolution of the sine wave (number of points)
// // #define SAW_REW        100

// // void setup() {
// //   Serial.begin(115200);
// //   Serial.println("Starting...");
// // }

// // void loop() {
// //   // Read the potentiometer (ADC) value
// //   int adcVal = analogRead(PIN_ANALOG_IN);  // ESP32 has 12-bit ADC (0-4095)
  
// //   // Map ADC value to a frequency range (e.g., 1 Hz to 100 Hz for smoother control)
// //   //int frequency = map(adcVal, 0, 4095, 1, 100); 
// //   int frequency = map(adcVal, 0, 4095, 1, 4000);  // Map ADC value to 1 Hz to 1000 Hz


// //   // Generate sine wave values and write to DAC
// //   // for (int i = 0; i < SINE_RES; i++) {
// //   //   // Calculate the sine wave value between 0 and 255 (for 8-bit DAC)
// //   //   int dacVal = (sin(2 * PI * i / SINE_RES) + 1) * 127.5; // Shift sine wave to 0-255
// //     // Generate sawtooth wave values and write to DAC
// //   for (int i = 0; i < SINE_RES; i++) {
// //     // Calculate the sawtooth wave value between 0 and 255 (for 8-bit DAC)
// //     int dacVal = map(i, 0, SINE_RES, 0, 255);  // Linear ramp from 0 to 255


// //     // Write the sine wave value to the DAC
// //     dacWrite(DAC_PIN, dacVal);

// //     // Control the speed of the waveform (related to frequency)
// //     delayMicroseconds(1000000 / (frequency * SINE_RES));  // Delay based on frequency
// //   }

// //   // Print values to the Serial Monitor for debugging
// //   double voltage = adcVal / 4095.0 * 3.3;  // Calculate input voltage from ADC value
// //   Serial.printf("ADC Val: %d, Frequency: %d Hz, Voltage: %.2fV\n", adcVal, frequency, voltage);
// // }

// #include <math.h>

// #define PIN_ANALOG_IN  4    // Pin connected to potentiometer
// #define DAC_PIN        25   // DAC1 on ESP32 (GPIO 25)
// #define SINE_RES       100  // Resolution of the sine wave (number of points)
// #define BUTTON_PIN     32   // GPIO pin for button

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting...");

//   // Set up button pin as input with pull-down resistor
//   pinMode(BUTTON_PIN, INPUT_PULLDOWN);
// }

// void loop() {
//   // Read the potentiometer (ADC) value
//   int adcVal = analogRead(PIN_ANALOG_IN);  // ESP32 has 12-bit ADC (0-4095)

//   // Map ADC value to a frequency range (e.g., 1 Hz to 4000 Hz)
//   int frequency = map(adcVal, 0, 4095, 1, 4000); 

//   // Generate sawtooth wave values and write to DAC
//   for (int i = 0; i < SINE_RES; i++) {
//     // Calculate the sawtooth wave value between 0 and 255 (for 8-bit DAC)
//     int dacVal = map(i, 0, SINE_RES, 0, 255);  // Linear ramp from 0 to 255

//     // Write the sawtooth wave value to the DAC
//     dacWrite(DAC_PIN, dacVal);

//     // Control the speed of the waveform (related to frequency)
//     delayMicroseconds(1000000 / (frequency * SINE_RES));  // Delay based on frequency
//   }

//   // Print values to the Serial Monitor for debugging
//   double voltage = adcVal / 4095.0 * 3.3;  // Calculate input voltage from ADC value
//   Serial.printf("ADC Val: %d, Frequency: %d Hz, Voltage: %.2fV\n", adcVal, frequency, voltage);

//   // Check if the button is pressed
//   if (digitalRead(BUTTON_PIN) == HIGH) {
//     Serial.println("Button press");
//   }
// }



// #include <math.h>

// #define PIN_ANALOG_IN  4    // Pin connected to potentiometer
// #define DAC_PIN        25   // DAC1 on ESP32 (GPIO 25)
// #define SINE_RES       100  // Resolution of the sine wave (number of points)
// #define BUTTON_PIN     32   // GPIO pin for button

// int waveformMode = 0;  // 0 = Sawtooth, 1 = Sine, 2 = Square
// bool lastButtonState = LOW;

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting...");
//   pinMode(BUTTON_PIN, INPUT_PULLDOWN);  // Set up button pin as input with pull-down resistor
// }

// void loop() {
//   int adcVal = analogRead(PIN_ANALOG_IN);  // Read potentiometer (ADC value)
  
//   // Map ADC value to frequency and amplitude ranges
//   int frequency = map(adcVal, 0, 4095, 1, 1000);  // Map ADC value to frequency range (1 Hz to 1000 Hz)
//   int amplitude = map(adcVal, 0, 4095, 0, 255);   // Map ADC value to amplitude range (0 to 255)

//   // Check if the button is pressed and debounce
//   bool buttonState = digitalRead(BUTTON_PIN);
//   if (buttonState == HIGH && lastButtonState == LOW) {
//     waveformMode = (waveformMode + 1) % 3;  // Cycle between 0 (Saw), 1 (Sine), and 2 (Square)
//     Serial.printf("Switched to mode: %d\n", waveformMode);
//     delay(200);  // Debounce delay
//   }
//   lastButtonState = buttonState;

//   for (int i = 0; i < SINE_RES; i++) {
//     int dacVal = 0;

//     // Generate different waveforms based on the current mode
//     if (waveformMode == 0) {  // Sawtooth wave
//       dacVal = map(i, 0, SINE_RES, 0, amplitude);  // Linear ramp from 0 to amplitude
//     } else if (waveformMode == 1) {  // Sine wave
//       dacVal = (sin(2 * PI * i / SINE_RES) + 1) * (amplitude / 2.0);  // Sine wave between 0 and amplitude
//     } else if (waveformMode == 2) {  // Square wave
//       dacVal = (i < SINE_RES / 2) ? amplitude : 0;  // High for half the cycle, low for the other half
//     }

//     dacWrite(DAC_PIN, dacVal);  // Write to DAC

//     delayMicroseconds(1000000 / (frequency * SINE_RES));  // Control waveform speed based on frequency
//   }

//   double voltage = adcVal / 4095.0 * 3.3;  // Calculate input voltage
//   Serial.printf("ADC Val: %d, Frequency: %d Hz, Amplitude: %d, Voltage: %.2fV\n", adcVal, frequency, amplitude, voltage);
// }


// WORKING!!!

// #include <math.h>

// #define PIN_ANALOG_IN  4    // Pin connected to potentiometer
// #define DAC_PIN        25   // DAC1 on ESP32 (GPIO 25)
// #define SINE_RES       100  // Resolution of the wave (number of points)
// #define BUTTON_PIN     32   // GPIO pin for button

// int waveformMode = 0;  // 0 = Sawtooth, 1 = Sine, 2 = Square
// bool lastButtonState = LOW;
// unsigned long lastDebounceTime = 0;
// const unsigned long debounceDelay = 200;  // Debounce delay in ms

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting...");
//   pinMode(BUTTON_PIN, INPUT_PULLDOWN);  // Set up button pin as input with pull-down resistor
// }

// void loop() {
//   // Read the potentiometer (ADC value)
//   int adcVal = analogRead(PIN_ANALOG_IN);  
  
//   // Map ADC value to a smoother frequency range (e.g., 100 Hz to 1000 Hz)
//   int frequency = map(adcVal, 0, 4095, 100, 1000);  
//   int amplitude = 255;  // We'll use full amplitude for clearer oscilloscope display

//   // Button press detection with debouncing
//   bool buttonState = digitalRead(BUTTON_PIN);
//   if (buttonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
//     waveformMode = (waveformMode + 1) % 3;  // Cycle between 0 (Saw), 1 (Sine), 2 (Square)
//     Serial.printf("Switched to mode: %d\n", waveformMode);
//     lastDebounceTime = millis();  // Reset debounce timer
//   }

//   for (int i = 0; i < SINE_RES; i++) {
//     int dacVal = 0;

//     // Generate different waveforms based on the current mode
//     if (waveformMode == 0) {  // Sawtooth wave (sharp rise, sharp drop)
//       dacVal = map(i, 0, SINE_RES, 0, amplitude);  // Linear ramp up to max amplitude
//     } else if (waveformMode == 1) {  // Sine wave (smooth oscillation)
//       dacVal = (sin(2 * PI * i / SINE_RES) + 1) * (amplitude / 2.0);  // Shift sine wave to range 0 to amplitude
//     } else if (waveformMode == 2) {  // Square wave (distinct high/low transition)
//       dacVal = (i < SINE_RES / 2) ? amplitude : 0;  // High for first half of cycle, low for second half
//     }

//     // Write the waveform value to the DAC
//     dacWrite(DAC_PIN, dacVal);

//     // Control the waveform's frequency
//     delayMicroseconds(1000000 / (frequency * SINE_RES));  // Adjust based on frequency
//   }

//   double voltage = adcVal / 4095.0 * 3.3;  // Calculate input voltage for debugging
//   Serial.printf("ADC Val: %d, Frequency: %d Hz, Mode: %d, Voltage: %.2fV\n", adcVal, frequency, waveformMode, voltage);
// }


#include <math.h>

#define PIN_ANALOG_IN  4    // Pin connected to potentiometer
#define DAC_PIN        25   // DAC1 on ESP32 (GPIO 25)
#define SINE_RES       100  // Resolution of the wave (number of points)
#define BUTTON_PIN     32   // GPIO pin for button

int waveformMode = 0;  // 0 = Sawtooth, 1 = Sine, 2 = Square, 3 = Triangle
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;  // Debounce delay in ms

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);  // Set up button pin as input with pull-down resistor
}

void loop() {
  // Read the potentiometer (ADC value)
  int adcVal = analogRead(PIN_ANALOG_IN);  
  
  // Map ADC value to a smoother frequency range (e.g., 100 Hz to 1000 Hz)
  int frequency = map(adcVal, 0, 4095, 100, 1000);  
  int amplitude = 255;  // We'll use full amplitude for clearer oscilloscope display

  // Button press detection with debouncing
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
    waveformMode = (waveformMode + 1) % 4;  // Cycle between 0 (Saw), 1 (Sine), 2 (Square), 3 (Triangle)
    Serial.printf("Switched to mode: %d\n", waveformMode);
    lastDebounceTime = millis();  // Reset debounce timer
  }

  for (int i = 0; i < SINE_RES; i++) {
    int dacVal = 0;

    // Generate different waveforms based on the current mode
    if (waveformMode == 0) {  // Sawtooth wave (sharp rise, sharp drop)
      dacVal = map(i, 0, SINE_RES, 0, amplitude);  // Linear ramp up to max amplitude
    } else if (waveformMode == 1) {  // Sine wave (smooth oscillation)
      dacVal = (sin(2 * PI * i / SINE_RES) + 1) * (amplitude / 2.0);  // Shift sine wave to range 0 to amplitude
    } else if (waveformMode == 2) {  // Square wave (distinct high/low transition)
      dacVal = (i < SINE_RES / 2) ? amplitude : 0;  // High for first half of cycle, low for second half
    } else if (waveformMode == 3) {  // Triangle wave (linear rise and fall)
      if (i < SINE_RES / 2) {
        dacVal = map(i, 0, SINE_RES / 2, 0, amplitude);  // Rising edge
      } else {
        dacVal = map(i, SINE_RES / 2, SINE_RES, amplitude, 0);  // Falling edge
      }
    }

    // Write the waveform value to the DAC
    dacWrite(DAC_PIN, dacVal);

    // Control the waveform's frequency
    delayMicroseconds(1000000 / (frequency * SINE_RES));  // Adjust based on frequency
  }

  double voltage = adcVal / 4095.0 * 3.3;  // Calculate input voltage for debugging
  Serial.printf("ADC Val: %d, Frequency: %d Hz, Mode: %d, Voltage: %.2fV\n", adcVal, frequency, waveformMode, voltage);
}


