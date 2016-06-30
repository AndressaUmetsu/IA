set title 'Energia por Estado'
set xlabel 'Estado'
set ylabel 'Energia'

set terminal pngcairo
#set output 'plots/Energy20.png'
#set output 'plots/Energy50.png'
#set output 'plots/Energy75.png'
#set output 'plots/Energy100.png'
set output 'plots/Energy250.png'

#set xtics [10:110]
#set yrange[0:0.000012]
#set xrange[0:200]

set logscale x;
#set logscale y;

set grid
set border
set tics nomirror

#plot 'out/mediauf20-01.csv' u 1:3 w l title 'Energia uf20'
#plot 'out/mediauf50-01.csv' u 1:3 w l title 'Energia uf50'
#plot 'out/mediauf75-01.csv' u 1:3 w l title 'Energia uf75'
#plot 'out/mediauf100-01.csv' u 1:3 w l title 'Energia uf100'
plot 'out/mediauf250-01.csv' u 1:3 w l title 'Energia uf250'




