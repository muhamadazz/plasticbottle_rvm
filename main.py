import cv2
import serial
import time
from ultralytics import YOLO
from utils import find_arduino_port  # pastikan file utils.py ada di folder yang sama

# Cari port Arduino
port = find_arduino_port()
if port is None:
    raise Exception("❌ Arduino tidak ditemukan! Pastikan Arduino tersambung.")
# Load YOLO model
model = YOLO('best.pt')

# Koneksi serial ke Arduino (ganti COM6 sesuai port kamu)
arduino = serial.Serial(port, 9600, timeout=1)
time.sleep(2)

# Buka kamera
cap = cv2.VideoCapture(0)

detected = False
start_time = time.time()

print("🕵️ Mendeteksi botol selama 10 detik...")

while time.time() - start_time < 20:
    ret, frame = cap.read()
    if not ret:
        continue

    # Deteksi dengan YOLO
    results = model.predict(frame, conf=0.5)

    # Gambar bounding box dan label (opsional)
    for result in results:
        boxes = result.boxes
        for box in boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])
            label = result.names[int(box.cls[0])]
            conf = box.conf[0]

            # Gambar kotak dan label ke frame
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(frame, f"{label} {conf:.2f}", (x1, y1 - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

            if "PlasticBottle" in label:
                detected = True
                break

    # ✅ Tampilkan hasil deteksi
    cv2.imshow("Deteksi Botol", frame)

    if detected:
        break

    # Tombol keluar manual
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Tutup kamera dan jendela
cap.release()
cv2.destroyAllWindows()

# Kirim perintah ke Arduino
if detected:
    print("✅ Botol terdeteksi, kirim 'BOTOL'")
    arduino.write(b'BOTOL\n')
else:
    print("❌ Tidak ada botol, kirim 'TIDAK'")
    arduino.write(b'TIDAK\n')

# Tunggu respons dari Arduino
while True:
    if arduino.in_waiting:
        response = arduino.readline().decode().strip()
        print(f"📥 Arduino: {response}")
        if response == "SELESAI":
            break

arduino.close()
