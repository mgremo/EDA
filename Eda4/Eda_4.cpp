#include <vector>
#include <iostream>

using namespace std;

int totalCash(vector<int> cash, vector<int> values, int maxValue) {
	int num = 0;
	for (int i = 0; i < 8; i++) {
		num += cash[i] * values[i];
	}
	return num;
}

int totalCoins(const vector<int> cash) {
	int coins = 0;
	for (int i = 0; i < 8; i++)
		coins += cash[i];
	return coins;
}
bool esSol(int actValue, int maxValue) {
	return actValue == maxValue;
}
bool esCompletable(int actValue, int maxValue) {
	return actValue < maxValue;
}
bool nextCoin(const vector<int>& cash, int& actCoin) {
	while (actCoin < 8 && cash[actCoin] == 0)
		actCoin++;
	return actCoin < 8;
}
int topCoin(const vector<int>& v,const vector<int>& values,int maxValue) {
	int iMax = 8;
	while (iMax > 0 && ( v[iMax-1] == 0 || (v[iMax-1] != 0 && (values[iMax-1] > maxValue))))
		iMax--;
	return iMax;
}
//Metodo recursivo
bool calderilla(const vector<int>& v, vector<int>& u, const vector<int>& w, int i,int& iMax, int val, int& maxVal,int& n) {

	bool resuelto = false;
	//Si podemos poner mas monedas
	if (i < iMax) {
		int k = v[i];
		int valAux;
		//Tratamos de ponerlas todas, y a partir de ahi vamos quitando
		while (!resuelto && k >= 0) {
			u[i] = k;
			valAux = val + w[i] * k;
			resuelto = esSol(valAux, maxVal) || (esCompletable(valAux, maxVal) && calderilla(v, u, w, i + 1, iMax, valAux, maxVal));
			k--;
		}
	}
	return resuelto;
}

int resuelve(vector<int> cash, vector<int> values, int maxValue) {
	vector<int> actCash{ 0,0,0,0,0,0,0,0 };
	int total = totalCash(cash,values,maxValue);
	if (maxValue > 0 && total > maxValue) {
		int iMax = topCoin(cash, values, maxValue);
		if (iMax >= 0 && calderilla(cash, actCash, values, 0, iMax, 0, maxValue))
			return totalCoins(actCash);
		else
			return -1;
	}
	else if (maxValue == 0)
		return 0;
	else if (total == maxValue)
		return totalCoins(cash);
	else return -1;
}
void input(const vector<int>& values) {
	int val;
	cin >> val;
	int n;
	vector<int> cash;
	for (int i = 0; i < 8; i++) {
		cin >> n;
		cash.push_back(n);
	}
	int sol = resuelve(cash, values, val);
	if (sol >= 0)
		cout << sol << endl;
	else
		cout << "IMPOSIBLE" << endl;
}

int main() {
	vector<int> values = { 1,2,5,10,20,50,100,200};
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++) {
		input(values);
	}
	return 0;
}