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
	int kolicinaBrojeva = 0;
	double a[100], b[100];
	while (kolicinaBrojeva < 2) {
		MPI_Comm_rank(MPI_COMM_WORLD, &rang);
		if (rang == 0) {
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 3, 1, MPI_COMM_WORLD);
			MPI_Recv(a, 100, MPI_DOUBLE, 4, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (kolicinaBrojeva == 1) {
				printf("Proces 0 primio je poruku oznake %d od procesa ranga %d.\n",
					status.MPI_TAG, status.MPI_SOURCE);
			}
		}
		else if (rang == 3) {
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 2, 2, MPI_COMM_WORLD);
			MPI_Recv(a, 100, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (kolicinaBrojeva == 1) {
			printf("Proces 3 primio je poruku oznake %d od procesa ranga %d.\n",
				status.MPI_TAG, status.MPI_SOURCE);
			}
		}
		else if (rang == 2) {
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 1, 3, MPI_COMM_WORLD);
			MPI_Recv(a, 100, MPI_DOUBLE, 3, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (kolicinaBrojeva == 1) {
			printf("Proces 2 primio je poruku oznake %d od procesa ranga %d.\n",
				status.MPI_TAG, status.MPI_SOURCE);
			}
		}
		else if (rang == 1) {
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 4, 4, MPI_COMM_WORLD);
			MPI_Recv(a, 100, MPI_DOUBLE, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (kolicinaBrojeva == 1) {
			printf("Proces 1 primio je poruku oznake %d od procesa ranga %d.\n",
				status.MPI_TAG, status.MPI_SOURCE);
			}
		}
		else if (rang == 4) {
			MPI_Send(a, kolicinaBrojeva, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
			MPI_Recv(a, 100, MPI_DOUBLE, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (kolicinaBrojeva == 1) {
			printf("Proces 4 primio je poruku oznake %d od procesa ranga %d.\n",
				status.MPI_TAG, status.MPI_SOURCE);
		}
		}
		kolicinaBrojeva++;
	}

	MPI_Finalize();
	return 0;
}