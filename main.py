import serial
import serial.tools.list_ports
import time

# Detect and connect to Arduino
def find_arduino(baudrate=9600, timeout=2):
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        if "Arduino" in p.description or "CH340" in p.description or "USB Serial" in p.description:
            try:
                arduino = serial.Serial(p.device, baudrate=baudrate, timeout=timeout)
                time.sleep(2)  # Give Arduino time to reset
                print(f"Connected to Arduino on {p.device}")
                return arduino
            except Exception as e:
                print(f"Failed to connect on {p.device}: {e}")
    print("Arduino not found.")
    return None

# Send command
def send_command(arduino, motion_type, direction, speed, delay_after=2):
    if not arduino or not arduino.is_open:
        print("Arduino not connected.")
        return
    command = f"{motion_type} {direction} {speed}\n"
    arduino.write(command.encode())
    print(f"Sent: {command.strip()}")
    time.sleep(delay_after)

# Hardcoded movement sequence
def run_motion_sequence(arduino):
    commands = [
        ("straight", "forward", 100, 2),
        ("straight", "backward", 100, 2),
        ("horizontal", "left", 100, 2),
        ("horizontal", "right", 100, 2),
        ("diagonal", "forward_left", 100, 2),
        ("diagonal", "forward_right", 100, 2),
        ("diagonal", "backward_left", 100, 2),
        ("diagonal", "backward_right", 100, 2),
        ("rotate", "left", 100, 4),
        ("rotate", "right", 100, 4),
        ("straight", "forward", 0, 2),  # Stop
    ]

    for motion_type, direction, speed, delay_time in commands:
        send_command(arduino, motion_type, direction, speed, delay_after=delay_time)

# Main
if __name__ == "__main__":
    arduino = find_arduino()
    if arduino:
        try:
            run_motion_sequence(arduino)
        except KeyboardInterrupt:
            print("Interrupted.")
        finally:
            arduino.close()
            print("Connection closed.")
