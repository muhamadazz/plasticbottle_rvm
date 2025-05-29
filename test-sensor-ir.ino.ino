// Pin sensor IR 3-pin
const int ir3Pin1 = 7;
const int ir3Pin2 = 8;
const int ir3Pin3 = 9;

// Pin sensor IR 4-pin
const int ir4DigitalPin = 10;
const int ir4AnalogPin = A0;

void setup() {
  // Inisialisasi pin sebagai input
  pinMode(ir3Pin1, INPUT);
  pinMode(ir3Pin2, INPUT);
  pinMode(ir3Pin3, INPUT);
  pinMode(ir4DigitalPin, INPUT);

  // Memulai komunikasi serial
  Serial.begin(9600);
}

void loop() {
  // Membaca sensor IR 3-pin
  int ir3Val1 = digitalRead(ir3Pin1);
  int ir3Val2 = digitalRead(ir3Pin2);
  int ir3Val3 = digitalRead(ir3Pin3);

  // Membaca sensor IR 4-pin
  int ir4DigitalVal = digitalRead(ir4DigitalPin);
  int ir4AnalogVal = analogRead(ir4AnalogPin);

  // Menampilkan hasil pembacaan
  Serial.println("=== Pembacaan Sensor ===");
  Serial.print("IR3-1 (D7): ");
  Serial.println(ir3Val1 == LOW ? "Objek Terdeteksi" : "Tidak Terdeteksi");

  Serial.print("IR3-2 (D8): ");
  Serial.println(ir3Val2 == LOW ? "Objek Terdeteksi" : "Tidak Terdeteksi");

  Serial.print("IR3-3 (D9): ");
  Serial.println(ir3Val3 == LOW ? "Objek Terdeteksi" : "Tidak Terdeteksi");

  Serial.print("IR4 Digital (D10): ");
  Serial.println(ir4DigitalVal == LOW ? "Objek Terdeteksi" : "Tidak Terdeteksi");

  Serial.print("IR4 Analog (A0): ");
  Serial.println(ir4AnalogVal);

  Serial.println("------------------------");
  delay(500); // Delay untuk stabilitas pembacaan
}
