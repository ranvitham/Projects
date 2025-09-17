import tkinter as tk
import threading
import socket
import time
import matplotlib.pyplot as plt
import numpy as np
import os

# GLOBAL VARIABLES
gui_send_message = "w\n"
latest_scan_data = []

# TCP Settings
HOST = "192.168.1.1"
PORT = 288

def main():
    global window, Last_command_Label, Bump_Status_Label, Cliff_Status_Label
    global forward_entry, backward_entry, left_entry, right_entry

    window = tk.Tk()
    window.title("CyBot Base Station")

    # Control Buttons
    control_frame = tk.Frame(window)
    control_frame.pack()

    tk.Button(control_frame, text="Ping Scan", command=send_scan).grid(row=0, column=0)
    tk.Button(control_frame, text="IR Scan", command=ir_scan).grid(row=0,column=1)
    tk.Button(control_frame, text="Emergency Stop", command=send_stop).grid(row=1, column=1)
 
    # Move Forward
    tk.Button(control_frame, text="Move Forward", command=send_forward).grid(row=1, column=0)
    #tk.Label(control_frame, text="Forward Distance:").grid(row=1, column=1)
    #forward_entry = tk.Entry(control_frame, width=10)
    #forward_entry.grid(row=1, column=2)

    # Move Backward
    tk.Button(control_frame, text="Move Backward", command=send_backward).grid(row=2, column=0)
    tk.Label(control_frame, text="Backward Distance:").grid(row=2, column=1)
    backward_entry = tk.Entry(control_frame, width=10)
    backward_entry.grid(row=2, column=2)

    # Turn Left
    tk.Button(control_frame, text="Turn Left", command=send_left).grid(row=3, column=0)
    tk.Button(control_frame, text="Turn Left 70",command=send_left_70).grid(row=3, column=1)
    #left_entry = tk.Entry(control_frame, width=10)
    #left_entry.grid(row=3, column=2)
    

    # Turn Right
    tk.Button(control_frame, text="Turn Right", command=send_right).grid(row=4, column=0)
    tk.Button(control_frame, text="Turn Right 70",command=send_right_70).grid(row=4, column=1)
    #right_entry = tk.Entry(control_frame, width=10)
    #right_entry.grid(row=4, column=2)

    # Quit Button
    tk.Button(control_frame, text="Quit", command=send_quit).grid(row=5, column=0, columnspan=2)

    #Input Boxes

    # Status Display
    Last_command_Label = tk.Label(window, text="Last Command Sent: ")
    Last_command_Label.pack()

    Bump_Status_Label = tk.Label(window, text="Bump Sensors: Left=0, Right=0")
    Bump_Status_Label.pack()

    Cliff_Status_Label = tk.Label(window, text="Cliff Sensors: Clear")
    Cliff_Status_Label.pack()

    # Start Client Thread
    my_thread = threading.Thread(target=socket_thread)
    my_thread.start()

    window.mainloop()

def send_scan():
    global gui_send_message
    gui_send_message = "s"
def ir_scan():
    global gui_send_message
    gui_send_message = "i"

def send_stop():
    global gui_send_message

    gui_send_message = "S"

def send_forward():
    global gui_send_message
    global gui_send_val

    gui_send_message = "f"
   # gui_send_val = forward_entry
   

def send_backward():
    global gui_send_message
    global gui_send_val

    gui_send_message = "b"
   # gui_send_val = backward_entry

def send_left():
    global gui_send_message
    global gui_send_val

    gui_send_message = "l"
    #gui_send_val = left_entry

def send_left_70():
    global gui_send_message
    gui_send_message = "L"

def send_right():
    global gui_send_message
    global gui_send_val

    gui_send_message = "r"
    #gui_send_val = right_entry
def send_right_70():
    global gui_send_message
    gui_send_message = "R"

def send_quit():
    global gui_send_message, window
    gui_send_message = "quit\n"
    time.sleep(1)
    window.destroy()

def socket_thread():
    global gui_send_message, Last_command_Label, latest_scan_data, gui_send_val
    direction = ['f', 'b', 'r', 'l', 'L', 'R']

    # Create socket
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    cybot_socket.connect((HOST, PORT))
    cybot = cybot_socket.makefile("rbw", buffering=0)
    

    while gui_send_message != "quit\n":
        # Update GUI
        time.sleep(1)
        
        Last_command_Label.config(text=f"Last Command Sent: {gui_send_message.strip()}")

        if gui_send_message == ("i"):
            cybot.write(gui_send_message.encode())
            handle_scan(cybot)
            time.sleep(1)
            gui_send_message = 'z'
            print(gui_send_message)
        
        if gui_send_message == ("s"):
            cybot.write(gui_send_message.encode())
            handle_scan(cybot)
            time.sleep(1)
            gui_send_message = 'z'
            print(gui_send_message)
        
        

        #adding in other commands
        if gui_send_message in direction:
            cybot.write(gui_send_message.encode())
            time.sleep(1)
            print(gui_send_message)
            #msg = 'Nothing found'
            #msg = cybot.readline().decode()
           # print(msg.strip())
            gui_send_message = 'z'
            print(gui_send_message)
            
            cybot.write(gui_send_message.encode())


    cybot.close()
    cybot_socket.close()

def handle_scan(cybot):
    global latest_scan_data
    
    scan_angles = []
    scan_distances = []
    x = 0 #change as needed to accomidate number of data points

    while (x <= 90):
        rx_message = cybot.readline().decode()
        print(rx_message.strip())
        if rx_message.strip() == "END":
            break
        try:
            parts = rx_message.strip().split()
            angle = int(parts[0])
            distance = float(parts[1])
            scan_angles.append(np.deg2rad(angle))
            scan_distances.append(distance)
            x = x + 1
        except Exception as e:
            print("Failed to parse line:", rx_message)

    latest_scan_data = (scan_angles, scan_distances)
    plot_scan(scan_angles, scan_distances)

def plot_scan(angles, distances):
    plt.figure(figsize=(6,6))
    ax = plt.subplot(111, projection='polar')
    ax.set_theta_zero_location('E')
    ax.set_theta_direction(1)
    ax.plot(angles, distances, marker='o')
    ax.set_title("CyBot Sensor Scan")
    plt.show()

if __name__ == "__main__":
    main()