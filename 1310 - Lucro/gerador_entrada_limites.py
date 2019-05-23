import random

num_instancias = 1000
i=0
instancia = []
while(i<=num_instancias):

	num_dias = 50
	custo_dia = 999
	receita = [999 for i in range(0, num_dias)]

	instancia.append([num_dias, custo_dia, receita])
	i=i+1

arq = open('entrada_gerada.txt', 'w')

for inst in instancia:

	arq.write(str(inst[0]) + '\n') # num_dias
	arq.write(str(inst[1]) + '\n') # custo_dia
	for k in inst[2]: # receitas
		arq.write(str(k) + '\n')


arq.close()