
from math import *

d=80

#1st coefficient
sinc=[1/d]
for i in range(1,80):
    #SINC = sin(x) / x
    #d: is scale factor
    #Multiply by 2 for all except the first coefficient
    sinc += [ 2*( sin(pi*(i)/d) / (pi*(i)/d) )/d ] #sinc

#Create Binary values
coefficients = []
for i,s in enumerate(sinc):
    binary = round(s*0x100000)
    if binary < 0: binary += (1<<24)

    coefficients += [binary]

#Print values
for i in range(len(coefficients)):
    print(F"{i:2d}: {sinc[i]:+8f} 0x{coefficients[i]:06X}")

#Create initialization code
for i in range(len(coefficients)):
    print(F"    SYNTH_FILTER_COEFF_REG(bank, {i}) = 0x{coefficients[i]:06X};")

#Accuracy check
accum=0
for s in sinc:
    accum+=s
print(F"Sum: {accum}") #Should be as close to 1 as possible

accum=0
