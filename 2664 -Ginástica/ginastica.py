lista = []
def ginastica_pd(d, i, t): 


    if(i < d[1] or i > d[2]):
        return 0
    #print("Esse é o valor: ", i, " esse é o t: ", t)
    #print(i, t)
    if t == 1:
        return 1
    
    soma = ginastica_pd(d, i-1, t-1) + ginastica_pd(d, i+1, t-1)
    
    return soma 
  
#Driver Code 
if __name__=='__main__': 
    t = 30
    m = 2
    n = 5
    d = [t, m, n]
    soma = 0
    for i in range(m, n+1):
        soma = ginastica_pd(d, i, t) + soma
    print(soma)
      
#This code is contributed by sahilshelangia 