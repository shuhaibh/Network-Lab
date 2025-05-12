import tkinter as tk
import time


def age():
    birthdate_str=inp.get()
    try:
        day,month,year = map(int,birthdate_str.split('-'))
        t = time.localtime()
        years = t.tm_year-year
        if(t.tm_mon,t.tm_mday)<(month,day):
            years -= 1
        out.delete(0,tk.END)
        out.insert(0,f"age:{years}")
    except Exception:
        out.delete(0, tk.END)
        out.insert(0, "Invalid date format")
    
window=tk.Tk()

lb = tk.Label(window,text="Enter the Birthdate:(dd-mm-yyyy)")
lb.pack()

inp=tk.Entry(window)
inp.pack()

but=tk.Button(window,text="Calculate Age",command=age)
but.pack()

out=tk.Entry(window)
out.pack()

window.mainloop()
