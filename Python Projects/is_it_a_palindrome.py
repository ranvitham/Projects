"""
A palindrome is a word, phrase, or sequence that reads the same backward as 
forward, e.g., madam or nurses run. This function takes in a string and returns
true or false depending on if it's a palindrome.
"""


def pal_func(x):
     if " " in x:
       x = x.lower()
     if " " in x:
         x = x.replace(" ", "")

     y = x[::-1]

     if x == y:
         return True
     if x !=y:
         return False
