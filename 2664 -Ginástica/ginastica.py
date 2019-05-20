
def leitura(nome_arquivo):
	arq = open(nome_arquivo, 'r')
	info = arq.read()
	arq.close()
	info = info.split(' ')

	return int(info[0]), int(info[1]), int(info[2])

def faz_combinacoes(values, t, k):
	## a melhor opção é já gerar as opções no formato correto
	pass



if __name__ == '__main__':
	
	t, m, n = leitura('entrada.txt')
	# t é o número de minutos por exercícios
	# m é o valor mínimo de dificuldade
	# n é o valor máximo de dificuldade permitido
	n = n+1
	values = [i for i in range(m, n)]
	lista, comb=[], []
	comb = faz_combinacoes(values, t, 0)
	print(comb)