from random import randint
N = 1000 #linhas
M = 1000 #colunas
NUM_MESAS = 1000000

def gerar_mesa():
    global N
    global M
    return "{} {}\n".format(randint(1,N/2),randint(1,M/2))
def gerar_ponto():
    ocupado = '#'
    vazio = '.'
    var = randint(1,6)
    if var > 5:
        return ocupado
    else:
        return vazio
def gerar_planta():
    sala = ""
    for i in range(N):
        for j in range(M):
            sala += gerar_ponto()
        sala += '\n'
    return sala

for testes in range(0, 100):
    arquivo = "{} {}\n".format(N, M)
    arquivo += gerar_planta()
    arquivo += "{}\n".format(NUM_MESAS)
    for i in range(NUM_MESAS):
        arquivo += gerar_mesa() 

    text_file = open("Entradas/gerada_gigante_"+str(testes), "w")
    text_file.write("{}".format(arquivo))
    text_file.close()
    break