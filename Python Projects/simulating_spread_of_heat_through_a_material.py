"""
This function takes in a 2-dimensional numpy-array containing heat values and uses the finite 
difference method to produce the heat distribution for that material at the next time step. 

The heat equation is a partial differential equation that describes the flow 
of heat through space and time. In the following equation, the function 𝑢(𝑥,𝑦,𝑡)
describes how much heat resides at the location (𝑥,𝑦) at time 𝑡:

∂𝑢/∂𝑡 −𝛼(∂^2/𝑢∂^𝑥2 + ∂^2𝑢/∂𝑦^2) = 0

Numerically, this equation can be written out as:

𝑢(𝑡)𝑖𝑗= (𝑢(𝑡−1)𝑖+1, 𝑗+𝑢(𝑡−1)𝑖−1, 𝑗+𝑢(𝑡−1)𝑖, 𝑗+1+𝑢(𝑡−1)𝑖, 𝑗−1) / 4
 
That is, 𝑢(𝑡)𝑖𝑗 is the heat at grid location (𝑖,𝑗) at time-step 𝑡. Its value is given by the 
average of the heat of all four of its neighboring grid positions from time-step 𝑡−1.
"""

import numpy as np

def evolve_heat_slow(u):
    npp = np.copy(u)
    nr = len(npp)
    nc = len(npp[0])
    rows = []
    cols = []
    for i in range(0, nr):
        rows.append(i)
    for x in range(0, nc):
        cols.append(x)
     
    for i in rows:
        for j in cols:
            nv = []
            if i + 1 == nr:
                nv.append(u[0, j])
            else:
                nv.append(u[i+1, j])


            nv.append(u[i-1, j])

            if j + 1 == nc:
                nv.append(u[i, 0])
            else:
                nv.append(u[i, j+1])

            nv.append(u[i, j-1])

            total = 0
            for ele in range(0, len(nv)):
                total = total + nv[ele]

               
            total /= 4
               

            npp[i, j] = total
     
    npp[0, :] = u[0, :]
    npp[-1, :] = u[-1, :]
    npp[:, 0] = u[:, 0]
    npp[:, -1] = u[:, -1]

    return npp
