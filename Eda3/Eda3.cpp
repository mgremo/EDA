#include <string>
#include <iostream>
#include <vector>

using namespace std;

//O(1)
int DiagAscd(const int& i, const int& j) {
	return i + j;
}
//O(1)
int DiagDescd(const int& i, const int& j) {
	return i - j;
}
// O(T) = O(DiagDesd) + O(DiagAscd)
// O(T) = O(1) + O(1) = O(1)
bool ataca(const int& N,const int& i, const int& k, const vector<bool>& filas, const vector<bool>& diagAsc, const vector<bool>& diagDesc) {
	int diAsc = DiagAscd(i, k);
	int diDes = DiagDescd(i, k) + (N  - 1);
	return diagAsc[diAsc] || diagDesc[diDes] || filas[i];
}

//O(T) = O(Ataca) = O(1)
bool Sol(const int& i, const int& k, const int& N, vector<bool>& filas, const vector<bool>& diagAsc, const vector<bool>& diagDesc) {
	return (k == N - 1) && !ataca(N,i, k, filas, diagAsc, diagDesc);
}
//O(T) = O(Ataca) = O(1)
bool solParcial(const int& i, const int& k, const int& N, const vector<bool>& filas, const vector<bool>& diagAsc, const vector<bool>& diagDesc) {
	return (k < N - 1) && !ataca(N,i, k, filas, diagAsc, diagDesc);
}

// k: numero de la columna en la que ponemos a la reina
// N: numero de reinas
// i: numero de fila en la que ponemos a la reina
// tab: Filas ocupadas
// Diag Asc: Diagonales ocupadas
// Diag Desc: Diagonales ocupadas
// numSol: Numero de combinaciones posibles colocando reinas

/*COSTE DE NREINAS:
O(T) = N * ( O(Sol) ) si es solucion o k < N
Coste: N * ( O(SolParcial) + O(Nreinas) ) mientras sea solucion parcial (k < N - 1) 
O(T) = O( N ^ N )
*/
void NReinas(const int& N, int k, vector<bool>& fils, vector<bool>& diagAsc, vector<bool>& diagDesc, int& numSol) {
	//Hay que ver todas las posibles combinaciones en cada fila de la columna K
	for (int i = 0; i < N; i++) {
		if (Sol(i, k, N, fils, diagAsc, diagDesc))
			numSol++;
		else if (solParcial(i, k, N, fils, diagAsc, diagDesc)) {
			//MARCADO
			int diDes = DiagDescd(i, k) + ((N - 1));
			fils[i] = true;
			diagAsc[DiagAscd(i, k)] = true;
			diagDesc[diDes] = true;
			//LLAMADA RECURSIVA
			NReinas(N, k + 1, fils, diagAsc, diagDesc, numSol);
			//DESMARCADO
			fils[i] = !true;
			diagAsc[DiagAscd(i, k)] = !true;
			diagDesc[diDes] = !true;
		}
	}


}
void initBoolVector(vector<bool>& v) {
	for (int i = 0; i < v.size(); i++)
		v[i] = false;
}

void NQueen(int N) {
	int nsol = 0;
	vector<bool> tab(N), diagAsc(N * 2 - 1), diagDesc(N * 2 - 1);
	initBoolVector(tab);
	initBoolVector(diagAsc);
	initBoolVector(diagDesc);
	NReinas(N, 0, tab, diagAsc, diagDesc, nsol);
	cout << nsol << endl;
}

int main() {
	int nCasos;
	cin >> nCasos;
	for (int i = 0; i < nCasos; i++) {
		int N;
		cin >> N;
		if(N>0) NQueen(N);
		else cout << 0 << endl;
	}
	return 0;
}