set xrange[0:*]
set yrange[0:*]
f(x) = a*x+b
file = "../data/averageSlope/avSlopeByDimension.dat"
fit f(x) file u 1:($2/$4):3 via a,b
plot file u 1:2:3 w yerrorbars,\
	file u 1:4 title 'zk',\
	file u 1:($2/$4):3 w yerrorbars,\
	f(x)
