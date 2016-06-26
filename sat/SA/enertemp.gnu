set title 'Temperatura X Tempo'
set xlabel 'Temperatura'
set ylabel 'Tempo'

#set xtics [10:110]
#set yrange[0:0.000012]
#set xrange[0:200]
plot 'out/mediauf20-01.csv' u 2:3 w l title 'oi'

set term jpeg
set output "energytemp.jpeg"
replot