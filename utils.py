import serial.tools.list_ports

def find_arduino_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if 'Arduino' in port.description or 'CH340' in port.description or 'USB-SERIAL' in port.description:
            return port.device  # contoh: 'COM3'
    return None
