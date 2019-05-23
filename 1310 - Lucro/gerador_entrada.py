import random

num_instancias = random.randint(1, 1000)
i=0
instancia = []
while(i<=num_instancias):

	num_dias = random.randint(1, 50)
	custo_dia = random.randint(0, 1000)
	receita = [random.randint(0, 1000) for i in range(0, num_dias)]

	instancia.append([num_dias, custo_dia, receita])
	i=i+1

arq = open('entrada_gerada.txt', 'w')

for inst in instancia:

	arq.write(str(inst[0]) + '\n') # num_dias
	arq.write(str(inst[1]) + '\n') # custo_dia
	for k in inst[2]: # receitas
		arq.write(str(k) + '\n')


arq.close()