max=99
for i in `seq 0 $max`
do
	./executar.sh < "Gerador/Entradas/gerada_$i"
done