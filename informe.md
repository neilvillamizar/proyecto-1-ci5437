## Detalles de la implementación

### Algoritmos

#### BFS
Para la pregunta de analizar los arboles de búsqueda se implemento BFS con y sin eliminación de duplicados, esto porque como todos los movimientos tienen costo 1, UCS terminaría haciendo un recorrido al estilo de BFS. Para la eliminación de duplicados se creo un set de estados en el que puedes insertar, consultar y eliminar.

#### A*
Esta implementación es igual a la de las laminas. Se uso la priority_queue que trae c++, multiplicando los valores por -1 al insertarlos ya que esta pone a los valores mas altos primero. Y también se creo un map de estados para guardar el costo de cada uno.

#### IDA*
Para ida* se utilizo la implementación que solo necesita un nodo, con una pequeña modificación, el nodo no es global si no que la función recibe el apuntador a ese nodo, esto hace que gaste un poco mas en memoria pero no es una cantidad relevante, es del mismo tamaño del vector de acciones tomadas. Para la eliminación de duplicados se uso el set de estados, de forma de que no pases por nodos que ya están en el camino actual. 

Cada una de estas implementaciones cuenta los nodos creados por altura y el tiempo de ejecución, también en caso de que se excedan de algún tiempo que se especifique, detienen la búsqueda.

### Heurísticas

#### Distancia Manhattan
Se hizo una implementación que toma tiempo O(tamaño de la matriz) y espacio O(1). Básicamente tomamos los valores de la matriz en orden, sabemos la posición en la que están y la posición en la que deberían estar, digamos X y Y, si la matriz en NxN, al hacer X/N obtenemos la fila en la que esta y con X%N la columna, y esto aplica también para Y, por lo que así podemos calcular la distancia manhattan de forma eficiente.

#### PDB aditivas y max
Aquí solo se va calculando el valor de la heurística de cada abstracción y vamos aplicando suma o max dependiendo del caso.

### PDB

#### 15 puzzle
Creamos 3 abstracciones, mapeando estados a blanks, en las que dividimos los estados de la siguiente forma:
1. 1, 2, 3, 6, 7
2. 4, 5, 8, 9, 12, 13
3. 10, 11, 14, 15

#### 24 puzzle
Creamos 6 abstracciones, mapeando estados a blanks, en las que dividimos los estados de la siguiente forma:
1. 1, 2, 6, 7
2. 3, 4, 8, 9
3. 5, 10, 15, 20
4. 11, 12, 13, 14
5. 16, 17, 18, 19
6. 21, 22, 23, 24

#### Rubik

#### TopSpin

#### Hanoi

### Casos generados

#### 24 puzzle
Para este problema los casos que venían dados tardaban mucho en correr, por lo que se crearon nuevos casos fáciles, medios y difíciles.

### PSVN usados

#### 15 puzzle y 24 puzzle
Se creo un programa en c++ que imprime el psvn del n-puzzle, crea un dominio con n<sup>2</sup> piezas, una b (blank) y los numeros [1, n<sup>2</sup>), los movimientos son mover el blank a cualquier vecino valido y el goal es b 1 2 3 ... n<sup>2</sup>-1.


#### TopSpin 
Aqui usamos el psvn que fue entregado, pero se le elimino el ultimo elmento del vector ya que no era relevante.

#### Otros problemas
Para los demas fueron utilizados los psvn entregados sin modificarlos.
