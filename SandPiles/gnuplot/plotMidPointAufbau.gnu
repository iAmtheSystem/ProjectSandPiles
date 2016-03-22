# set view map
# set dgrid3d
# set contour base
# set surface
# set nosurface
# set style data lines
# set grid
set dgrid3d
# set hidden3d
# set isosample 40
set xrange[-1:20]
set yrange[-1:20]
set zrange[0:5]
set cbrange [0:6]
set terminal png
#set output "nachher.png"
#splot '../2d_before.dat' u 1:2:3 
#set output "vorher.png"
#splot '../2d_after.dat' u 1:2:3
set terminal x11
set key below
# plot sprintf('../data/Lattice.dat') u 1:2:3 w image title sprintf('Lattice.dat');

do for [i=0:40000] {
plot sprintf('../data/averageSlope/step%d.dat',i) u 1:2:3 w image title sprintf('Step%d.dat',i);
pause 0.05
}

