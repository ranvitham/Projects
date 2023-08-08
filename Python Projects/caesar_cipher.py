Caesar cipher shifts each letter of the alphabet by some fixed amount, 
wrapping at the end of the alphabet and ignoring whitespace."


def encode_caesar(string, shift):
     alpha = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

     #analyzing string
     string = list(string)
     final = []

     for x in string:
          isa = x.isalpha()

          if isa == True:
               loc = alpha.index(x)
               loc = loc + shift
               if loc > 51:
                    nloc = loc - 51
                    loc = nloc + -1
               x = alpha[loc]

          final.append(x)
          finali = "".join([str(item) for item in final])

     return finali
