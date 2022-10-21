#include <stdio.h>

#define MAX_N 100005
int input[MAX_N];

int count_inversions(int n){
	int count = 0;

	for(int i = 0; i < n-1; i++)
		for(int j = i+1; j < n; j++)
			if(input[i] > input[j])
				count++;

	return count;
}

int main(){
	int n, k;
	
	scanf("%d", &n);
	while(n){
		for(int i = 0; i < n; i++)
			scanf("%d", &input[i]);

		k = count_inversions(n);

		if(k&1) printf("Jaques\n");
		else printf("Fino\n");

		scanf("%d", &n);
	}

	return 0;
}