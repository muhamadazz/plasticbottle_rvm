// === PIN INFRARED ===
const int ir1Pin = 3;   // IR sensor 1
const int ir2Pin = 4;   // IR sensor 2

String inputString = "";

void setup() {
  Serial.begin(9600);

  pinMode(ir1Pin, INPUT);
  pinMode(ir2Pin, INPUT);
}

void loop() {
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    inputString.trim();

    if (inputString == "BOTOL") {
      int sensor1 = digitalRead(ir1Pin);
      int sensor2 = digitalRead(ir2Pin);

      int sensorCount = 0;
      if (sensor1 == LOW) sensorCount++;  // LOW = terhalang
      if (sensor2 == LOW) sensorCount++;

      int poin = 0;
      if (sensorCount == 1) poin = 5;
      else if (sensorCount == 2) poin = 10;

      Serial.println("poin:" + String(poin));
      Serial.println("SELESAI");
    }

    else if (inputString == "TIDAK") {
      // Jika tidak ada botol, tetap kirim poin 0 dan selesai
      Serial.println("poin:0");
      Serial.println("SELESAI");
    }
  }
}
