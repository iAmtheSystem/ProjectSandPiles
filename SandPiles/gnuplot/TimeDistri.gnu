file = '../data/TimeDistribution_save100x100.dat'
unset logscale
set xrange[1:100]
set yrange[1:*]

f(x) = a*x**(c)+b

a=1326
b=0
c=1-2.05

d=a
e=b
f=c


g(x) = d*x**(f)+e
fit f(x) file via a,c


set xrange[1:10000]
set yrange[1:10000000]
set logscale xy

plot file u 1:2 w l,\
	g(x),\
	f(x)
