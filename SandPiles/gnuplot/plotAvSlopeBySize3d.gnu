set xrange[4:50]
set yrange[0:*]
f(x) = a*x**(c)+b
c=2./3
a = 0.004
b = 2.9
file = '../data/averageSlope/avSlopeBySize_save3d.dat'
fit f(x) file u 1:($2) via a,b,c
set xrange[0:150]
plot file u 1:($2):3 w yerrorbars,\
	f(x)
