set title 'Temperatura X Probabilidade'
set xlabel 'Temperatura'
set ylabel 'Probabilidade'

#set xtics [10:110]
#set yrange[0:0.000012]
#set xrange[574:1350]
set logscale x;
set logscale y;
plot 'out/mediauf20-01.csv' u 2:5 w l title 'oi'

set term jpeg
set output "probXtempe.jpeg"
replot
