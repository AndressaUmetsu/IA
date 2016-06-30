set title 'Temperatura X Tempo'
set xlabel 'Tempo'
set ylabel 'Temperatura'

set terminal pngcairo
set output 'plots/Temperature.png'

set autoscale

set grid
set border
set tics nomirror

plot 'out/mediauf20-01.csv'  u 1:2 w l title 'Temperatura'
