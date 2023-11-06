import multiprocessing
tamaño=10000
numbers = list(range(1, tamaño + 1))
#2, 2, 5, 4, 10, 6, 17,…
# 2= 1*1+1,5=2*2+1
# 2=2*1,4=2*2,6=3*2

# Función para calcular 
def A(number):
    #print("holllll")
    result = (number*number)+1
    #print(f"{result}")
    return (number, result)

def B(number):
    #print("***")
    result = (2*number)
    #print(f"{result}")
    return (number, result)
if __name__ == "__main__":
  

     #numbers=[1,2,3,4,5] 
    # Dividir la lista 
    even_numbers = [number for number in numbers ]
    odd_numbers = [number for number in numbers ]

    # Crear un "pool" de procesos con 2 procesadores
    with multiprocessing.Pool(processes=2) as pool:
        # Calcular factoriales de números pares e impares en paralelo
        resultsA= pool.map(A, even_numbers)
        resultsB= pool.map(B, odd_numbers)

    # Combinar y mostrar los resultados
    results = resultsA + resultsB
    results.sort(key=lambda x: x[0])  # Ordenar los resultados por el número original

    for number, result in results:
        #print(f"{number} y {result}")
        print(result)

