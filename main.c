#include <stdio.h>
#include <stdlib.h>

int merge(int *input, int l, int mid, int r){ // Processo de intercalação
	int cnt_inv = 0;
	int i = l;
	int j = mid+1;
	int k = 0;

	int *aux = malloc((r-l+1) * sizeof(int));

	while(i <= mid && j <= r){
		// Verificar qual o menor elemento entre as partes
		if(input[i] <= input[j])
			aux[k++] = input[i++]; // Se o elemento da primeira metade é menor, adiciona ele no auxiliar e vai pro próximo elemento
		else {
			aux[k++] = input[j++]; // Caso o elemento da primeira metade seja maior

			// A ideia do problema é contar o número de inversões, se um elemento da primeira metade é maior que um da segunda,
			// significa que no vetor original ele estava antes de um elemento maior (inversão)
			
			// Lembrando que durante a intercalação das partes, todos os elementos à direita de um elemento (dentro de sua própria metade) são maiores que ele
			// então se um elemento da primeira metade é maior que um da segunda, todos os elementos a direita dele também o são
			cnt_inv += mid-i+1;
		}
	}

	// Caso restem elementos na primeira metade
	while(i <= mid)
		aux[k++] = input[i++];

	// Caso restem elementos na segunda metade
	while(j <= r)
		aux[k++] = input[j++];

	// Atualiza o vetor principal com base no auxiliar que está ordenado
	for(i = l, k = 0; i <= r; i++, k++)
		input[i] = aux[k];

	free(aux);
	return cnt_inv;
}

int merge_sort(int *input, int l, int r){
	int mid, cnt_inv = 0;

	if(r > l){
		// Chama a ordenação pras metades do vetor (dividir)
		mid = (l+r)/2;
		cnt_inv += merge_sort(input, l, mid);
		cnt_inv += merge_sort(input, mid+1, r);

		// Chama a intercalação (conquistar)
		cnt_inv += merge(input, l, mid, r);
	}
	
	return cnt_inv;
}

int main(){
	int n, k;
	
	scanf("%d", &n);
	int maior_n = n;
	int *input = malloc(maior_n * sizeof(int));
	while(n){
		// Lê a sequencia para o vetor
		for(int i = 0; i < n; i++)
			scanf("%d", &input[i]);

		k = merge_sort(input, 0, n-1);
		
		// Se Jaques sempre começa, as trocas 1, 3, 5... são feitas por ele
		if(k&1) printf("Jaques\n");
		else printf("Fino\n");

		scanf("%d", &n);
		if(n > maior_n){
			maior_n = n;
			input = realloc(input, maior_n * sizeof(int)); // Evitar de ficar fazendo reallocs desnecessários, e ao mesmo tempo não alocar um vetor maior que qualquer caso do problema
		}
	}

	free(input);
	return 0;
}