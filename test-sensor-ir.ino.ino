// const int sensorPin = 7;    // Pin untuk membaca sensor
// const int ledPin = 13;      // Pin untuk LED indikator

// void setup() {
//   pinMode(sensorPin, INPUT);
//   pinMode(ledPin, OUTPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   int sensorValue = digitalRead(sensorPin);

//   if (sensorValue == LOW) {
//     Serial.println("OBJEK TERDETEKSI");
//     digitalWrite(ledPin, HIGH); // Nyalakan LED
//   } else {
//     Serial.println("TIDAK TERDETEKSI");
//     digitalWrite(ledPin, LOW);  // Matikan LED
//   }

//   delay(200);
// }

const int analogPin = A0;  // Pin untuk membaca nilai analog
const int digitalPin = 8;  // Pin untuk membaca nilai digital
const int ledPin = 13;     // LED indikator pada board

void setup() {
  pinMode(digitalPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(analogPin);    // Membaca nilai analog (0–1023)
  int digitalValue = digitalRead(digitalPin); // Membaca nilai digital (HIGH atau LOW)

  // Menampilkan nilai ke Serial Monitor
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(" | Digital: ");
  Serial.println(digitalValue == LOW ? "Objek Terdeteksi" : "Tidak Terdeteksi");

  // Mengontrol LED indikator
  digitalWrite(ledPin, digitalValue == LOW ? HIGH : LOW);

  delay(200); // Delay untuk stabilitas pembacaan
}
