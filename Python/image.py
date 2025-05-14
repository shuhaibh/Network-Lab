#image.py
from tkinter import *
from PIL import ImageTk,Image

root = Tk()

canvas = Canvas(root,width=300,height=300)
canvas.pack()
img=ImageTk.PhotoImage(Image.open("image.jpg"))
canvas.image = img  # Keep a reference to avoid garbage collection
canvas.create_image(20,20,anchor=NW,image=img)
mainloop()