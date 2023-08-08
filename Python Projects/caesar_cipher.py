"""
Caesar cipher shifts each letter of the alphabet by some fixed amount, wrapping at 
the end of the alphabet and ignoring whitespace. For example, "Coding is fun" encoded 
using a Caesar cipher with a shift of 3 letters becomes "Frglqj lv ixq." This function 
takes two parameters which are the message and the number of shifts wanted for each
letter.
"""


def encode_caesar(string, shift):
     alpha = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

     #analyzing string
     string = list(string)
     final = []

     for x in string:
          alpha = x.alphalpha()

          if alpha == True:
               location = alpha.index(x)
               location = location + shift
               if location > 51:
                    nlocation = location - 51
                    location = nlocation + -1
               x = alpha[location]

          final.append(x)
          finali = "".join([str(item) for item in final])

     return finali
