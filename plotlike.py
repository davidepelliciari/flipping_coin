import numpy as np
import matplotlib.pyplot as plt
import math

fdati = 'likelihood.dat'

theta=np.genfromtxt(fdati,comments="#", usecols=(0), dtype=None, unpack=True)
like=np.genfromtxt(fdati,comments="#", usecols=(1), dtype=None, unpack=True)

plt.plot(theta,like,color='k',linestyle='',marker='.')
plt.title("Likelihood function")
plt.xlabel("theta")
plt.ylabel("Likelihood")
plt.show()
