import tkinter as tk
from tkinter import ttk, messagebox
import psycopg2

# Initialize the main window
root = tk.Tk()
root.title("Library Management System")
root.geometry("1200x700")
root.configure(bg="#E6F3F3")

# Sidebar Frame
sidebar_frame = tk.Frame(root, bg="#FFFFFF", width=400)  # Set desired width
sidebar_frame.pack(side="left", fill="y")  # Fill vertically

# Top logo and title section
top_frame = tk.Frame(sidebar_frame, bg="#FFFFFF")
top_frame.pack(pady=(20, 10))
tk.Label(top_frame, text="Library Management", font=("Poppins", 14, "bold"), bg="#FFFFFF", fg="#2E3A59").pack()

# Selected indicator frame
selected_indicator_frame = tk.Frame(sidebar_frame, bg="#2E3A59", width=5, height=50)
selected_indicator_frame.place(x=0, y=190)  # Start with the first button selected

# Helper function to update selected item indicator
def select_sidebar_item(y_position):
    selected_indicator_frame.place(y=y_position)

# Create a frame for the sidebar buttons
button_frame = tk.Frame(sidebar_frame, bg="#FFFFFF")
button_frame.pack(expand=True, pady=(20, 0))  # This can be adjusted

# Function to create sidebar buttons
def create_nav_button(text, command, y_position):
    label = tk.Label(
        button_frame,  # Change this to button_frame
        text=text,
        font=("Poppins", 14),
        bg="#FFFFFF",
        fg="#2E3A59",
        cursor="hand2"
    )
    label.bind("<Button-1>", lambda e: [command(), select_sidebar_item(y_position)])
    label.bind("<Enter>", lambda e: label.config(fg="#0056b3"))  # Change color on hover
    label.bind("<Leave>", lambda e: label.config(fg="#2E3A59"))  # Revert color on leave
    label.pack(fill="x", padx=10, pady=5)  # Adjust padding as needed

# Create sidebar buttons
create_nav_button("Add User", lambda: load_buttons(), 190)
create_nav_button("Add Book", lambda: load_form("Add Book"), 250)
create_nav_button("Record", lambda: load_form("Record"), 310)
create_nav_button("Retrieve", lambda: load_form("Retrieve"), 370)

# Main Content Frame
content_frame = tk.Frame(root, bg="#C8E6E5", padx=20, pady=20)
content_frame.pack(side="right", fill="both", expand=True)

# Run the Tkinter main loop
root.mainloop()