# Algoritmos de ordenação: análise de complexidade

O objetivo desse trabalho é realizar a análise individual dos algoritmos de 
ordenação a partir do tempo necessário para ordenar vetores e da quantidade de comparações e movimentações (que também implicam no tempo de execução do 
algoritmo) a partir das seguintes características: os vetores podem ser organizados de forma crescente, decrescente e desordenados; o tamanho do vetor varia entre 100 e 100.000.

Para verificar a quantidade de comparações e movimentações, foram colocadas 
variáveis contadoras, uma que considera qualquer comparação entre chaves de 
registros e outra que considera quaisquer trocas e movimentações dos registros.

Em relação a contagem de tempo, foi utilizado a biblioteca <windows.h>, que 
disponibiliza as funções QueryPerformanceFrequency e QueryPerformanceCounter, nas quais possibilitam parametrizar o tempo gasto dos algoritmos. 

Por último, a geração de vetores para uso como entradas foi feito utilizando um algoritmo em C, e a geração de gráficos, em python. Cada algoritmo de ordenação realiza a leitura dos arquivos de entrada e gera arquivos de saída separados em comparações, movimentações e tempo gasto, os quais são lidos pelo algoritmo em python, que gera os gráficos em HTML (os quais estão presentes em formato de link no nome de cada algoritmo aqui apresentado e podem ser acessados caso os HTMLs estejam nas devidas pastas). Especificações com mais detalhes estão presente no arquivo `README(especificacoes_dos_arquivos)`.

## Conclusões
Considerando o campo temporal, em geral, o quick sort e o radix sort foram os melhores, sendo que o quick se saiu melhor em entradas ordenadas ou de tamanho menor e o radix, em entradas maiores e aleatórias.

Em casos menores, os termos descartados pela complexidade pesam mais, 
então a criação de buckets e a alocação de memória adicional podem ter desacelerado o radix, além de que o log(n) é tão pequeno quanto o parâmetro d do radix nesse caso. Isso também vale para a entrada inversa em relação a criação de buckets, que desaceleram o radix. Enfim, todas essas características culminam para o radix obter maiores números de movimentações de registros. Contudo, em casos maiores, a complexidade detém uma maior acurácia e a linearidade para o radix, fazendo com que ele ultrapasse no caso das entradas aleatórias.

No caso das entradas ordenadas, essa característica em conjunto da 
implementação da mediana na escolha do pivô proporciona o melhor estado para o quick sort, dividindo os subproblemas de forma altamente balanceada. Enquanto isso, o radix não se beneficia com a ordenação. Além disso, o quick sort apresentou valores menores de movimentação de registros, implicando em uma quantidade de rotinas reduzida.

Dado essas duas análises, o quick sort se sai melhor em um geral, mas em 
casos realistas (dados te magnitude parecida e em ordem aleatória), o radix pode acabar sendo mais eficiente.

Importante frisar que há outros algoritmos que ficam próximos, que são o heap sort e o merge sort, principalmente por apresentarem complexidade parecida, mas perdem tempo na construção de estruturas para a ordenação, assim possuindo grandes níveis de comparações e, principalmente, movimentações.

Sobre os piores algoritmos, iniciando no quesito temporal, pode-se classificar o bubble, o count, o insertion e o selection. Esses são algoritmos que apresentam complexidade quadrática, fazendo com que, mesmo que relativamente simples, detenham baixa eficiência.

A princípio, o count e o selection podem parecer piores por não se beneficiam da ordenação, porém, se desconsiderar o caso específico das entradas ordenadas e considerar entradas mais realistas, o bubble sort proporciona o maior tempo entre os algoritmos, devido à sua grande quantidade de comparações e movimentações realizadas maiores ou iguais a dos outros. Assim, o bubble sort pode ser considerável como o pior algoritmo de ordenação.
