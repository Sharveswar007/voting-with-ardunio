import tkinter as tk
import serial

# Change COM port accordingly (Windows: "COM3", Linux: "/dev/ttyUSB0", Mac: "/dev/cu.usbmodem...")
arduino = serial.Serial("COM5", 9600)

# Create Tkinter window
root = tk.Tk()
root.title("Electronic Voting Machine")
root.geometry("400x300")

# Variables to store votes
votesA, votesB, votesC = tk.IntVar(), tk.IntVar(), tk.IntVar()

# Labels
tk.Label(root, text="Candidate A", font=("Arial", 16)).pack()
tk.Label(root, textvariable=votesA, font=("Arial", 16)).pack()

tk.Label(root, text="Candidate B", font=("Arial", 16)).pack()
tk.Label(root, textvariable=votesB, font=("Arial", 16)).pack()

tk.Label(root, text="Candidate C", font=("Arial", 16)).pack()
tk.Label(root, textvariable=votesC, font=("Arial", 16)).pack()

# Function to read data from Arduino
def update_votes():
    if arduino.in_waiting > 0:
        data = arduino.readline().decode().strip()
        if data.startswith("A:"):
            votesA.set(int(data.split(":")[1]))
        elif data.startswith("B:"):
            votesB.set(int(data.split(":")[1]))
        elif data.startswith("C:"):
            votesC.set(int(data.split(":")[1]))
        elif data == "RESET":
            votesA.set(0)
            votesB.set(0)
            votesC.set(0)
    root.after(100, update_votes)

# Start updating votes
update_votes()

# Run GUI
root.mainloop()
