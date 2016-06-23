set title 'temperatura'
set xlabel 'iteração'
set ylabel 'temperatura'
#set xtics [10:110]
#set yrange[0:0.000012]
set xrange[574:1350]


plot 'outTemp.csv' u 1:2 w l title 'Temperature'

set term jpeg
set output "TempoDijkstra.jpeg"
replot
