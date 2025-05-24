// Pin infrared
const int irPins[] = {A0, A1, A2, A3};

// Motor DC pin
const int ENA = 8;
const int IN1 = 6;
const int IN2 = 7;

// State
String inputString = "";
bool inputComplete = false;

void setup() {
  Serial.begin(9600);

  // Set pin mode infrared
  for (int i = 0; i < 4; i++) {
    pinMode(irPins[i], INPUT);
  }

  // Set motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  stopMotor();
}

void loop() {
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    inputString.trim();

    if (inputString == "BOTOL") {
      int sensorCount = 0;

      for (int i = 0; i < 4; i++) {
        int value = digitalRead(irPins[i]);
        if (value == LOW) { // Jika sensor aktif (IR terhalang)
          sensorCount++;
        }
      }

      int poin = 0;
      if (sensorCount == 2) {
        poin = 5;
      } else if (sensorCount == 3) {
        poin = 10;
      } else if (sensorCount == 4) {
        poin = 15;
      } else {
        poin = 0;
      }

     
      gerakMotor(1); // arah searah
      delay(1000);   // Sesuain sama kecepatan dan durasi buat ke 60 derajat
      stopMotor();

      // Kirim ke Python
      Serial.println("poin:" + String(poin));
      Serial.println("SELESAI");
    }

    else if (inputString == "TIDAK") {
      // Motor berputar -60 derajat
      gerakMotor(-1); //arah kebawah (harusnya)
      delay(1000);
      stopMotor();

      Serial.println("SELESAI");
    }
  }
}

void gerakMotor(int arah) {
  digitalWrite(ENA, HIGH);
  if (arah == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

void stopMotor() {
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
