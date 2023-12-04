#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
int main(int argc, char* argv[]) {
	int rang;
	const int MAKS_BROJ = 100;
	int brojevi[MAKS_BROJ];
	MPI_Init(&argc, &argv);
	int velicina;
	MPI_Comm_size(MPI_COMM_WORLD, &velicina);
	if (velicina < 3) {
		return 0;
	}
	MPI_Request zahtjev;
	MPI_Status status;
	int kolicinaBrojeva;
	double a[100], b[100];
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	if (rang == 2) {
		for (int k = 0; k < 50; k++) {
			const int MAKS_BROJ = 100;
			int brojevi[MAKS_BROJ];
			srand(time(NULL));
			kolicinaBrojeva = (rand() / (float)RAND_MAX) * MAKS_BROJ;
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 0, 20, MPI_COMM_WORLD);
			kolicinaBrojeva = (rand() / (float)RAND_MAX) * MAKS_BROJ;
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 0, 40, MPI_COMM_WORLD);
		}
	}
	else if (rang == 0) {
		for (int k = 0; k < 50; k++) {
			MPI_Recv(a, 100, MPI_DOUBLE, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Proces 0 primio je poruku oznake %d od procesa ranga %d.\n",
				status.MPI_TAG, status.MPI_SOURCE);
			MPI_Recv(a, 100, MPI_DOUBLE, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		}
	}
	MPI_Finalize();
	return 0;
}