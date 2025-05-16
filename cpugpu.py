import serial
import time
import psutil
import GPUtil

# Replace 'COMX' with the correct COM port for your NodeMCU (e.g., COM3 on Windows or /dev/ttyUSB0 on Linux/Mac)
SERIAL_PORT = 'COM4'
BAUD_RATE = 9600

def get_cpu_usage():
    """Get the CPU usage percentage."""
    return psutil.cpu_percent(interval=1)

def get_gpu_usage():
    """Get the GPU usage percentage."""
    gpus = GPUtil.getGPUs()
    if gpus:
        return gpus[0].load * 100  # Return the first GPU's usage percentage
    return 0.0  # Return 0 if no GPUs are found

def main():
    # Open the serial port
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        print(f"Sending data to {SERIAL_PORT} at {BAUD_RATE} baud...")

        while True:
            # Get system usage data
            cpu_usage = get_cpu_usage()
            gpu_usage = get_gpu_usage()

            # Format the data
            data = f"CPU:{cpu_usage:.1f}% GPU:{gpu_usage:.1f}%\n"
            print(f"Sending: {data.strip()}")

            # Send the data over serial
            ser.write(data.encode('utf-8'))

            # Wait for 1 second before sending the next update
            time.sleep(1)

if __name__ == "__main__":
    main()
