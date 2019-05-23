import sys

def leitura():

	while(i)

	return num_dias, custo_dia, list(map(lambda x: int(x), info))

def leitura_teclado():

	info = []
	for line in sys.stdin:
		if line.replace('\n', '') == 'EOF':
			break
		info.append(int(line))
	num_dias =  info[0]
	custo_dia = info[1]
	info.pop(0)
	info.pop(0)
	return num_dias, custo_dia, info

def soma_subvetor(valores, num_dias): # algoritmo proposto em sala de aula pelo vinicius
	
	if(len(valores)==1):
		return max(valores[0], 0)

	x = soma_subvetor(valores[:-1], num_dias)

	
	s = 0
	i = len(valores)-1
	if len(valores) <= num_dias:
		while(i>0):
			s += valores[i]
			if(s>x):
				x = s
			i=i-1
	
	return x


if __name__ == '__main__':
	
	num_dias, custo_dia, valores = leitura()
	
	if num_dias == 0:
		s = 0
	if len(valores) == 0:
		s = 0
	if num_dias>0 and len(valores)>0:
		valores = list(map(lambda x: x-custo_dia, valores))
		s = soma_subvetor(valores, num_dias)

	print(s)
