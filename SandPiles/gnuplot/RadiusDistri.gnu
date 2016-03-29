file = '../data/RadiusDistribution_save100x100.dat'
unset logscale
set xrange[1:30]
set yrange[1:*]

f(x) = a*x**(c)+b

a=10000
b=0
c=1-2.15


fit f(x) file via a,c


set xrange[1:100]
set yrange[1:*]
set logscale xy

set key below

plot file u 1:2 w l title "Radii of 2500 avalanches in a 2D 50x50 Lattice",\
	f(x) lc 3 title "fitted for the first 30 datapoints"

set output 'RadiusDistribution2D.png'
set terminal png
replot
