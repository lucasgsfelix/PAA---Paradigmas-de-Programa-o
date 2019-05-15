
def leitura(nome_arquivo):
	arq = open(nome_arquivo, 'r')
	info = arq.read()
	arq.close()
	info = info.split(' ')

	return int(info[0]), int(info[1]), int(info[2])

def faz_combinacoes(values):

	pass


if __name__ == '__main__':
	
	t, m, n = leitura('entrada.txt')
	n = n+1
	values = [i for i in range(m, n)]
	faz_combinacoes(values)