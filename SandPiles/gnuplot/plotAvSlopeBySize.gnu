set xrange[0:*]
set yrange[0:*]
f(x) = a*x**(c)+b
c=1./2
a = 0.01
b = 4
fit f(x) '../data/averageSlope/avSlopeBySize_save.dat' u 1:($2-2) via a,b,c
plot '../data/averageSlope/avSlopeBySize_save.dat' u 1:($2-2):3 w yerrorbars,\
	f(x)
