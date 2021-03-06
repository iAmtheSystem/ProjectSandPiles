file = '../data/SizeDistribution_save100x100.dat'
unset logscale
set xrange[1:200]
set yrange[1:*]

f(x) = a*x**(c)+b

a=10000
b=0
c=1-2.15


fit f(x) file via a,c


set xrange[1:*]
set yrange[1:*]
set logscale xy

plot file u 1:2 w l,\
	f(x)
