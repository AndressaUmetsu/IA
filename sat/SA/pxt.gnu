set title 'Probablidade de Aceitação'
set xlabel 'Temperatura'
set ylabel 'Probabilidade'

set terminal pngcairo
set output 'plots/ProbAccept20.png'
#set output 'plots/ProbAccept50.png'
#set output 'plots/ProbAccept75.png'
#set output 'plots/ProbAccept100.png'
#set output 'plots/ProbAccept250.png'


#set xtics [10:110]
#set yrange[0:0.000012]
#set xrange[574:1350]

set logscale x;
set logscale y;

set grid
set border
set tics nomirror

plot 'out/Accept0uf20-01.csv' u 1:2 w l title 'Probabilidade uf20'
#plot 'out/Accept0uf50-01.csv' u 1:2 w l title 'Probabilidade uf50'
#plot 'out/Accept0uf75-01.csv' u 1:2 w l title 'Probabilidade uf75'
#plot 'out/Accept0uf100-01.csv' u 1:2 w l title 'Probabilidade uf100'
#plot 'out/Accept0uf250-01.csv' u 1:2 w l title 'Probabilidade uf250'









