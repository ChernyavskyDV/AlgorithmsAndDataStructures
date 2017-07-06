#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	FILE* in = fopen("input.txt", "r");
	
	int N;
	fscanf(in, "%d", &N);
	
	int tempIndex;
	int *cardNumber = new int[N];
	for (int i = 0; i < N; ++i) {
		fscanf(in, "%d", &tempIndex);
		cardNumber[tempIndex - 1] = i+1;
	}
	
	int**solutionMatrix = new int*[N+1];
	for (int i = 0; i < N+1; ++i) {
		solutionMatrix[i] = new int[N+1];
	}
	for (int i = 0; i < N + 1; ++i) {
		for (int j = 0; j < N + 1; ++j) {
			solutionMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < N; ++i) {
		solutionMatrix[i][i + 1] = 1;
	}

	for (int i = 2; i < N + 1; ++i) {
		for (int j = 1; j < N - i + 2; ++j) {
			int k = j + i - 1;
			solutionMatrix[j][k] = INT_MAX;
			for (int l = j; l < k; ++l) {
				solutionMatrix[j][k] = min(solutionMatrix[j][k],solutionMatrix[j][l]+solutionMatrix[l+1][k]+abs(cardNumber[l-1]-cardNumber[k-1]));
			}
		}
	}

	FILE* out = fopen("output.txt", "w");
	fprintf(out, "%d", solutionMatrix[1][N]);
	
	fclose(in);
	fclose(out);
	delete[]cardNumber;
	delete[]solutionMatrix;
	return 0;
}