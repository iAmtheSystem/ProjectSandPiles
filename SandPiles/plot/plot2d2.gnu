	#set view map
#set dgrid3d
#set contour base
#set surface
# set nosurface
#set style data lines
#set grid
set terminal png
set output 'real.png'

set dgrid3d
set contour base
#splot 'copy.dat' 


set dgrid3d
#set hidden3d
#set samples 5
#set isosamples 5
set xrange[-1:25]
set yrange[-1:25]
set zrange[0:5]
set cbrange [0:7]
#set view map
set xlabel "x"
set ylabel "y"
#set pm3d
plot 'Lattice.dat' u 1:2:3 w image, \
'copy.dat' w image
      #set output "vorher.png"
      #splot '../2d_after.dat' u 1:2:3
      #set terminal x11
      #set key below
      #do for [i=0:999] {
    #plot sprintf('../data/step%d.dat',i) u 1:2:3 w image title sprintf('Step%d.dat',i);
    #pause 0.1
    #}

