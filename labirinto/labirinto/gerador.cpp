#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Labirinto{
private:
	int linha;
	int coluna;
	int total;
	pair<int, int> ini;
	pair<int, int> fim;
public:
	char **lab;
	char **visitados;
	
	int getIniFirst(){
		return ini.first;
	}
	
	int getIniSecond(){
		return ini.second;
	}
	
	void setLinha(){
		cin>>linha;
	}
	
	void setColuna(){
		cin>>coluna;
	}
	
	void setTotal(){
		total = (linha*coluna) - 2;
	}
	
	void iniciarLab(){
		lab = new char*[linha];
		for(int i = 0; i<linha; i++){
			lab[i] = new char[coluna];
		}
		visitados = new char*[linha];
		for(int i = 0; i<linha; i++){
			visitados[i] = new char[coluna];
		}
		
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				lab[i][j] = '-';
				visitados[i][j] = '*';
			}
		}
	}
	
	void deletarLab(){
		for(int i = 0; i<linha; i++){
			delete[] lab[i];
		}
		delete[] lab;
	}
	
	void randomizarPontos(){
		ini.first = rand() % linha ;
		ini.second = rand() % coluna;
		fim.first = rand () % linha;
		fim.second = rand() % coluna;
		
		lab[ini.first][ini.second] = '#';
		lab[fim.first][fim.second] = '$';
		visitados[ini.first][ini.second] = '-';
	}
	
	void pontos(){
		cout<<ini.first<<" "<<ini.second<<endl;
		cout<<fim.first<<" "<<fim.second<<endl;
	}
	
	void imprimirIn(){
		ofstream myfile;
		myfile.open("1.in");
		myfile<<linha<<" "<<coluna<<endl;
		lab[ini.first][ini.second] = '#';
		lab[fim.first][fim.second] = '$';
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				myfile<<lab[i][j];
			}
			myfile<<endl;
		}
		myfile<<endl;
		myfile.close();
	}
	
	void imprimirLab(){
		lab[ini.first][ini.second] = '#';
		lab[fim.first][fim.second] = '$';
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				cout<<lab[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	void imprimirVisitados(){
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				cout<<visitados[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	void desenharRecurcao(int r, int c){

		int vet[4];
		int visi[4];
		for(int i = 0; i<4; i++)
			visi[i] = 0;
		int count = 0;
		int aux ;
		while(count < 4){
			aux = rand()%4;
			if(aux == 0 and visi[0] == 0){
				vet[count] = aux;
				count++;
				visi[0] = 1;
			}
			if(aux == 1 and visi[1] == 0){
				vet[count] = aux;
				count++;
				visi[1] = 1;
			}
			if(aux == 2 and visi[2] == 0){
				vet[count] = aux;
				count++;
				visi[2] = 1;
			}
			if(aux == 3 and visi[3] == 0){
				vet[count] = aux;
				count++;
				visi[3] = 1;
			}
		}
		
		for(int i = 0; i<4; i++){
			switch(vet[i]){
			case 0:
				if(r - 2 <= 0)
					continue;
				if(visitados[r-2][c] != '-'){
					visitados[r-2][c] = '-';
					visitados[r-1][c] = '-';
					lab[r-2][c] = '*';
					lab[r-1][c] = '*';
					
					desenharRecurcao(r - 2, c);
				}
				break;
			
			case 1:
				if(c+2 >= coluna - 1)
					continue;
				if(visitados[r][c+2] != '-'){
					visitados[r][c+2] = '-';
					visitados[r][c+1] = '-';
					lab[r][c+2] = '*';
					lab[r][c+1] = '*';
					desenharRecurcao(r, c+2);
				}
				break;
			
			case 2:
					if(r+2 >= linha - 1)
						continue;
				if(visitados[r+2][c] != '-'){
					visitados[r+2][c] = '-';
					visitados[r+1][c] = '-';
					lab[r+2][c] = '*';
					lab[r+1][c] = '*';
			
					desenharRecurcao(r+2, c);
				}
				break;
			
			case 3:
				if(c-2 <= 0)
						continue;
				if(visitados[r][c-2] != '-'){
					visitados[r][c-2] = '-';
					visitados[r][c-1] = '-';
					lab[r][c-2] = '*';
					lab[r][c-1] = '*';
					desenharRecurcao(r, c-2);
				}
				break;
			}
		}
	}
};



int main(int argc, const char * argv[]) {
	Labirinto l;
	srand(time(NULL));
	l.setLinha();
	l.setColuna();
	l.setTotal();
	l.iniciarLab();
	l.randomizarPontos();
	l.desenharRecurcao(l.getIniFirst(), l.getIniSecond());
	//l.imprimirLab();
	l.imprimirIn();
	return 0;
}
