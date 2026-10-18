#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


const byte sensorPins[3] = {2, 3, 4};
const byte ledPins[4] = {12, 6, 7, 8};
const byte buzzerPin = 9;
const byte buttonPin = 10;


const byte TOTAL_NEURONS = 50;
const byte INPUTS = 3;
const byte HIDDEN = 32;
const byte OUTPUTS = 15;

const int THRESHOLD = 5;

int membrane[TOTAL_NEURONS] = {0};
bool fired[TOTAL_NEURONS] = {false};

int sensor[3] = {0, 0, 0};
byte currentClass = 0;
unsigned long spikeCount = 0;

bool paused = false;
bool lastButtonReading = HIGH;
bool stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 40;


unsigned long led8Until = 0;
const unsigned long outputLedDuration = 250;

unsigned long lastLcdUpdate = 0;
const unsigned long lcdInterval = 250;

void setup() {
  Serial.begin(115200);

  for (byte i = 0; i < 3; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  for (byte i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("50 Neuron SNN");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

void readSensors() {
  
  for (byte i = 0; i < 3; i++) {
    sensor[i] = (digitalRead(sensorPins[i]) == LOW) ? 1 : 0;
  }

  currentClass = sensor[0] + sensor[1] + sensor[2];
}

void checkButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != stableButtonState) {
      stableButtonState = reading;

      if (stableButtonState == LOW) {
        paused = !paused;
      }
    }
  }

  lastButtonReading = reading;
}

void updateNetwork() {
  
  for (byte i = 0; i < TOTAL_NEURONS; i++) {
    fired[i] = false;
  }

  
  for (byte i = 0; i < INPUTS; i++) {
    fired[i] = sensor[i] == 1;
    membrane[i] = fired[i] ? THRESHOLD : 0;
  }

  
  for (byte i = INPUTS; i < INPUTS + HIDDEN; i++) {
    byte preferredClass = (i % 3) + 1;

    if (currentClass == preferredClass && currentClass > 0) {
      membrane[i] += 2;
    } else {
      membrane[i] -= 1;
    }

    if (membrane[i] < 0) {
      membrane[i] = 0;
    }

    if (membrane[i] >= THRESHOLD) {
      fired[i] = true;
      membrane[i] = 0;
    }
  }

  
  for (byte i = INPUTS + HIDDEN; i < TOTAL_NEURONS; i++) {
    byte outputGroup = ((i - (INPUTS + HIDDEN)) / 5) + 1;

    int incomingSpikes = 0;

    for (byte h = INPUTS; h < INPUTS + HIDDEN; h++) {
      byte hiddenClass = (h % 3) + 1;

      if (fired[h] && hiddenClass == outputGroup) {
        incomingSpikes++;
      }
    }

    if (currentClass > 0 && currentClass == outputGroup) {
      membrane[i] += incomingSpikes;
    } else {
      membrane[i] -= 1;
    }

    if (membrane[i] < 0) {
      membrane[i] = 0;
    }

    if (membrane[i] >= THRESHOLD) {
      fired[i] = true;
      membrane[i] = 0;
      spikeCount++;
    }
  }
}

void updateOutputs() {
  
  digitalWrite(ledPins[0], sensor[0] ? HIGH : LOW);
  digitalWrite(ledPins[1], sensor[1] ? HIGH : LOW);
  digitalWrite(ledPins[2], sensor[2] ? HIGH : LOW);

  
  bool outputSpike = false;

  for (byte i = INPUTS + HIDDEN; i < TOTAL_NEURONS; i++) {
    if (fired[i]) {
      outputSpike = true;
      break;
    }
  }

  if (outputSpike) {
    led8Until = millis() + outputLedDuration;
    tone(buzzerPin, 2000, 80);
  }

  digitalWrite(
    ledPins[3],
    (long)(led8Until - millis()) > 0 ? HIGH : LOW
  );

  if (paused) {
    noTone(buzzerPin);
    for (byte i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void updateLCD() {
  if (millis() - lastLcdUpdate < lcdInterval) {
    return;
  }

  lastLcdUpdate = millis();

  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(sensor[0]);
  lcd.print(sensor[1]);
  lcd.print(sensor[2]);
  lcd.print(" Class:");
  lcd.print(currentClass);
  lcd.print("  ");

  lcd.setCursor(0, 1);
  if (paused) {
    lcd.print("PAUSED          ");
  } else {
    lcd.print("Spikes:");
    lcd.print(spikeCount);
    lcd.print("       ");
  }
}

void sendSerialData() {
  

  for (byte i = 0; i < 3; i++) {
    Serial.print(sensor[i]);
    Serial.print(',');
  }

  for (byte i = 0; i < TOTAL_NEURONS; i++) {
    Serial.print(membrane[i]);
    Serial.print(',');
  }

  Serial.print(currentClass);
  Serial.print(',');
  Serial.println(spikeCount);
}

void loop() {
  checkButton();
  readSensors();

  if (!paused) {
    updateNetwork();
  } else {
    for (byte i = 0; i < TOTAL_NEURONS; i++) {
      fired[i] = false;
    }
  }

  updateOutputs();
  updateLCD();
  sendSerialData();

  delay(100);
}