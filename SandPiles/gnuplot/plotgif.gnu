set terminal gif animate delay 10
set output 'foobar.gif'
set dgrid3d
set hidden3d
set isosample 40
set xrange[-1:100]
set yrange[-1:100]
set zrange[0:5]
set cbrange [2:5]
do for[i=0:999] {
plot sprintf('../data/step%d.dat',i) u 1:2:3 w image 
}
