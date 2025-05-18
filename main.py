import cv2
import serial
import time
from ultralytics import YOLO 


# Load model deteksi
model = YOLO('best.pt')

# Koneksi ke Arduino (cek COM port nya dulu pal itu pake apa, misalnya "COM3" atau "/dev/ttyACM0")
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)  # Waktu tunggu koneksi

# Inisialisasi kamera
cap = cv2.VideoCapture(0)

detected = False
start_time = time.time()

print("Mendeteksi botol selama 10 detik...")

while time.time() - start_time < 10:
    ret, frame = cap.read()
    if not ret:
        continue

    # Deteksi botol
    results = model.predict(frame, conf=0.5)
    for result in results:
        for label in result.names.values():
            if "PlasticBottles" in label.lower() or "PlasticBottles" in label:
                detected = True
                break

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    if detected:
        break

cap.release()
cv2.destroyAllWindows()

# Kirim perintah ke Arduino
if detected:
    print("✅ Botol terdeteksi, kirim sinyal ke Arduino.")
    arduino.write(b'BOTOL\n')
else:
    print("❌ Tidak ada botol, kirim sinyal ke Arduino.")
    arduino.write(b'TIDAK\n')

# Tunggu respons dari Arduino
while True:
    if arduino.in_waiting:
        response = arduino.readline().decode().strip()
        print(f"📥 Dari Arduino: {response}")
        if response == "SELESAI":
            break

arduino.close()
