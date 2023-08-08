"""
The relaxation method allows one to "guess" a fixed-point solution, and then iteratively
improve upon this guess until one has arrived at a value that is sufficiently close to 
the true fixed-point.

To see how close the guesses are to the fixed point the following formula gives an 
upper-bound estimate of how close 𝑥𝑛 is to a true fixed point:

𝜖𝑛=|((𝑥𝑛−𝑥𝑛−1)^2) / (2𝑥𝑛−1−𝑥𝑛−2−𝑥𝑛)|


This relaxation function accepts four arguments:
   - a Python function, which accepts a number as an input, and returns a float as an output
   - an initial guess for the fixed-point, 𝑥0, a floating-point number
   - a tolerance value, a positive-valued floating-point number
   - a max number of iterations that your algorithm is permitted to run

"""

def relaxation_method(func, xo, tol, max_it):
    i = 0
    results = []
    e = 100

    if max_it == 0:
        return results

    for i in range(0,max_it):
        if i == 0:
            results.append(xo)
        elif i < 3:
            results.append(func(results[-1]))
        else:
            num = (results[-1] - results[-2])**2
            dem = 2*results[-2] - results[-3] - results[-1]
            if dem == 0:
                dem = 1e-14
            e = abs(num/dem)
            
            if tol < e:
                results.append(func(results[-1]))
            else:
                return results
        i+=1
   
    return results
