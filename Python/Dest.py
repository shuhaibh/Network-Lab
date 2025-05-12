class student:
    def __del__(self):
        print("Deleted Object")

obj = student()
del obj

