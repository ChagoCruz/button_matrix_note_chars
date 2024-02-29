#include <Arduino.h>
#include <unordered_set>

const int numRows = 3;
const int numCols = 14;

const int rowPins[numRows] = {29, 30, 31};
const int colPins[numCols] = {32, 0, 1, 9, 5, 4, 3, 2, 14, 24, 25, 26, 27, 28};

const char buttonChars[numRows][numCols] = {
  {'\0', '\0', '\0', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'},
  {'\0', 'P', 'Q', 'R', '\0', 'T', 'U', '\0', 'W', 'X', 'Y', '\0', '!', '?'},
  {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '+', '*', '/'}
};

std::unordered_set<char> pressedButtons;

void setup() {
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  for (int j = 0; j < numCols; j++) {
    pinMode(colPins[j], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void scanMatrix() {
  pressedButtons.clear();  // Clear the set before scanning

  for (int i = 0; i < numRows; i++) {
    digitalWrite(rowPins[i], LOW);

    for (int j = 0; j < numCols; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        char pressedChar = buttonChars[i][j];
        if (pressedChar != '\0') {
          pressedButtons.insert(pressedChar);
        }
      }
    }

    digitalWrite(rowPins[i], HIGH);
  }

  if (!pressedButtons.empty()) {
    Serial.print("Pressed buttons: ");
    for (char button : pressedButtons) {
      Serial.print(button);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("No buttons pressed");
  }
}

void loop() {
  scanMatrix();
  delay(100);
}
