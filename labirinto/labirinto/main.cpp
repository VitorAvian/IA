#include <iostream>
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
		//visitados[fim.first][fim.second] = '-';
		
		//visitados[0][0] = '-';
	}
	
	void pontos(){
		cout<<ini.first<<" "<<ini.second<<endl;
		cout<<fim.first<<" "<<fim.second<<endl;
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
		
		/*for(int i = 0; i<4; i++){
			cout<<vet[i]<<" ";
		}
		cout<<endl;*/
		
		for(int i = 0; i<4; i++){
			//cout<<vet[i]<<" ";
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
	
	
	void desenhar(){
		//stack<pair<int, int> > s;
		queue<pair<int, int> > q;
		pair<int, int> atual;
		pair<int, int> aux;
		int count, count2, flag;
		atual = ini;
		while(!q.empty()){
			q.push(atual);
			visitados[atual.first][atual.second] = '-';
			//if(atual == fim){
			//	break;
			//}
			//visitados[atual.first][atual.second] = '-';
			count = 0;
			if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-')
				count++;
			//if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second+1] != '-')
			//	count++;
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second+1] != '-')
				count++;
			//if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-')
			//	count++;
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-')
				count++;
			//if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-')
			//	count++;
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-')
				count++;
			//if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-')
				//count++;
			if(count>0){
				
				flag = 1;
				while(flag){
					switch(rand()%4){
						case 0:
							if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-'){
								if(count>1){
									q.push(atual);
								}
								lab[atual.first-1][atual.second] = '*';
								visitados[atual.first-1][atual.second] = '-';
								if(atual.first + 1 < linha)visitados[atual.first+1][atual.second] = '-';
								if(atual.second -1 >= 0) visitados[atual.first][atual.second-1] = '-';
								if(atual.second +1 < coluna) visitados[atual.first][atual.second+1] = '-';
								atual.first--;
								flag = 0;
							}
							break;
						/*case 1:
							if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second+1] != '-'){
								if(count>1){
									s.push(atual);
								}
								lab[atual.first-1][atual.second+1] = '*';
								visitados[atual.first-1][atual.second+1] = '-';
								atual.first--;
								atual.second++;
								total--;
								flag = 0;
							}
							break;*/
						case 1:
							if(atual.second + 1 < coluna and visitados[atual.first][atual.second+1] != '-'){
								if(count>1){
									q.push(atual);
								}
								lab[atual.first][atual.second+1] = '*';
								
								if(atual.first - 1 >= 0) visitados[atual.first-1][atual.second] = '-';
								if(atual.first + 1 < linha)visitados[atual.first+1][atual.second] = '-';
								if(atual.second -1 >= 0) visitados[atual.first][atual.second-1] = '-';
								visitados[atual.first][atual.second+1] = '-';
								atual.second++;
						
								flag = 0;
							}
							break;
						/*case 3:
							if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-'){
								if(count>1){
									s.push(atual);
								}
								lab[atual.first+1][atual.second+1] = '*';
								visitados[atual.first+1][atual.second+1] = '-';
								atual.first++;
								atual.second++;
								total--;
								flag = 0;
							}
							break;*/
						case 2:
							if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-'){
								if(count>1){
									q.push(atual);
								}
								lab[atual.first+1][atual.second] = '*';
								
								if(atual.first - 1 >= 0) visitados[atual.first-1][atual.second] = '-';
								visitados[atual.first+1][atual.second] = '-';
								if(atual.second -1 >= 0) visitados[atual.first][atual.second-1] = '-';
								if(atual.second + 1 < coluna)visitados[atual.first][atual.second+1] = '-';
								atual.first++;
								//total-=4;
								flag = 0;
							}
							break;
						/*case 5:
							if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-'){
								if(count>1){
									s.push(atual);
								}
								lab[atual.first+1][atual.second-1] = '*';
								visitados[atual.first+1][atual.second-1] = '-';
								atual.first++;
								atual.second--;
								total--;
								flag = 0;
							}
							break;*/
						case 3:
							if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-'){
								if(count>1){
									q.push(atual);
								}
								lab[atual.first][atual.second-1] = '*';
								
								if(atual.first - 1 >= 0) visitados[atual.first-1][atual.second] = '-';
								if(atual.first + 1 < linha)visitados[atual.first+1][atual.second] = '-';
								visitados[atual.first][atual.second-1] = '-';
								if(atual.second + 1 < coluna)visitados[atual.first][atual.second+1] = '-';
								atual.second--;
								//total-=4;
								flag = 0;
							}
							break;
						/*case 7:
							if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-'){
								if(count>1){
									s.push(atual);
								}
								lab[atual.first-1][atual.second-1] = '*';
								visitados[atual.first-1][atual.second-1] = '-';
								atual.first--;
								atual.second--;
								total--;
								flag = 0;
							}
							break;*/
					}
					
				}
			}
			else {
				//imprimirLab();
				//imprimirVisitados();
				while(!q.empty()){
					aux = q.front();
					count2 = 0;
					if(aux.first - 1 >= 0 and visitados[aux.first-1][aux.second] != '-')
						count2++;
					//if(aux.first - 1 >= 0 and aux.second + 1 < coluna and visitados[aux.first-1][aux.second+1] != '-')
					//	count2++;
					if(aux.second + 1 < coluna and visitados[aux.first][aux.second+1] != '-')
						count2++;
					//if(aux.first + 1 < linha and aux.second + 1 < coluna and visitados[aux.first+1][aux.second+1] != '-')
					//	count2++;
					if(aux.first + 1 < linha and visitados[aux.first+1][aux.second] != '-')
						count2++;
					//if(aux.first + 1 < linha and aux.second - 1 >= 0 and visitados[aux.first+1][aux.second-1] != '-')
					//	count2++;
					if(aux.second - 1 >= 0 and visitados[aux.first][aux.second-1] != '-')
						count2++;
					//if(aux.first - 1 >= 0 and aux.second - 1 >= 0 and visitados[aux.first-1][aux.second-1] != '-')
					//	count2++;
					if(count2 > 0){
						atual = aux;
						break;
					}
					else{
						//atual = s.top();
						q.pop();
					}
				}
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
	//l.pontos();
	//l.desenhar();
	l.desenharRecurcao(l.getIniFirst(), l.getIniSecond());
	l.imprimirLab();
	//l.imprimirVisitados();
	return 0;
}
