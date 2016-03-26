load 'blues.pal'
set dgrid3d 50,50,50
set sample 50
set isosample 50
set terminal png
set output 'borders.png'
set ticslevel 0.1
set xrange [0:25]
set yrange [0:25]

set contour
unset surface
set cntrparam levels discrete 0.99,1.1

set view map
unset clabel

set table "contours.dat"
splot "cluster2.dat" u 1:2:3 not
unset table
unset contour

set cbrange [0:5]

plot "Lattice2.dat" u ($1+0.5):($2+0.5):3 w image not, "clusterpoints.dat" u 1:2 lc 2 lw 6 w l not
#plot "contours.dat" u 1:2:3 lc 2 w l lw 6  not