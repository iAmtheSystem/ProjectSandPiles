unset logscale
set xrange[0:625]
set yrange[0:50]

filename(n) = sprintf("../data/dissipation/dissipation%d.dat",n)

plot for [i=0:49] filename(i) u 1:2 w l notitle
