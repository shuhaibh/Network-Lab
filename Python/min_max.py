def min_max(lst):
    """
    Finds the minimum and maximum values in a list.

    Parameters:
    lst (list): A list of comparable elements.

    Returns:
    tuple: A tuple containing the minimum and maximum values, or (None, None) if the list is empty.
    """
    if not lst:
        return None,None
    else:
        return min(lst),max(lst)
    
if __name__ =="__main__":
    numbers = [1,5,6,2,9]
    minimum,maximum = min_max(numbers)
    print(f"Maximum = {maximum} , Minimum = {minimum}")


