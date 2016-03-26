#
set xrange[1:100]
set yrange[1:10000]
unset logscale

set terminal x11

f(x) = a* x**b
a = 1000
b = -1

fit f(x) "../data/SizeDistribution.dat" u 1:2 via a,b
set logscale xy

plot "../data/SizeDistribution.dat" w lines,\
	f(x)
