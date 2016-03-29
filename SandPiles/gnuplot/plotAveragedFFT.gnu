
set yrange [1e18:*]
set logscale xy
#unlogscale

file = '../data/dissipation/averagedFFTOfSpectrum.dat'

f(x) = a*(x)**(b) + c

a = 7e21
b = -1
c = 5e20
set xrange [10:100]
fit f(x) file u 1:2 via a,b

set xrange [1:110]
plot file u 1:2:3 w yerrorbars, file u 1:2 w l, f(x)
