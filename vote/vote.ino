// Electronic Voting Machine using Arduino UNO
// 3 candidates + 1 reset button
// Votes displayed via Serial (for GUI)

int buttonA = 2;   // Candidate A
int buttonB = 3;   // Candidate B
int buttonC = 4;   // Candidate C
int resetBtn = 5;  // Reset button

int votesA = 0, votesB = 0, votesC = 0;

void setup() {
  Serial.begin(9600);             // Start Serial Communication
  pinMode(buttonA, INPUT_PULLUP); // Using internal pull-up
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(resetBtn, INPUT_PULLUP);
}

void loop() {
  bool aPressed = !digitalRead(buttonA);
  bool bPressed = !digitalRead(buttonB);
  bool cPressed = !digitalRead(buttonC);
  bool resetPressed = !digitalRead(resetBtn);

  // Allow only one valid button press at a time
  if (aPressed && !bPressed && !cPressed) {
    votesA++;
    Serial.println("A:" + String(votesA));
    delay(500); // Debounce
  } 
  else if (!aPressed && bPressed && !cPressed) {
    votesB++;
    Serial.println("B:" + String(votesB));
    delay(500);
  } 
  else if (!aPressed && !bPressed && cPressed) {
    votesC++;
    Serial.println("C:" + String(votesC));
    delay(500);
  }

  // Reset all votes
  if (resetPressed) {
    votesA = votesB = votesC = 0;
    Serial.println("RESET");
    delay(500);
  }
}
