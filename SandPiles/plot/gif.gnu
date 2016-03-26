load 'blues.pal'
set dgrid3d 50,50,50
set sample 50
set isosample 50
set terminal gif
set output 'real.gif'
set ticslevel 0.1


set contour
unset surface
set cntrparam levels discrete 0.99,1.1

set view map
unset clabel
#plot "contours.dat" u 1:2:3 lc 2 w l lw 6  not

set terminal x11
do for [i=0:9]{


set table sprintf('contours%d.dat',i)
splot sprintf('~/SandPiles/SandPiles/data/cluster%d.dat',i) u 1:2:3 not
unset table
unset contour
plot 'Lattice.dat' u 1:2:3 w image not, sprintf('contours%d.dat',i) u 1:2 lc 2 lw 6 w l not
pause 0.1
}